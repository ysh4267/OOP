#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>

using namespace std;

#define SCREEN_SIZE	79


struct GameObject {
	int		pos;
	char	shape[20];
};

void clear_screen(char *screen)
{
	memset(screen, ' ', SCREEN_SIZE);
}

void draw(char *screen, const GameObject& player, const GameObject& enemy, const GameObject& bullet)
{
	if (screen == NULL) return;

	if (player != NULL && player_pos >=0 && player_pos < SCREEN_SIZE ) {
		strncpy(screen + player_pos, player, strlen(player));
	}
	if (enemy != NULL && enemy_pos >= 0 && enemy_pos < SCREEN_SIZE) {
		strncpy(screen + enemy_pos, enemy, strlen(enemy));
	}
	if (bullet_pos != -1) {
		if (player_pos < enemy_pos)
		{
			strncpy(screen + bullet_pos, ">", strlen(">"));
		}
		else if ( player_pos > enemy_pos)
		{
			strncpy(screen + bullet_pos, "<", strlen("<"));
		}
	}
}

void update(GameObject& player, GameObject& enemy, GameObject& bullet)
{
	if (*bullet_pos == -1) return;

	if (*bullet_pos == enemy_pos)
	{
		*bullet_pos = -1;
		return;
	}
	if (*bullet_pos < 0 || *bullet_pos >= SCREEN_SIZE)
	{
		*bullet_pos = -1;
		return;
	}
	
	if (player_pos < enemy_pos)		(*bullet_pos)++;
	
	if (player_pos > enemy_pos)		(*bullet_pos)--;
	
}



void render(char *screen)
{
	screen[SCREEN_SIZE] = '\0';
	cout << screen << '\r';
	Sleep(33);
}

void process_input(GameObject& player, GameObject& enemy, GameObject& bullet)
{
	if (_kbhit() == 0) return;

	int ch = _getch();

	if (ch == 224)
	{
		ch = _getch();
		if (ch == 75) (*player_pos)--;
		if (ch == 77) (*player_pos)++;
		if (ch == 80) (*enemy_pos)++;
		if (ch == 72) (*enemy_pos)--;
	}
	else if (ch == ' ') 
	{
		if (*bullet_pos == -1) 
		{
			*bullet_pos = *player_pos;
		}
	}
}

int main()
{	
	char screen[SCREEN_SIZE + 1];
	GameObject player;
	GameObject enemy;
	GameObject bullet;

	strcpy(player.shape, "^_^");
	player.pos = rand() % SCREEN_SIZE;
	strcpy(enemy.shape, "*__*");
	enemy.pos = rand() % SCREEN_SIZE;
	strcpy(bullet.shape, ">");
	bullet.pos = -1;

	while (1)
	{
		clear_screen(screen);
		process_input(player, enemy, bullet);
		draw(screen, player, enemy, bullet);
		update(player, enemy, bullet);
		render(screen);			
	}
	return 0;

}