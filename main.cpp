#include "raylib.h"
#include "game.h"

int main()
{
	int screenWidth = 800;
	int screenHeight = 450;
	bool gameActive = false;

	InitWindow(screenWidth, screenHeight, "Tic Tac Toe");

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(WHITE);

		DrawText("Do you want to play singleplayer or multiplayer?", 160, 80, 20, LIGHTGRAY);
		DrawText("Tap (S) for singleplayer and (M) for multiplayer", 160, 110, 20, LIGHTGRAY);

		EndDrawing();

		if (IsKeyPressed(KEY_S) && !gameActive) Game game(1);
		if (IsKeyPressed(KEY_M) && !gameActive) Game game(2);
	}

	CloseWindow();

	return 0;
}