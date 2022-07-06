#include "game.h"
#include "raylib.h"
#include <vector>
#include <iostream>

Game::Game(int gamemode)
{
	board = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	player1turn = true;

	// top row
	box1 = { 200, 25, 120, 120 };
	box2 = { 340, 25, 120, 120 };
	box3 = { 480, 25, 120, 120 };
	// middle row
	box4 = { 200, 165, 120, 120 };
	box5 = { 340, 165, 120, 120 };
	box6 = { 480, 165, 120, 120 };
	// bottom row
	box7 = { 200, 305, 120, 120 };
	box8 = { 340, 305, 120, 120 };
	box9 = { 480, 305, 120, 120 };

	if (gamemode == 1) singleplayer(true);
	if (gamemode == 2) multiplayer(true);
}

void Game::singleplayer(bool run)
{
	boxesFree = 8;
	gameWon = false;
	makeMove(0);

	while (run && !WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		DrawText("Player 1 (X)", 30, 140, 20, DARKGRAY);
		DrawText("Computer", 30, 170, 18, DARKGRAY);
		DrawText("Player 2 (O)", GetScreenWidth() - 170, 140, 20, DARKGRAY);
		DrawText("You", GetScreenWidth() - 170, 170, 18, DARKGRAY);

		drawBoard();

		if (IsKeyDown(KEY_R) || IsKeyDown(KEY_ESCAPE)) run = false;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !player1turn) makeMove(getBox());
		if (player1turn)
		{
			computerMove();
		}

		if (checkWinner1())
		{
			gameWon = true;
			DrawText("Computer has won!", 170, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}
		if (checkWinner2())
		{
			// not even possible
			gameWon = true;
			DrawText("You have won!", 190, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}
		if (checkDraw())
		{
			gameWon = false;
			DrawText("It's a draw!", 280, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}

		EndDrawing();
	}
}

void Game::multiplayer(bool run)
{
	boxesFree = 9;
	gameWon = false;

	while (run && !WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		DrawText("Player 1 (X)", 30, 140, 20, DARKGRAY);
		DrawText("Player 2 (O)", GetScreenWidth() - 170, 140, 20, DARKGRAY);

		drawBoard();

		if (IsKeyDown(KEY_R) || IsKeyDown(KEY_ESCAPE)) run = false;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) makeMove(getBox());


		if (checkWinner1())
		{
			gameWon = true;
			DrawText("Player 1 has won!", 190, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}
		if (checkWinner2())
		{
			gameWon = true;
			DrawText("Player 2 has won!", 190, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}
		if (checkDraw())
		{
			gameWon = false;
			DrawText("It's a draw!", 280, 100, 50, RED);
			DrawText("Type (R) to return", 260, 160, 35, RED);
		}
		EndDrawing();
	}
}

void Game::drawBoard()
{
	// vertical bars
	DrawRectangle(320, 25, 20, 400, BLACK);
	DrawRectangle(460, 25, 20, 400, BLACK);

	// horizontal bars
	DrawRectangle(200, 145, 400, 20, BLACK);
	DrawRectangle(200, 285, 400, 20, BLACK);

	// draw rects if hovered
	if (CheckCollisionPointRec(GetMousePosition(), box1)) DrawRectangleRec(box1, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box2)) DrawRectangleRec(box2, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box3)) DrawRectangleRec(box3, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box4)) DrawRectangleRec(box4, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box5)) DrawRectangleRec(box5, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box6)) DrawRectangleRec(box6, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box7)) DrawRectangleRec(box7, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box8)) DrawRectangleRec(box8, LIGHTGRAY);
	if (CheckCollisionPointRec(GetMousePosition(), box9)) DrawRectangleRec(box9, LIGHTGRAY);

	// enter values
	// top row
	DrawText(TextFormat("%c", board[0]), 245, 60, 50, BLACK);
	DrawText(TextFormat("%c", board[1]), 385, 60, 50, BLACK);
	DrawText(TextFormat("%c", board[2]), 525, 60, 50, BLACK);
	// middle row
	DrawText(TextFormat("%c", board[3]), 245, 200, 50, BLACK);
	DrawText(TextFormat("%c", board[4]), 385, 200, 50, BLACK);
	DrawText(TextFormat("%c", board[5]), 525, 200, 50, BLACK);
	// bottom row
	DrawText(TextFormat("%c", board[6]), 245, 340, 50, BLACK);
	DrawText(TextFormat("%c", board[7]), 385, 340, 50, BLACK);
	DrawText(TextFormat("%c", board[8]), 525, 340, 50, BLACK);

	return;
}

bool Game::checkDraw()
{
	boxesFree = 0;
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ') boxesFree++;
	}
	if (boxesFree == 0 && !gameWon) return true;
	else return false;
}

bool Game::checkWinner1()
{
	// horizontal
		 if (board[0] == board[1] && board[0] == board[2] && board[0] == 'X') return true;
	else if (board[3] == board[4] && board[3] == board[5] && board[3] == 'X') return true;
	else if (board[6] == board[7] && board[6] == board[8] && board[6] == 'X') return true;
	// vertical
	else if (board[0] == board[3] && board[0] == board[6] && board[0] == 'X') return true;
	else if (board[1] == board[4] && board[1] == board[7] && board[1] == 'X') return true;
	else if (board[2] == board[5] && board[2] == board[8] && board[2] == 'X') return true;
	// diagonal
	else if (board[0] == board[4] && board[0] == board[8] && board[0] == 'X') return true;
	else if (board[2] == board[4] && board[2] == board[6] && board[2] == 'X') return true;
	// else
	else return false;
}

bool Game::checkWinner2()
{
	// horizontal
	if (board[0] == board[1] && board[0] == board[2] && board[0] == 'O') return true;
	else if (board[3] == board[4] && board[3] == board[5] && board[3] == 'O') return true;
	else if (board[6] == board[7] && board[6] == board[8] && board[6] == 'O') return true;
	// vertical
	else if (board[0] == board[3] && board[0] == board[6] && board[0] == 'O') return true;
	else if (board[1] == board[4] && board[1] == board[7] && board[1] == 'O') return true;
	else if (board[2] == board[5] && board[2] == board[8] && board[2] == 'O') return true;
	// diagonal
	else if (board[0] == board[4] && board[0] == board[8] && board[0] == 'O') return true;
	else if (board[2] == board[4] && board[2] == board[6] && board[2] == 'O') return true;
	// else
	else return false;
}

void Game::makeMove(int box)
{
	if (box == 9) return;
	if (board[box] == ' ' && !gameWon)
	{
		if (player1turn)
		{
			board[box] = 'X';
			player1turn = false;
		}
		else
		{
			board[box] = 'O';
			player1turn = true;
		}
	}
	return;
}

int Game::getBox()
{
	if (CheckCollisionPointRec(GetMousePosition(), box1)) return 0;
	else if (CheckCollisionPointRec(GetMousePosition(), box2)) return 1;
	else if (CheckCollisionPointRec(GetMousePosition(), box3)) return 2;
	else if (CheckCollisionPointRec(GetMousePosition(), box4)) return 3;
	else if (CheckCollisionPointRec(GetMousePosition(), box5)) return 4;
	else if (CheckCollisionPointRec(GetMousePosition(), box6)) return 5;
	else if (CheckCollisionPointRec(GetMousePosition(), box7)) return 6;
	else if (CheckCollisionPointRec(GetMousePosition(), box8)) return 7;
	else if (CheckCollisionPointRec(GetMousePosition(), box9)) return 8;
	else return 9;
}

void Game::computerMove()
{
	// vars
	int bestmove = 0;
	int bestscore = -2;
	int score;

	// check possible outcome
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == ' ')
		{
			board[i] = 'X';
			score = minimax(false);
			board[i] = ' ';
			// determines best move to make
			if (score > bestscore)
			{
				bestscore = score;
				bestmove = i;
			}
		}
	}
	// makes move
	makeMove(bestmove);
	return; 
}

int Game::minimax(bool isMaximizing)
{// check return values else go deeper into the game
	if (checkWinner1())
	{
		return 1;
	}
	else if (checkWinner2())
	{
		return -1;
	}
	else if (checkDraw())
	{
		return 0;
	}

	int score;

	// player X
	if (isMaximizing)
	{
		int bestscore = -2;
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == ' ')
			{
				board[i] = 'X';
				score = minimax(false);
				board[i] = ' ';

				if (score > bestscore)
				{
					bestscore = score;
				}
			}
		}
		return bestscore;
	}
	// player O
	else
	{
		int bestscore = 2;
		for (int i = 0; i < 9; i++)
		{
			if (board[i] == ' ')
			{
				board[i] = 'O';
				score = minimax(true);
				board[i] = ' ';

				if (score < bestscore)
				{
					bestscore = score;
				}
			}
		}
		return bestscore;
	}
}