#include "stdafx.h"
#include "Game.h"

int main(int argc, char *argv[])
{
	Game * pGame = new Game();

	pGame->Initialise();
	pGame->LoadingScene();
	pGame->Loop();

	return 0;
}