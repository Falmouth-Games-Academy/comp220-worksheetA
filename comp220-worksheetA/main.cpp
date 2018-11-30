//main.cpp - defines the entry point of the application

#include "main.h"

int main(int argc, char* args[])
{
	// Game class gets called in
	GraphicsApplication game;

	// GameLoop function runs the game
	game.gameLoop();

	// Return 0 ends the application once gameloop has finished
	return 0;
}