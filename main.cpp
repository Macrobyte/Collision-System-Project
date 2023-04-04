#include <SDL.h>
#include "Visualizer.h"
#include "Time.h"
#include "Circle.h"
#include "Polygon.h"
#include "CollisionHandler.h"
#include "PolygonFactory.h"

const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;

void TestPolygonCollision(float speed)
{
	float shapeSpeed = speed;
	std::vector<Vector2> hexagon = PolygonFactory::CreateHexagon(50);
	std::vector<Vector2> heptagon = PolygonFactory::CreateHeptagon(50);
	std::vector<Vector2> pentagon = PolygonFactory::CreatePentagon(50);
	std::vector<Vector2> nonagon = PolygonFactory::CreateNonagon(50);

	Polygon* poly1 = new Polygon(Vector2(100, 100), shapeSpeed, RGB(255, 100, 100), "Poly 1", Vector2(1, 1), pentagon);
	Polygon* poly2 = new Polygon(Vector2(100, 800), shapeSpeed, RGB(100, 255, 100), "Poly 2", Vector2(1, -1), nonagon);
	Polygon* poly3 = new Polygon(Vector2(1500, 100), shapeSpeed, RGB(100, 100, 255), "Poly 2", Vector2(-1, 1), heptagon);
	Polygon* poly4 = new Polygon(Vector2(1500, 800), shapeSpeed, RGB(255, 255, 100), "Poly 2", Vector2(-1, -1), hexagon);

	Visualizer::AddShape(poly1);
	Visualizer::AddShape(poly2);
	Visualizer::AddShape(poly3);
	Visualizer::AddShape(poly4);

	CollisionHandler::AddCollidable(poly1);
	CollisionHandler::AddCollidable(poly2);
	CollisionHandler::AddCollidable(poly3);
	CollisionHandler::AddCollidable(poly4);
}

void TestCircleCollision(float speed)
{
	float shapeSpeed = speed;
	//Circles for testing. Note: They collide with eachother but not with other polygons
	Circle* circle1 = new Circle(Vector2(100, 350), shapeSpeed, 50, RGB(255, 100, 100), "Circle 1", Vector2(1, 0));
	Circle* circle2 = new Circle(Vector2(700, 400), shapeSpeed, 50, RGB(100, 255, 100), "Circle 2", Vector2(-1, 0));
	Circle* circle3 = new Circle(Vector2(500, 500), shapeSpeed, 50, RGB(100, 100, 255), "Circle 2", Vector2(0, 1));
	Circle* circle4 = new Circle(Vector2(600, 300), shapeSpeed, 50, RGB(255, 255, 100), "Circle 2", Vector2(0,-1));
	 

	Visualizer::AddShape(circle1);
	Visualizer::AddShape(circle2);
	Visualizer::AddShape(circle3);
	Visualizer::AddShape(circle4);

	CollisionHandler::AddCollidable(circle1);
	CollisionHandler::AddCollidable(circle2);
	CollisionHandler::AddCollidable(circle3);
	CollisionHandler::AddCollidable(circle4);
}

int main(int argc, char* argv[])
{
	TestPolygonCollision(200);
	//TestCircleCollision(200);

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