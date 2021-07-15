#include <iostream>
#include <conio.h>
#include <windows.h>
#include <direct.h>
#include <time.h>

#define MAXSNAKESIZE 100

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
		}
		void MoveDown() {
			y++;
		}
		void MoveRight() {
			x++;
		}
		void MoveLeft() {
			x--;
		}
		void Draw() {
			gotoxy(x, y);
			cout << "*";
		}
		void Earse() {
			gotoxy(x, y);
			cout << " ";
		}
		void CopyPos(Point * p) {
			p->x = x;
			p->y = y;
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
	public:
		Snake() {
			size = 1;
			cell[0] = new Point(10, 10);
			for (int i = 1; i < MAXSNAKESIZE; i++) {
				cell[i] = NULL;
			}
			fruit.SetPoint(rand()%50, rand()%25);
		}

		void AddCell(int x, int y) {
			cell[size++] = new Point(x, y);
		}
		
		void TurnUp() {
			dir = 'w';
		}
		void TurnDown() {
			dir = 's';
		}
		void TurnRight() {
			dir = 'd';
		}
		void TurnLeft() {
			dir = 'a';
		}
		
		void Move() {	
			system("cls");
			
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
			
			if (fruit.GetX() == cell[0]->GetX() && fruit.GetY() == cell[0]->GetY()) {
				AddCell(0, 0);
				fruit.SetPoint(rand()%50, rand()%25);	
			}
			
			for (int i = 0; i < size; i++) {
				cell[i]->Draw();
			}
			fruit.Draw();			
			
			Sleep(50);
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