#include "Visualizer.h"
#include "VUtils.h"

SDL_Window* Visualizer::_window = nullptr;
SDL_Renderer* Visualizer::_renderer = nullptr;
bool Visualizer::_isRunning = false;
std::vector<Shape*> Visualizer::_shapes = std::vector<Shape*>();
int  Visualizer::_width = 0;
int  Visualizer::_height = 0;

/// <summary>
/// This is a function that initializes a window and renderer using the SDL library for visualization. 
/// The function takes in a title, x, y, width, height, and isFullscreen as arguments.
/// </summary>
/// <param name="title"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="isFullscreen"></param>
/// <returns>The function sets _isRunning to true and returns it. </returns>
bool Visualizer::Initialize(const char* title, int x, int y, int width, int height, bool isFullscreen)
{
	VUtils::LogWarning("Initializing Visualizer...");
	
	_width = width;
	_height = height;

	
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        Uint32 flag = 0;
        if(isFullscreen)
			flag = SDL_WINDOW_FULLSCREEN;
        
		if (!(_window = SDL_CreateWindow(title, x, y, _width, _height, flag)))
			VUtils::LogError("Failed to create Window. Error: ", SDL_GetError());
        else
            if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)))
                VUtils::LogError("Failed to create Renderer. Error: ", SDL_GetError());
    }
    else
    {
        VUtils::LogError("Failed to initialize SDL. Error: ", SDL_GetError());
    }  

	VUtils::LogColor("Visualizer initialized.", VUtils::GREEN);

	return _isRunning = true;   		
}

/// <summary>
/// This is a function that handles events such as key presses, mouse clicks, etc.
/// It first creates an SDL_Event object and then calls SDL_PollEvent to check for events.
/// </summary>
void Visualizer::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				_isRunning = false;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

/// <summary>
/// This function is responsible for rendering the shapes added to the Visualizer object. 
/// It first sets the background color to black using SDL_SetRenderDrawColor, then clears the renderer using SDL_RenderClear.
/// It loops through all the shapes added to the _shapes vector and calls their Draw() function, passing in the renderer object as a parameter. 
/// Finally, it presents the rendered objects on the screen using SDL_RenderPresent.
/// </summary>
void Visualizer::Render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255); //Sets background color
	
	SDL_RenderClear(_renderer);
	

	for (size_t i = 0; i < _shapes.size(); i++)
	{
		_shapes[i]->Draw(_renderer);
	}

	SDL_RenderPresent(_renderer);
}

/// <summary>
/// This function is responsible for updating the shapes added to the Visualizer object.
/// </summary>
/// <param name="deltaTime"></param>
void Visualizer::Update(float deltaTime)
{
	for (size_t i = 0; i < _shapes.size(); i++)
	{
		_shapes[i]->Update(deltaTime);
	}
}

/// <summary>
/// This function is responsible for cleaning up the Visualizer object.
/// </summary>
void Visualizer::Clean()
{
	VUtils::LogWarning("Cleaning Visualizer...");
	
	SDL_DestroyWindow(_window);
	
	SDL_DestroyRenderer(_renderer);
	
	SDL_Quit();
}

/// <summary>
/// This function checks if a given position is out of bounds, based on the dimensions of the Visualizer window and a given radius. 
/// </summary>
/// <param name="position"></param>
/// <param name="radius"></param>
/// <returns>It returns a boolean value indicating if the position is out of bounds.</returns>
bool Visualizer::IsOutOfBounds(const Vector2& position, float radius)
{
	const float left = 0.0f + radius;
	const float right = _width - radius;
	const float top = 0.0f + radius;
	const float bottom = _height - radius;

	return (position.x < left || position.x > right || position.y < top || position.y > bottom);
}

/// <summary>
/// This function adds shapes to a list in the Vizualizer.
/// </summary>
/// <param name="shape"></param>
void Visualizer::AddShape(Shape* shape)
{
	_shapes.push_back(shape);
}

