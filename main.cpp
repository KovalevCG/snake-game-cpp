#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

bool gameOver;
const int width = 10;
const int height = 10;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
std::string output;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Setup() {
	ShowConsoleCursor(false);
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width + 1;
	fruitY = rand() % height + 1;
	score = 0;
}

void Draw() {
	output = "";
	dir = STOP;
	ClearScreen();

	for (int i = 1; i <= width; i++) output += "#";
	output += "\n";

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) { 
			if (i == y && j == x) {
				output += "0";
			}
			else if (i == fruitY && j == fruitX) {
				output += "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						output += "o";
						print = true;
					}
				}
				if (!print) {
					output += " ";
				}
			}
		}
		output += "\n";
	}

	for (int i = 1; i <= width; i++) {
		output += "#";
	}
	output = output + "\n\nHeight: " + std::to_string(height) + ";    Width: " + std::to_string(width) + "\n";
	output += "X: " + std::to_string(x) + ";    Y: " + std::to_string(y) + "\n";
	output += "fruitX: " + std::to_string(fruitX) + ";    fruitY: " + std::to_string(fruitY) + "\n";
	output += "nTail: " + std::to_string(nTail);
	output += "\ntailX: ";
	for (int i = 0; i < nTail; i++) {
		output += std::to_string(tailX[i]) + " ";
	}
	output += "\ntailY: ";
	for (int i = 0; i < nTail; i++) {
		output += std::to_string(tailY[i]) + " ";
	}
	output += "\nScore: " + std::to_string(score);
	std::cout << output;
	
}

void Input() {
	if (_kbhit()) {
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
		case 'x':
			gameOver = true;
		}
	}
}

void Logic() {
	if (dir != STOP) {
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = x;
		tailY[0] = y;
		for (int i = 1; i < nTail; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}
	}
	switch (dir) {
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x > width || x < 1 || y > height || y < 1) gameOver = true;
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 1;
		fruitX = rand() % width + 1;
		fruitY = rand() % height + 1;
	}
}

int main(){
	Setup();
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		//Sleep(300);
	}
	return 0;
}