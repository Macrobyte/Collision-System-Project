#include "Polygon.h"
#include "Circle.h"
#include "Visualizer.h"

/// <summary>
/// This method draws a polygon on a given SDL_Renderer object by iterating through its vertices and drawing lines between them.
/// </summary>
/// <param name="renderer"></param>
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

/// <summary>
/// This method updates the polygon's position based on its current velocity and the amount of time that has passed since the last update. 
/// It first calls the UpdateVertices method to recalculate the positions of the polygon's vertices based on its current position and rotation. 
/// </summary>
/// <param name="deltaTime"></param>
void Polygon::Update(float deltaTime)
{
	UpdateVertices();

	Vector2 newPosition = GetPosition() + GetVelocity() * deltaTime;

	float left = 0.0f;
	float right = Visualizer::GetWidth();
	float top = 0.0f;
	float bottom = Visualizer::GetHeight();

	if (newPosition.x < left)
	{
		newPosition.x = right;
	}
	else if (newPosition.x > right)
	{
		newPosition.x = left;
	}

	if (newPosition.y < top)
	{
		newPosition.y = bottom;
	}
	else if (newPosition.y > bottom)
	{
		newPosition.y = top;
	}

	SetPosition(newPosition);
}

/// <summary>
/// This method returns a vector containing all of the normals for the edges of the polygon. 
/// The normals are calculated by finding the perpendicular vector for each edge of the polygon.
/// This is an IPolygonCollidable method.
/// </summary>
/// <returns>A vector containing all of the normals for the edges of the polygon.</returns>
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

/// <summary>
/// This function updates the polygon's vertices by adding its position to each vertex, effectively translating the polygon to its new position. 
/// It does so by iterating through each vertex in the polygon, retrieving its original position from the _originalVertices vector, and adding the current position to it. 
/// The updated vertices are stored in the _vertices vector.
/// </summary>
void Polygon::UpdateVertices()
{
	for (int i = 0; i < _vertices.size(); ++i)
	{
		_vertices[i] = _originalVertices[i] + GetPosition();
	}
}

/// <summary>
/// This is the OnCollision method of the Polygon class. 
/// It handles collision events with other collidable objects.
/// This is an IPolygonCollidable method.
/// </summary>
/// <param name="other"></param>
void Polygon::OnCollision(ICollidable& other)
{
	if (const IPolygonCollidable* polygon = dynamic_cast<const IPolygonCollidable*>(&other))
	{
		//std::cout << "Polygon collided with polygon" << std::endl;

		Vector2 collisionNormal = SAT::GetCollisionNormalPolygon(*this, *polygon);

		SetPosition(GetPosition() + collisionNormal);
		
		SetVelocity(GetVelocity().reflect(collisionNormal));
	}
	else if (const ICircleCollidable* circle = dynamic_cast<const ICircleCollidable*>(&other))
	{
		//std::cout << "Polygon collided with circle" << std::endl;
	
		Vector2 collisionNormal = SAT::GetCollisionNormalCirclePolygon(*circle, *this);

		float overlap = SAT::GetOverlapCirclePolygon(*circle, *this, collisionNormal);

		Vector2 separationVector = collisionNormal * overlap;
		
		SetPosition(GetPosition() + separationVector + 0.1f);

		SetVelocity(GetVelocity().reflect(collisionNormal));


		//complete this
	}
}







