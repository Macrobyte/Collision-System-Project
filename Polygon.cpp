#include "Polygon.h"
#include "Circle.h"

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
	// Check if the other object is a polygon
	if (const IPolygonCollidable* polygon = dynamic_cast<const IPolygonCollidable*>(&other))
	{
		// Get the collision normal
		Vector2 collisionNormal = SAT::GetCollisionNormalPolygon(*this, *polygon);

		SetVelocity(GetVelocity().reflect(collisionNormal));
		
		// Move polygon out of collision
		SetPosition(GetPosition() + collisionNormal );
	}
	// Check if the other object is a circle
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		// Get the collision normal
		Vector2 collisionNormal = SAT::GetCollisionNormalCirclePolygon(*circle, *this);

		SetVelocity(GetVelocity().reflect(collisionNormal));

		// Move circle out of collision
		SetPosition(GetPosition() + collisionNormal * SAT::GetOverlapCirclePolygon(*circle, *this, collisionNormal));
		
	}
}







