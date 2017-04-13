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

void process_input(GameObject& player, GameObject& enemy, GameObject& bullet)
{
	if (_kbhit() == 0) return;

	int ch = _getch();
	if (ch == 224)
	{
		ch = _getch();
		switch (ch)
		{
		case 75:
			(*player_pos)--; 
			break;
		case 77:
			(*player_pos)++;
			break;
		case 72:
			(*enemy_pos)--;
			break;
		case 80:
			(*enemy_pos)++;
			break;
		}
	}
	else if (ch == ' ')
	{
		if (*bullet_pos == -1)
		{
			*bullet_pos = *player_pos;
		}
	}
}

void draw(char *canvas, const GameObject& player, const GameObject& enemy, const GameObject& bullet)
{
	if (canvas == NULL) return;

	if (player != NULL && player_pos >= 0 && player_pos < SCREEN_SIZE)
	{
		strncpy(canvas + player_pos, player, strlen(player));
	}
	if (enemy != NULL && enemy_pos >= 0 && enemy_pos < SCREEN_SIZE)
	{
		strncpy(canvas + enemy_pos, enemy, strlen(enemy));
	}
	if (bullet_pos != -1)
	{
		if (player_pos < enemy_pos)
		{
			strncpy(canvas + bullet_pos, ">", strlen(">"));
		}
		if (player_pos > enemy_pos)
		{
			strncpy(canvas + bullet_pos, "<", strlen("<"));
		}
	}
}

void update(const GameObject& player, const GameObject& enemy, GameObject& bullet)
{
	if (*bullet_pos == -1) return;

	if (*bullet_pos < 0 || *bullet_pos >= SCREEN_SIZE)
	{
		*bullet_pos = -1;
		return;
	}
	if (*bullet_pos == enemy_pos)
	{
		*bullet_pos = -1;
		return;
	}
	if (player_pos < enemy_pos)
	{
		(*bullet_pos)++;
	}
	else if (player_pos > enemy_pos)
	{
		(*bullet_pos)--;
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
		process_input(player, enemy, bullet);
		draw(canvas, player, enemy, bullet);
		update(player, enemy, bullet);
		render(canvas);
	}
	return 0;
}