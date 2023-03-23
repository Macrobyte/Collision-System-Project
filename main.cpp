#include <SDL.h>
#include "Visualizer.h"
#include "Square.h"

int main(int argc, char* argv[])
{

	Visualizer::AddShape(new Square(Vector2(100, 100), Vector2(100, 100), RGB(255, 255, 0)));
	
	if (Visualizer::Initialize("Collision System Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
	{
		while (Visualizer::IsRunning())
		{
			Visualizer::HandleEvents();
			Visualizer::Render();
		}
	}

	Visualizer::Clean();
	
	return 0;
}