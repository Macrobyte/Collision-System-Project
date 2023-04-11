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
	
	Vector2 newPosition = GetPosition() + GetVelocity() * deltaTime;

	// Check if the circle has gone beyond the left or right edges of the screen
	if (newPosition.x < -GetRadius())
	{
		newPosition.x = Visualizer::GetWidth() + GetRadius();
	}
	else if (newPosition.x > Visualizer::GetWidth() + GetRadius())
	{
		newPosition.x = -GetRadius();
	}

	// Check if the circle has gone beyond the top or bottom edges of the screen
	if (newPosition.y < -GetRadius())
	{
		newPosition.y = Visualizer::GetHeight() + GetRadius();
	}
	else if (newPosition.y > Visualizer::GetHeight() + GetRadius())
	{
		newPosition.y = -GetRadius();
	}

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
		//std::cout << "Circle collided with polygon" << std::endl;
		
		Vector2 collisionNormal = SAT::GetCollisionNormalCirclePolygon(*this, *polygon);

		float overlap = SAT::GetOverlapCirclePolygon(*this, *polygon, collisionNormal);

		SetPosition(GetPosition() + collisionNormal * overlap + 0.1f);

		SetVelocity(GetVelocity().reflect(collisionNormal));
		
	}
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		//std::cout << "Circle collided with circle" << std::endl;

		Vector2 collisionNormal = (GetPosition() - circle->GetPosition()).normalize();

		float overlap = (GetRadius() + circle->GetRadius()) - (GetPosition() - circle->GetPosition()).magnitude();

		SetPosition(GetPosition() + collisionNormal * overlap);

		SetVelocity(GetVelocity().reflect(collisionNormal));
	}
}





