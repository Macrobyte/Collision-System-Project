#include "Circle.h"
#include "Polygon.h"

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
	Vector2 newPosition = GetPosition() + GetVelocity() * deltaTime;
	SetPosition(newPosition);
}


void Circle::OnCollision(ICollidable& other) 
{
	
	// Check if the other object is a polygon
	if (const IPolygonCollidable* polygon = dynamic_cast<const IPolygonCollidable*>(&other))
	{
		// Get the collision normal
		Vector2 collisionNormal = SAT::GetCollisionNormalCirclePolygon(*this, *polygon);

		SetVelocity(GetVelocity().reflect(collisionNormal));

		// Move the polygon out of the collision
		SetPosition(GetPosition() + collisionNormal );
	}
	// Check if the other object is a circle
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		// Get the collision normal
		Vector2 collisionNormal = (GetPosition() - circle->GetPosition()).normalize();

		SetVelocity(GetVelocity().reflect(collisionNormal));

		// Move the circle out of the collision
		float overlap = (GetRadius() + circle->GetRadius()) - (GetPosition() - circle->GetPosition()).magnitude();
		SetPosition(GetPosition() + collisionNormal * overlap);

	}
}





