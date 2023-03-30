#include "Circle.h"
#include "Polygon.h"

#pragma region Shape Overrides
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
	switch (GetMoveDirection())
	{
	case MoveDirection::LEFT:
		SetPosition(GetPosition() + Vector2(-100, 0) * deltaTime);
		break;
	case MoveDirection::RIGHT:
		SetPosition(GetPosition() + Vector2(100, 0) * deltaTime);
		break;
	case MoveDirection::UP:
		SetPosition(GetPosition() + Vector2(0, 100) * deltaTime);
		break;
	case MoveDirection::DOWN:
		SetPosition(GetPosition() + Vector2(0, -100) * deltaTime);
		break;
	default:
		break;
	}
}

#pragma endregion

#pragma region ICollidable Interface Methods
float Circle::GetRadius() const
{
	return _radius;
}

Vector2 Circle::GetPosition() const
{
	return Shape::GetPosition();
}

ShapeType Circle::GetType() const
{
	return ShapeType::CIRCLE;
}

void Circle::OnCollision(const ICollidable& other) const
{
	const Polygon* polygon = dynamic_cast<const Polygon*>(&other);
	if (polygon != nullptr)
	{
		std::cout << this->GetName() << " collided with " << polygon->GetName() << std::endl;
	}

	const Circle* circle = dynamic_cast<const Circle*>(&other);
	if (circle != nullptr)
	{
		std::cout << this->GetName() << " collided with " << circle->GetName() << std::endl;
	}
}
#pragma endregion





