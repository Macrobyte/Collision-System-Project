#include "Circle.h"
#include "Polygon.h"
#include "Visualizer.h"

/// <summary>
/// The circle is drawn using the midpoint circle algorithm, which calculates and draws each pixel of the circle based on its radius and position. 
/// The function sets the renderer draw color to the circle's color before drawing it.
/// </summary>
/// <param name="renderer"></param>
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

/// <summary>
/// This method updates the position of the Circle based on its current velocity and the amount of time that has passed since the last update.
/// </summary>
/// <param name="deltaTime"></param>
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

/// <summary>
/// This method handles handles collision with another ICollidable object. The method checks the type of the colliding object using dynamic_cast to determine if it's a IPolygonCollidable or an ICircleCollidable.
/// </summary>
/// <param name="other"></param>
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





