#include <SDL.h>
#include "Visualizer.h"
#include "Timer.h"
#include "Rectangle.h"
#include "Pentagon.h"
#include "Circle.h"
#include "CollisionHandler.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	//Visualizer::AddShape(new Pentagon(Vector2(300, 400), 30, RGB(0, 255, 0), "Pentagon 1"));
	//Visualizer::AddShape(new Circle(Vector2(100, 100), 50, RGB(255, 0, 0), "Circle 1"));
	//Rectangle* rec1 = new Rectangle(Vector2(700, 400), Vector2(50, 50), RGB(255, 255, 255), "Square 1", DOWN);
	//Rectangle* rec2 = new Rectangle(Vector2(640, 500), Vector2(50, 50), RGB(255, 255, 255), "Square 2", UP);
	//Circle* circle1 = new Circle(Vector2(700, 400), 25, RGB(255, 0, 0), "Circle 1", RIGHT);
	Circle* circle2 = new Circle(Vector2(200, 100), 50, RGB(255, 0, 0), "Circle 2", RIGHT);
	
	Pentagon* penta1 = new Pentagon(Vector2(450, 100), 50, RGB(0, 255, 0), "Pentagon 1", LEFT);

	
	//Visualizer::AddShape(rec1);
	//Visualizer::AddShape(rec2);
	//Visualizer::AddShape(circle1);
	Visualizer::AddShape(circle2);
	
	Visualizer::AddShape(penta1);
	
	
	//CollisionHandler::AddCollidable(rec1);
	//CollisionHandler::AddCollidable(rec2);
	//CollisionHandler::AddCollidable(circle1);
	CollisionHandler::AddCollidable(circle2);
	CollisionHandler::AddCollidable(penta1);

	

	if (Visualizer::Initialize("Collision System Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false))
	{
		Timer::Initialize(1.0f / 60.0f);
		
		while (Visualizer::IsRunning())
		{
			Visualizer::HandleEvents();
			
			float deltaTime = Timer::GetElapsedTime();
						
			Visualizer::Update(deltaTime);
			
			CollisionHandler::HandleCollisions();

			Visualizer::Render();
			
			//std::cout << Timer::GetFPS() << std::endl;

			Timer::Sleep();
		}		
	}

	Visualizer::Clean();
	
	return 0;
}