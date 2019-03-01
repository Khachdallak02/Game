#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <conio.h>
using namespace std;

bool gameOver = false;
bool realgameOver = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width/2 - 1;
	y = height/2 -1;
	fruitX = rand() % (width-2)+1;
	fruitY = rand() % (height-2)+1;
	score = 0;
}

void Draw() {
	system("cls");
	if (gameOver){
		cout << "GAME OVER!!!" << endl;
		cout << "Final Score: " << score << endl;
		system("pause");
	}
	else{

		for (int i = 0; i <= width; ++i) cout << "#";
		cout << endl;
		bool flag = false;
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (!j || j == width - 1)
					cout << '#';
				if (i == (x) && j == (y)){
					if (y < height -1){
						cout << '@';
						flag = true;
					}
				}
				else if (i == fruitX && j == fruitY)
					cout << 'F';
				else {
					bool print = false;
					for (int k = 0; k < nTail; ++k) {
						if (tailX[k] == i && tailY[k] == j) {
							cout << 'o';
							print = true;
						}
					}
					if (!print) cout << ' ';
				}
			}
			cout << endl;
		}
		if (!flag) gameOver = true;
		for (int i = 0; i <= width; ++i) cout << "#";
		cout << endl;
		cout << "Score: " << score << endl;
	}
}
void Input() {
	if (_kbhit())
		{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case '`':
			gameOver = true;
			break;
		}
	}
}

void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x; tailY[0] = y;
	for (int i = 1; i < nTail; ++i) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		--y;
		break;
	case RIGHT:
		++y;
		break;
	case UP:
		--x;
		break;
	case DOWN:
		++x;
		break;
	}

	if (x > width || x < 0 || y > (height) || y < 0) 
		gameOver = true;

	for (int i = 0; i < nTail; ++i) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		srand(time(false));
		fruitX = rand() % (width-2)+1;
		fruitY = rand() % (height-2)+1;
		++nTail;
	}
}
void STG(){	gameOver ? realgameOver = true : realgameOver;}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	Setup();
	do{ STG(); Input(); Logic(); Draw(); } while (!realgameOver);
	return 0;
}