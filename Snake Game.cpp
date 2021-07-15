#include <iostream>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include <time.h>

#define MAXSNAKESIZE 100
#define MAXFRAMEX 119
#define MAXFRAMEY 29

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

class Point {
	private:
		int x;
		int y;
	public:
		Point() {
			x = y = 10;
		}
		Point(int x, int y) {
			this->x = x;
			this->y = y;
		}
		
		void SetPoint(int x, int y) {			
			this->x = x;
			this->y = y;
		}
		int GetX() {
			return x;
		}
		int GetY() {
			return y;
		}
		void MoveUp() {
			y--;
			if (y < 0) {
				y = MAXFRAMEY;
			}
		}
		void MoveDown() {
			y++;
			if (y > MAXFRAMEY) {
				y = 0;
			}
		}
		void MoveRight() {
			x++;
			if (x > MAXFRAMEX) {
				x = 0;
			}
		}
		void MoveLeft() {
			x--;
			if (x < 0) {
				x = MAXFRAMEX;
			}
		}
		void Draw(char item) {
			gotoxy(x, y);
			cout << item;
		}
		void Earse() {
			gotoxy(x, y);
			cout << " ";
		}
		void CopyPos(Point * p) {
			p->x = x;
			p->y = y;
		}
		int IsEqual(Point* p) {
			if (p->x == x && p->y == y) {
				return 1;
			}
			return 0;
		}
		void Debug() {
			cout << "(" << x << ", " << y << ")";
		}
};


class Snake {
	private:
		Point* cell[MAXSNAKESIZE];
		int size;
		char dir;
		Point fruit;
		int isAlive;
	public:
		Snake() {
			size = 1;
			cell[0] = new Point(10, 10);
			for (int i = 1; i < MAXSNAKESIZE; i++) {
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			isAlive = 1;
		}

		void AddCell(int x, int y) {
			cell[size++] = new Point(x, y);
		}
		
		void TurnUp() {
			if (dir != 's') {				
				dir = 'w';
			}
		}
		void TurnDown() {  
			if (dir != 'w') {	
				dir = 's';
			}
		}
		void TurnRight() {
			if (dir != 'a') {	
				dir = 'd';
			}
		}
		void TurnLeft() {
			if (dir != 'd') {	
				dir = 'a';
			}
		}
		
		void Move() {	
			system("cls");
			
			if (!isAlive) {
				cout << "THUA roi leu leu :P\n";
				cout << "Diem cua ban: " << (size-1)*10 << "\n";
				cout << "Ban co muon choi lai?";
				getch();
				isAlive = 1;
				size = 1;
			}
			
			for (int i=size-1; i>0; i--) {
				cell[i-1]->CopyPos(cell[i]);
			}
			
			switch(dir) {
				case 'w':
					cell[0]->MoveUp();
					break;
				case 's':
					cell[0]->MoveDown();
					break;
				case 'd':
					cell[0]->MoveRight();
					break;
				case 'a':
					cell[0]->MoveLeft();
					break;
			}
			
			if (SelfCollision()) {
				isAlive = 0;
			}
			
			if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
				AddCell(0, 0);
				fruit.SetPoint(rand()%MAXFRAMEX, rand()%MAXFRAMEY);
			}
			
			for (int i = 0; i < size; i++) {
				cell[i]->Draw('*');
			}
			fruit.Draw('O');			
			
			Sleep(10);
		}
		
		int SelfCollision() {
			for (int i=1; i<size; i++) {
				if (cell[0]->IsEqual(cell[i])) {
					return 1;
				}
			}
			return 0;
		}
		
		void Debug() {			
			for (int i = 0; i < size; i++) {
				cell[i]->Debug();
			}
		}
	
};


int main(){
	srand((unsigned)time(NULL));
	Snake snake;
	char key = 's';
	do {
		if (kbhit()) {
			key = getch();
		}
		switch(key) {
			case 'w':
			case 'W':
				snake.TurnUp();
				break;
			case 'S':
			case 's':
				snake.TurnDown();
				break;
			case 'd':
			case 'D':
				snake.TurnRight();
				break;
			case 'a':
			case 'A':
				snake.TurnLeft();
				break;
		}
		snake.Move();
	} while (key != 'q');
	
	return 0;
}