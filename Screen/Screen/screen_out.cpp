#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>

#define SCREEN_SIZE		79

using namespace std;

struct GameObject {
	char	shape[16];
	int		pos;

};

void clear_screen(char *canvas)
{
	memset(canvas, ' ', SCREEN_SIZE);
	canvas[SCREEN_SIZE] = '\0';
}

void process_input(struct GameObject* player, struct GameObject* enemy, struct GameObject* bullet)
{
	if (_kbhit() == 0) return;

	int ch = _getch();
	if (ch == 224)
	{
		ch = _getch();
		switch (ch)
		{
		case 75:
			player->pos--; 
			break;
		case 77:
			player->pos++;
			break;
		case 72:
			enemy->pos--;
			break;
		case 80:
			enemy->pos++;
			break;
		}
	}
	else if (ch == ' ')
	{
		if (bullet->pos == -1)
		{
			bullet->pos = player->pos;
		}
	}
}

void draw(char *canvas, const struct GameObject* player, const struct GameObject* enemy, const struct GameObject* bullet)
{
	if (canvas == NULL) return;

	if (player != NULL && player->pos >= 0 && player->pos < SCREEN_SIZE)
	{
		strncpy(canvas + player->pos, player->shape, strlen(player->shape));
	}
	if (enemy->pos >= 0 && enemy->pos < SCREEN_SIZE)
	{
		strncpy(canvas + enemy->pos, enemy->shape, strlen(enemy->shape));
	}
	if (bullet->pos != -1)
	{
		if (player->pos < enemy->pos)
		{
			strncpy(canvas + bullet->pos, ">", strlen(">"));
		}
		else if (player->pos > enemy->pos)
		{
			strncpy(canvas + bullet->pos, "<", strlen("<"));
		}
	}
}

void update(const struct GameObject* player, const struct GameObject* enemy, struct GameObject* bullet)
{
	if (bullet->pos == -1) return;

	if (bullet->pos < 0 || bullet->pos >= SCREEN_SIZE)
	{
		bullet->pos = -1;
		return;
	}
	if (bullet->pos == enemy->pos)
	{
		bullet->pos = -1;
		return;
	}
	if (player->pos < enemy->pos)
	{
		bullet->pos++;
	}
	else if (player->pos > enemy->pos)
	{
		bullet->pos--;
	}
}

void render(char *canvas)
{
	canvas[SCREEN_SIZE] = '\0';
	cout << canvas << '\r';
	Sleep(33);
}

int main()
{
	char	canvas[SCREEN_SIZE + 1];
	GameObject player;
	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;

	GameObject enemy;
	strcpy(enemy.shape,"*_*");
	enemy.pos = rand() % SCREEN_SIZE;

	GameObject bullet;
	strcpy(bullet.shape, ">");
	bullet.pos = -1;


	while (1)
	{
		clear_screen(canvas);
		process_input(&player, &enemy, &bullet);
		draw(canvas, &player, &enemy, &bullet);
		update(&player, &enemy, &bullet);
		render(canvas);
	}
	return 0;
}