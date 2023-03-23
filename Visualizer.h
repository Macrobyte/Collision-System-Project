#pragma once
#include <SDL.h>
#include "Shape.h"
#include <vector>

class Visualizer
{
public:	
	static bool Initialize(const char* title, int x, int y, int width, int height, bool isFullscreen);
	static void HandleEvents();
	static void Render();
	static void Clean();
	
	static void AddShape(Shape* shape);
	

	
	static bool IsRunning() { return _isRunning; }
	
private:	
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	static bool _isRunning;
	
	static std::vector<Shape*> _shapes;
};

