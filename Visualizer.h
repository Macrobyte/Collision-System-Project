#pragma once
#include <SDL.h>
#include <vector>
#include "Shape.h"

class Visualizer
{
public:	
	static bool Initialize(const char* title, int x, int y, int width, int height, bool isFullscreen);
	static bool IsRunning() { return _isRunning; }
	static void HandleEvents();
	static void Render();
	static void Update(float deltaTime);
	static void Clean();

	static bool IsOutOfBounds(const Vector2& position, float radius);
	static int GetWidth() { return _width; }
	static int GetHeight() { return _height; }
	
	static void AddShape(Shape* shape);
		
private:	
	static SDL_Window* _window;
	static int _width;
	static int _height;
	static SDL_Renderer* _renderer;
	static bool _isRunning;
		
	static std::vector<Shape*> _shapes;
};

