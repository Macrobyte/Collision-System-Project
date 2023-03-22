#include <SDL.h>
#include <iostream>
#include "Vector2.h"
#include "ConsoleUtilities.h"

using namespace CUtils;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window;

	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		SDL_Log("Could not create window: %s", SDL_GetError());
		return 1;
	}

	LogWarning("This is a warning message.");

	SDL_Delay(3000);

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}