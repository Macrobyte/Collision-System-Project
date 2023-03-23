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
	static void Clean();
	
	static void AddShape(Shape* shape);
	
	static SDL_Rect GetViewport() { return _viewport; }
	
	
private:	
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;
	static int _width;
	static int _height;
	static SDL_Rect _viewport;
	static bool _isRunning;
	
	static std::vector<Shape*> _shapes;
};

