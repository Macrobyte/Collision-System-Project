#include "Polygon.h"
#include "Circle.h"

void Polygon::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < _vertices.size(); ++i)
	{
		Vector2 start = _vertices[i] + GetPosition();
		Vector2 end = _vertices[(i + 1) % _vertices.size()] + GetPosition();
		SDL_RenderDrawLine(renderer, (int)start.x, (int)start.y, (int)end.x, (int)end.y);
	}
}

void Polygon::Update(float deltaTime)
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

std::vector<Vector2> Polygon::GetVertices() const
{
	return _vertices;
}

std::vector<Vector2> Polygon::GetNormals() const
{
	std::vector<Vector2> normals;
	std::vector<Vector2> vertices = GetVertices();

	for (int i = 0; i < vertices.size(); ++i)
	{
		Vector2 edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		Vector2 normal(-edge.y, edge.x);
		normal.normalize();
		normals.push_back(normal);
	}

	return normals;
}

Vector2 Polygon::GetPosition() const
{
	return Shape::GetPosition();
}

ShapeType Polygon::GetType() const
{
	return ShapeType::POLYGON;
}

void Polygon::OnCollision(const ICollidable& other) const
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
