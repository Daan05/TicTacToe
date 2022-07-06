#pragma once

#include "raylib.h"
#include <vector>

class Game
{
public:

	Game(int gamemode);

	void singleplayer(bool run);

	void multiplayer(bool run);

	void drawBoard();

	bool checkWinner1();

	bool checkWinner2();

	bool checkDraw();

	void makeMove(int box);

	int getBox();

	void computerMove();

	int minimax(bool isMaximizing);

private:

	int boxesFree;
	bool player1turn;
	std::vector<char> board;
	bool gameWon;

	// top row
	Rectangle box1;
	Rectangle box2;
	Rectangle box3;
	// middle row
	Rectangle box4;
	Rectangle box5;
	Rectangle box6;
	// bottom row
	Rectangle box7;
	Rectangle box8;
	Rectangle box9;
};
