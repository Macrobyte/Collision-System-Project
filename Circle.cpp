#include "Circle.h"
#include "Polygon.h"
#include "Visualizer.h"

void Circle::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);

	int x = 0;
	int y = _radius;
	int d = 3 - 2 * _radius;

	while (x <= y) {
		// Draw each pixel and its symmetrically opposite pixel
		SDL_RenderDrawPoint(renderer, GetPosition().x + x, GetPosition().y + y);
		SDL_RenderDrawPoint(renderer, GetPosition().x + x, GetPosition().y - y);
		SDL_RenderDrawPoint(renderer, GetPosition().x - x, GetPosition().y + y);
		SDL_RenderDrawPoint(renderer, GetPosition().x - x, GetPosition().y - y);
		SDL_RenderDrawPoint(renderer, GetPosition().x + y, GetPosition().y + x);
		SDL_RenderDrawPoint(renderer, GetPosition().x + y, GetPosition().y - x);
		SDL_RenderDrawPoint(renderer, GetPosition().x - y, GetPosition().y + x);
		SDL_RenderDrawPoint(renderer, GetPosition().x - y, GetPosition().y - x);

		// Update coordinates and decision variable
		if (d < 0) {
			d = d + 4 * x + 6;
		}
		else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}
	
void Circle::Update(float deltaTime)
{
	// TEMPORARY WAY OF DOING THIS
	if (Visualizer::IsOutOfBounds(GetPosition(), GetRadius()))
	{
		if (GetPosition().x - GetRadius() < 0 || GetPosition().x + GetRadius() > Visualizer::GetWidth())
		{
			SetVelocity(GetVelocity().reflect(Vector2::Right()));
		}
		else
		{
			SetVelocity(GetVelocity().reflect(Vector2::Down()));
		}
	}
	// TEMPORARY WAY OF DOING THIS
	
	Vector2 newPosition = GetPosition() + GetVelocity() * deltaTime;
	SetPosition(newPosition);
}


void Circle::OnCollision(ICollidable& other) 
{
	if (const IPolygonCollidable* polygon = dynamic_cast<const IPolygonCollidable*>(&other))
	{
		//Not yet implemented
	}
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		Vector2 collisionNormal = (GetPosition() - circle->GetPosition()).normalize();

		SetVelocity(GetVelocity().reflect(collisionNormal));

		float overlap = (GetRadius() + circle->GetRadius()) - (GetPosition() - circle->GetPosition()).magnitude();
		SetPosition(GetPosition() + collisionNormal * overlap);

	}
}





