#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <Windows.h>

#define SCREEN_SIZE	79

void draw(char *screen, int bullet_pos, int direction)
{
	screen[bullet_pos] = (direction == 0) ? '>' : '<';
}

void update(int* bullet_pos, int* direction)
{
	if (*direction == 0)
	{
		(*bullet_pos)++;
		if (*bullet_pos >= SCREEN_SIZE) {
			*direction = 1;
			*bullet_pos = SCREEN_SIZE - 1;
		}
	}
	else {
		(*bullet_pos)--;
		if (*bullet_pos < 0) {
			*direction = 0;
			*bullet_pos = 0;
		}
	}
}

int main()
{
	int bullet_pos = 0;
	char screen[SCREEN_SIZE + 1];
	int direction = 0;
	char face[] = "^___________^";

	while (1)
	{
		memset(screen, ' ', SCREEN_SIZE);

		draw(screen, bullet_pos, direction);	
		strncpy(screen + 10, face, strlen(face));

		update(&bullet_pos, &direction);

		screen[SCREEN_SIZE] = '\0';
		printf("%s\r", screen);
		Sleep(33);		
	}
	return 0;

}