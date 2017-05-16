#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <Windows.h>
#include <conio.h>

#define SCREEN_SIZE		79

using namespace std;

class GameObject {
	char 	shape[16];
	int		pos;

public:
	GameObject(const char *shape, int pos) : pos(pos) { strcpy(this->shape, shape); }
	
	void SetShape(const char *shape) { strcpy(this->shape, shape); }

	void SetPos(int pos) { this->pos = pos; }
	int  GetPos() const { return this->pos; }

	void IncreasePos() { this->pos++; }
	void DecreasePos() { this->pos--; }	

	void Draw(char *canvas) const
	{
		if (pos < 0 || pos >= SCREEN_SIZE) return;

		strncpy(canvas + pos, shape, strlen(shape) );
	}
};

class Bullet {
	GameObject  myData;
	bool 		isFired;
	GameObject* target;

	void reset() { isFired = false; }

public:
	Bullet() : isFired(false), myData( ">", 0), target(nullptr) {}

	void Fire(const GameObject& player, GameObject& enemy)
	{ 
		int player_pos = player.GetPos();
		int target_pos = enemy.GetPos();
		
		if (player_pos == target_pos) return;

		if (player_pos < target_pos) {
			myData.SetShape(">");
		} else {			
			myData.SetShape("<");
		}

		SetPos( player_pos );
		target = &enemy;
		isFired = true;
	}

	void SetPos(int pos) { myData.SetPos(pos); }
	int GetPos() const { return myData.GetPos(); }

	void IncreasePos() { myData.IncreasePos(); }
	void DecreasePos() { myData.DecreasePos(); }

	bool IsFired() { return isFired; }

	void Update()
	{
		if (isFired == false || !target) return;

		int pos = myData.GetPos();
		int target_pos = target->GetPos();

		if (pos < 0 || pos >= SCREEN_SIZE)
		{
			reset();
			return;
		}

		if (pos == target_pos) 
		{
			reset();
			return;
		}

		if (pos < target_pos) {
			IncreasePos();
		} else {
			DecreasePos();
		}
	}	

	void Draw(char *canvas) const
	{
		if (isFired == false || target == nullptr) return;

		myData.Draw(canvas);
	}
};

void clear_screen(char *canvas)
{
	memset(canvas, ' ', SCREEN_SIZE);
	canvas[SCREEN_SIZE] = '\0';
}

void process_input(GameObject& player, GameObject& enemy, Bullet bullets[], int bullets_len)
{
	if (_kbhit() == 0) return;

	int ch = _getch();
	if (ch == 224)
	{
		ch = _getch();
		switch (ch)
		{
		case 75:
			player.IncreasePos();
			break;
		case 77:
			player.DecreasePos();
			break;
		case 72:
			enemy.IncreasePos();
			break;
		case 80:
			enemy.DecreasePos();
			break;
		}
	}
	else if (ch == ' ')
	{
		for (int i = 0; i < bullets_len; i++)
		{
			if (bullets[i].IsFired() == false)
			{
				bullets[i].Fire(player, enemy);
				break; // exit from for statement
			}
		}
	}
}

void draw(char *canvas, const GameObject& player, const GameObject& enemy, const Bullet bullets[], int bullets_len)
{
	if (canvas == NULL) return;

	player.Draw(canvas);
	enemy.Draw(canvas);
	for (int i= 0; i < bullets_len; i++)
	{
		bullets[i].Draw(canvas);
	}
}

void update(const GameObject& player, const GameObject& enemy, Bullet bullets[], int bullets_len)
{
	for (int i = 0; i < bullets_len; i++)
	{
		bullets[i].Update();
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
	GameObject player("^_^", rand() % SCREEN_SIZE);	
	GameObject enemy("*_*", rand() % SCREEN_SIZE);	
	const int bullets_len = 30;
	Bullet bullets[bullets_len];

	while (1)
	{
		clear_screen(canvas);
		process_input(player, enemy, bullets, bullets_len);
		draw(canvas, player, enemy, bullets, bullets_len);
		update(player, enemy, bullets, bullets_len);
		render(canvas);
	}
	return 0;
}