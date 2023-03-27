#include "Circle.h"
#include "Rectangle.h"
#include "Pentagon.h"

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
		SetPosition(GetPosition() + Vector2(0, 0) * deltaTime);
		break;
	case MoveDirection::RIGHT:
		SetPosition(GetPosition() + Vector2(0, 0) * deltaTime);
		break;
	case MoveDirection::UP:
		SetPosition(GetPosition() + Vector2(0, 0) * deltaTime);
		break;
	case MoveDirection::DOWN:
		SetPosition(GetPosition() + Vector2(0, 0) * deltaTime);
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region ICollidable Interface Methods
std::vector<Vector2> Circle::GetVertices() const
{
	return std::vector<Vector2>();
}

std::vector<Vector2> Circle::GetNormals() const
{
	return std::vector<Vector2>();
}

void Circle::OnCollision(const ICollidable& other) const
{
	// Try to cast the other object to a Rectangle
	const Rectangle* rectangle = dynamic_cast<const Rectangle*>(&other);
	if (rectangle != nullptr) {

		std::cout << this->GetName() << " collided with " << rectangle->GetName() << std::endl;
	}

	// Try to cast the other object to a Circle
	const Circle* circle = dynamic_cast<const Circle*>(&other);
	if (circle != nullptr) {

		std::cout << this->GetName() << " collided with " << circle->GetName() << std::endl;
		return;
	}

	// Try to cast the other object to a Pentagon
	const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
	if (pentagon != nullptr) {

		std::cout << this->GetName() << " collided with " << pentagon->GetName() << std::endl;

		return;
	}

}

bool Circle::Collides(const ICollidable& other) const
{
	const Circle* circle = dynamic_cast<const Circle*>(&other);
	if (circle != nullptr) {

		float distance = (GetPosition() - circle->GetPosition()).magnitude();
		float radiusSum = _radius + circle->GetRadius();

		return distance < radiusSum;
	}

	const Rectangle* rectangle = dynamic_cast<const Rectangle*>(&other);
	if (rectangle != nullptr)
	{
		Vector2 closestPoint = rectangle->ClosestPoint(GetPosition());

		float distance = (GetPosition() - closestPoint).magnitude();

		return distance < _radius;
	}

	const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
	if (pentagon != nullptr)
	{
		std::vector<Vector2> vertices = other.GetVertices();
		std::vector<Vector2> normals = other.GetNormals();

		Vector2 center = GetPosition();

		// Check if the circle overlaps with any of the polygon's edges
		for (int i = 0; i < vertices.size(); i++) {
			Vector2 v1 = vertices[i];
			Vector2 v2 = vertices[(i + 1) % vertices.size()];

			// Calculate the normal of the current edge
			Vector2 edge = v2 - v1;
			Vector2 normal = Vector2(-edge.y, edge.x).normalize();

			float t = (center - v1).dot(normal) / normal.magnitude_squared();
			Vector2 projection = v1 + edge * t;

			// Calculate the distance between the center of the circle and the current edge
			float distance = (center - projection).magnitude();

			//std::cout << "Distance: " << distance << std::endl;

			// If the distance is greater than the radius of the circle, the shapes do not collide
			if (distance > _radius) {
				continue;
			}
			else
			{
				return true;
			}
		}

		// Check if the circle overlaps with any of the polygon's corners
		for (const auto& vertex : vertices) {
			if ((vertex - center).magnitude_squared() < _radius * _radius) {
				return true;
			}
		}

		// Check if the circle overlaps with any of the polygon's edges
		for (const auto& normal : normals) {
			std::vector<float> polygonProjections;
			for (const auto& vertex : vertices) {
				float projection = vertex.dot(normal);
				polygonProjections.push_back(projection);
			}
			float circleProjection = center.dot(normal);

			float minPolygonProjection = *std::min_element(polygonProjections.begin(), polygonProjections.end());
			float maxPolygonProjection = *std::max_element(polygonProjections.begin(), polygonProjections.end());
			float minCircleProjection = circleProjection - _radius;
			float maxCircleProjection = circleProjection + _radius;

			if (maxPolygonProjection < minCircleProjection || maxCircleProjection < minPolygonProjection) {
				continue;
			}
		}

		return false;
	}

	return false;
}
#pragma endregion





