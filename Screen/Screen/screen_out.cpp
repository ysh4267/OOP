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

	void draw(char *canvas) const // 함수 본체 앞에 const를 선언하는 것은 매우 중요한 의미를 부여하고 있습니다.
	{
		if (pos >= 0 && pos < SCREEN_SIZE)
		{
			strncpy(canvas + pos, shape, strlen(shape));
		}
	}
};

struct Bullet {
	struct GameObject  myData;

	void draw(char *canvas, const struct GameObject *player, const struct GameObject* enemy) const
	{
		if (myData.pos == -1 || player == NULL || enemy == NULL) return;

		if (myData.pos >= 0 && myData.pos < SCREEN_SIZE)
		{
			if (player->pos < enemy->pos)
			{
				strncpy(canvas + myData.pos, ">", strlen(">"));
			}
			else if (player->pos > enemy->pos)
			{
				strncpy(canvas + myData.pos, "<", strlen("<"));
			}
		}
	}
};

void clear_screen(char *canvas)
{
	memset(canvas, ' ', SCREEN_SIZE);
	canvas[SCREEN_SIZE] = '\0';
}

void process_input(struct GameObject* player, struct GameObject* enemy, struct Bullet bullets[], int bullets_len)
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
			if (bullets[i].myData.pos == -1)
			{
				bullets[i].myData.pos = player->pos;
				break; // exit from for statement
			}
		}
	}
}

void draw(char *canvas, const struct GameObject* player, const struct GameObject* enemy, const struct Bullet bullets[], int bullets_len)
{
	if (canvas == NULL) return;

	player->draw(canvas);
	enemy->draw(canvas);
	for (int i= 0; i < bullets_len; i++)
	{
		bullets[i].draw(canvas, player, enemy);
	}
}

void update(const struct GameObject* player, const struct GameObject* enemy, struct Bullet bullets[], int bullets_len)
{
	for (int i = 0; i < bullets_len; i++)
	{
		if (bullets[i].myData.pos == -1) continue;

		if (bullets[i].myData.pos < 0 || bullets[i].myData.pos >= SCREEN_SIZE)
		{
			bullets[i].myData.pos = -1;
			continue;
		}
		if (bullets[i].myData.pos == enemy->pos)
		{
			bullets[i].myData.pos = -1;
			continue;
		}
		if (player->pos < enemy->pos)
		{
			bullets[i].myData.pos++;
		}
		else if (player->pos > enemy->pos)
		{
			bullets[i].myData.pos--;
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
	Bullet bullets[bullets_len];

	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;
	strcpy(enemy.shape, "*_*");
	enemy.pos = rand() % SCREEN_SIZE;
	for (int i = 0; i < bullets_len; i++)
	{
		strcpy(bullets[i].myData.shape, ">");
		bullets[i].myData.pos = -1;
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