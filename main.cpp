#include <SDL.h>
#include "Visualizer.h"
#include "Square.h"

int main(int argc, char* argv[])
{

	Shape* square = new Square(Vector2(0, 0), Vector2(800, 600), RGB(255, 0, 0));

	Visualizer::AddShape(square);
	
	std::cout << Visualizer::GetViewport().x + Visualizer::GetViewport().w << std::endl;

	if (Visualizer::Initialize("Collision System Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false))
	{
		std::cout << Visualizer::GetViewport().x + Visualizer::GetViewport().w << std::endl;
		while (Visualizer::IsRunning())
		{
			Visualizer::HandleEvents();
			Visualizer::Render();
		}
	}

	Visualizer::Clean();
	
	return 0;
}