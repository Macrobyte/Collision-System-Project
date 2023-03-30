#include <SDL.h>
#include "Visualizer.h"
#include "Time.h"
#include "Circle.h"
#include "Polygon.h"
#include "CollisionHandler.h"
#include "PolygonFactory.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	float shapeSpeed = 50;
	std::vector<Vector2> squareVertices = PolygonFactory::CreateSquare(50);
	std::vector<Vector2> triangle = PolygonFactory::CreateTriangle(50);
	std::vector<Vector2> pentagon = PolygonFactory::CreatePentagon(50);
	std::vector<Vector2> nonagon = PolygonFactory::CreateNonagon(50);
	std::vector<Vector2> decagon = PolygonFactory::CreateDecagon(50);
	std::vector<Vector2> megagon = PolygonFactory::CreateMegagon(1);
	
	
	Polygon* poly1 = new Polygon(Vector2(0, 350), shapeSpeed, RGB(255, 255, 255), "Poly 1", Vector2(1,0), pentagon);
	Circle* circle1 = new Circle(Vector2(700, 400), shapeSpeed, 50, RGB(255, 255, 255), "Circle 1", Vector2(-1, 0));
	
	Visualizer::AddShape(poly1);
	Visualizer::AddShape(circle1);
	
	CollisionHandler::AddCollidable(poly1);
	CollisionHandler::AddCollidable(circle1);

	if (Visualizer::Initialize("Collision System Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false))
	{
		Time::Initialize(1.0f / 60.0f);
		
		while (Visualizer::IsRunning())
		{
			Visualizer::HandleEvents();
						
			Visualizer::Update(Time::DeltaTime());
			
			CollisionHandler::HandleCollisions();

			Visualizer::Render();

			Time::Sleep();
		}		
	}

	Visualizer::Clean();
	
	return 0;
}