#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
//
// Variables
//
bool gameOver;
const int width = 10;
const int height = 6;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;
std::string output;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
//
// Clear Screen Function
//
void ClearScreen()
{
	COORD cursorPosition;	cursorPosition.X = 0;	cursorPosition.Y = 0;	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
//
// Turn Off Cursor Visibility Function
//
void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
//
// Geme Setup
//
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
//
// Draw Screen Loop
//
void Draw() {
	// String Output Screen Variable
	output = "";
	// dir = STOP;
	ClearScreen();
	// Draw top row
	for (int i = 1; i <= width; i++) output += "#";
	output += "\n";
	// Draw Game
	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width + 1; j++) {
			// Draw Snake Head
			if (i == y && j == x) {
				output += "0";
			}
			// Draw Right Wall
			else if (j == width + 1) output += "|";
			// Draw Fruit
			else if (i == fruitY && j == fruitX) {
				output += "@";
			}
			// Draw Tail
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						output += "o";
						print = true;
					}
				}
				// Draw Empty Space
				if (!print) {
					output += " ";
				}
			}
		}
		output += "\n";
	}

	// Draw Last Row
	for (int i = 1; i <= width; i++) {
		output += "#";
	}
	// Draw Game Score
	output += "\n\nScore: -= " + std::to_string(score) + " =-";
	// Draw Additional Info
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
	std::cout << output;
}
//
// Keyboard Input Loop
//
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
//
// Game Logic Loop
//

// Tail
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
	// Set Direction of Movement
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
	// Move though walls X
	if (x > width)
		x = 1;
	else if (x < 1)
		x = width;
	// Y
	if (y > height)
		y = 1;
	else if (y < 1)
		y = height;
	// Collision with Tail
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
	}
	// If fruit eaten than:
	if (x == fruitX && y == fruitY) {
		nTail++;
		score += 1;
		fruitX = rand() % width + 1;
		fruitY = rand() % height + 1;
	}
}
//
// Snake Game
//
int main(){
	Setup();
	while (!gameOver) {
		Draw();
		Sleep(500);
		Input();
		Logic();
	}
	return 0;
}