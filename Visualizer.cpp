#include "Visualizer.h"
#include "ConsoleUtilities.h"

SDL_Window* Visualizer::_window = nullptr;
SDL_Renderer* Visualizer::_renderer = nullptr;
bool Visualizer::_isRunning = false;
std::vector<Shape*> Visualizer::_shapes = std::vector<Shape*>();

bool Visualizer::Initialize(const char* title, int x, int y, int width, int height, bool isFullscreen)
{
	CUtils::LogWarning("Initializing Visualizer...");

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        Uint32 flag = 0;
        if(isFullscreen)
			flag = SDL_WINDOW_FULLSCREEN;
        
		if (!(_window = SDL_CreateWindow(title, x, y, width, height, flag)))
			CUtils::LogError("Failed to create Window. Error: ", SDL_GetError());
        else
            if (!(_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED)))
                CUtils::LogError("Failed to create Renderer. Error: ", SDL_GetError());
    }
    else
    {
        CUtils::LogError("Failed to initialize SDL. Error: ", SDL_GetError());
    }
    
	CUtils::LogColor("Visualizer initialized.", CUtils::GREEN);

	return _isRunning = true;   		
}

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
		default:
			break;
		}
	}
}

void Visualizer::Render()
{
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderClear(_renderer);

	for (std::vector<Shape*>::size_type i = 0; i != _shapes.size(); i++)
	{
		_shapes[i]->Draw(_renderer);
	}

	SDL_RenderPresent(_renderer);
}

void Visualizer::Clean()
{
	CUtils::LogWarning("Cleaning Visualizer...");
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Visualizer::AddShape(Shape* shape)
{
	_shapes.push_back(shape);
}
