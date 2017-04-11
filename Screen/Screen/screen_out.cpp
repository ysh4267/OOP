#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define SCREEN_SIZE	79

void draw(char *screen, int bullet_pos, int direction, int player_pos, const char *face)
{
	strncpy(screen + bullet_pos, 
		(direction == 0) ? "===--->" : "<---===", 
		(direction == 0) ? strlen("===--->") : strlen("<---==="));

	strncpy(screen + player_pos, face, strlen(face));

}

void update(int* bullet_pos, int* direction)
{
	if (*direction == 0)
	{
		//(*bullet_pos)++;
		if (*bullet_pos >= SCREEN_SIZE) {
			*direction = 1;
			*bullet_pos = SCREEN_SIZE - 1;
		}
	}
	else {
		//(*bullet_pos)--;
		if (*bullet_pos < 0) {
			*direction = 0;
			*bullet_pos = 0;
		}
	}
}

void clear_screen(char *screen)
{
	memset(screen, ' ', SCREEN_SIZE);
}

void render(char *screen)
{
	screen[SCREEN_SIZE] = '\0';
	printf("%s\r", screen);
	Sleep(33);
}

void process_input(int* player_pos, int* bullet_pos)
{
	if (_kbhit() == 0) return;

	int ch = _getch();

	if (ch == 224)
	{
		ch = _getch();
		if (ch == 75) (*player_pos)--;
		if (ch == 77) (*player_pos)++;
	}
	else {
		if (ch == 'a') (*player_pos)--;
		if (ch == 's') (*player_pos)++;
		if (ch == 'w') (*bullet_pos)++;
		if (ch == 'x') (*bullet_pos)--;
	}
}

int main()
{
	int bullet_pos = 0;
	char screen[SCREEN_SIZE + 1];
	int direction = 0;
	char face[] = "^___________^";
	int player_pos = 10;

	while (1)
	{
		clear_screen(screen);
		process_input(&player_pos, &bullet_pos);
		draw(screen, bullet_pos, direction, player_pos, face);			
		update(&bullet_pos, &direction);
		render(screen);			
	}
	return 0;

}