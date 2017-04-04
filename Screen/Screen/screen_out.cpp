#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>

#define SCREEN_SIZE 79

int main()
{
	char screen[SCREEN_SIZE + 1];
	int bullet_pos = 30;
	char bullet_shape = '>';
	char player_face[4] = "^_^";
	char enemy_face[] = "*_____*";
	int enemy_pos = 50;
	int player_pos = 20;

	
	while (true) {
		memset(screen, ' ', SCREEN_SIZE);

		int ch = _getch();
		enemy_pos = enemy_pos + (rand() % 3 - 1);
		//enemy_pos %= SCREEN_SIZE;
		
		screen[bullet_pos] = bullet_shape;
		strncpy(screen + player_pos, player_face, strlen(player_face));
		strncpy(screen + enemy_pos, enemy_face, strlen(enemy_face));


		screen[SCREEN_SIZE] = '\0';
		printf("%s\r", screen);

		Sleep(33);

	}
	return 0;


}