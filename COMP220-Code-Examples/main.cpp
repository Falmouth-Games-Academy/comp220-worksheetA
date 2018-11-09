#include "Game.h"

int main(int argc, char ** argsv)
{
	Game* game = new Game();

	Uint64 CurrentFrameTime = 0;
	Uint64 PreviousFrameTime = 0;
	//Event loop, we will loop until running is set to false, usually if escape has been pressed or window is closed
	if (game->init(800, 500) == 0)
	{
		while (game->running)
		{
			CurrentFrameTime = SDL_GetPerformanceCounter();
			game->update((double)((CurrentFrameTime - PreviousFrameTime) * 1000 / 
				(double)SDL_GetPerformanceFrequency()));
			game->render();
			PreviousFrameTime = CurrentFrameTime;
		}
	}
	game->exit();
	return 0;
}