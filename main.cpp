#include <SDL.h>
#include "Visualizer.h"
#include "Timer.h"
#include "Circle.h"
#include "Polygon.h"
#include "CollisionHandler.h"
#include "PolygonFactory.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	Polygon* poly1 = new Polygon(Vector2(100, 100), RGB(255, 255, 255), "Poly 1", RIGHT, PolygonFactory::CreateSquare(200));
	Polygon* poly2 = new Polygon(Vector2(500, 100), RGB(255, 255, 255), "Poly 2", LEFT, PolygonFactory::CreateSquare(200));
	//Circle* circle1 = new Circle(Vector2(100, 100), 50, RGB(255, 255, 255), "Circle 1", RIGHT);
	//Circle* circle2 = new Circle(Vector2(500, 100), 50, RGB(255, 255, 255), "Circle 2", LEFT);
	
	Visualizer::AddShape(poly1);
	Visualizer::AddShape(poly2);
	//Visualizer::AddShape(circle1);
	//Visualizer::AddShape(circle2);
	
	CollisionHandler::AddCollidable(poly1);
	CollisionHandler::AddCollidable(poly2);
	//CollisionHandler::AddCollidable(circle1);
	//CollisionHandler::AddCollidable(circle2);

	

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