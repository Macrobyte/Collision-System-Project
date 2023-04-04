#include "Polygon.h"
#include "Circle.h"
#include "Visualizer.h"

void Polygon::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < _vertices.size(); ++i)
	{
		Vector2 start = _vertices[i];
		Vector2 end = _vertices[(i + 1) % _vertices.size()];
		SDL_RenderDrawLine(renderer, (int)start.x, (int)start.y, (int)end.x, (int)end.y);
	}
}

void Polygon::Update(float deltaTime)
{
	UpdateVertices();

	// TEMPORARY WAY OF DOING THIS
	const std::vector<Vector2>& vertices = GetVertices();
	Vector2 center = GetPosition();
	float radius = 0.0f;
	for (const Vector2& vertex : vertices)
	{
		float distance = (vertex - center).magnitude();
		if (distance > radius)
		{
			radius = distance;
		}
	}

	if (Visualizer::IsOutOfBounds(GetPosition(), radius))
	{
		if (GetPosition().x - radius < 0 || GetPosition().x + radius > Visualizer::GetWidth())
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

std::vector<Vector2> Polygon::GetNormals() const
{
	std::vector<Vector2> normals;
	std::vector<Vector2> vertices = GetVertices();

	for (int i = 0; i < vertices.size(); ++i)
	{
		Vector2 edge = vertices[(i + 1) % vertices.size()] - vertices[i];
		Vector2 normal(edge.y, -edge.x);
		normal.normalize();
		normals.push_back(normal);
	}

	return normals;
}

void Polygon::UpdateVertices()
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		_vertices[i] = _originalVertices[i] + GetPosition();
	}
}

void Polygon::OnCollision(ICollidable& other)
{
	if (const IPolygonCollidable* polygon = dynamic_cast<const IPolygonCollidable*>(&other))
	{
		Vector2 collisionNormal = SAT::GetCollisionNormalPolygon(*this, *polygon);

		SetVelocity(GetVelocity().reflect(collisionNormal));
		
		SetPosition(GetPosition() + collisionNormal);
	}
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		//Not yet implemented
	}
}







