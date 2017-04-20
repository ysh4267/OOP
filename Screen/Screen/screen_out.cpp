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

void process_input(struct GameObject* player, struct GameObject* enemy, struct GameObject bullets[], int bullets_len)
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
		for (int i = 0; i < bullets_len; i++)
		{
			if (bullets[i].pos == -1)
			{
				bullets[i].pos = player->pos;
				break; // exit from for statement
			}
		}
	}
}

void draw(char *canvas, const struct GameObject* player, const struct GameObject* enemy, const struct GameObject bullets[], int bullets_len)
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
	for (int i = 0; i < bullets_len; i++)
	{
		if (bullets[i].pos == -1) continue;

		// now, bullets[i].pos != -1 
		
		if (player->pos < enemy->pos)
		{
			strncpy(canvas + bullets[i].pos, ">", strlen(">"));
		}
		else if (player->pos > enemy->pos)
		{
			strncpy(canvas + bullets[i].pos, "<", strlen("<"));
		}
	}
}

void update(const struct GameObject* player, const struct GameObject* enemy, struct GameObject bullets[], int bullets_len)
{
	for (int i = 0; i < bullets_len; i++)
	{
		if (bullets[i].pos == -1) continue;

		if (bullets[i].pos < 0 || bullets[i].pos >= SCREEN_SIZE)
		{
			bullets[i].pos = -1;
			continue;
		}
		if (bullets[i].pos == enemy->pos)
		{
			bullets[i].pos = -1;
			continue;
		}
		if (player->pos < enemy->pos)
		{
			bullets[i].pos++;
		}
		else if (player->pos > enemy->pos)
		{
			bullets[i].pos--;
		}
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
	GameObject enemy;
	const int bullets_len = 30;
	GameObject bullets[bullets_len];

	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;
	strcpy(enemy.shape, "*_*");
	enemy.pos = rand() % SCREEN_SIZE;
	for (int i = 0; i < bullets_len; i++)
	{
		strcpy(bullets[i].shape, ">");
		bullets[i].pos = -1;
	}
	
	while (1)
	{
		clear_screen(canvas);
		process_input(&player, &enemy, bullets, bullets_len);
		draw(canvas, &player, &enemy, bullets, bullets_len);
		update(&player, &enemy, bullets, bullets_len);
		render(canvas);
	}
	return 0;
}