#include "Square.h"

void Square::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { (int)GetPosition().x, (int)GetPosition().y, (int)GetSize().x, (int)GetSize().y };
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rect);
}
