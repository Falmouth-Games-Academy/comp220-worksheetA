#include "stdafx.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Game * pGame = new Game();

	pGame->initialise();
	pGame->getShaders();
	pGame->loop();

	return 0;
}