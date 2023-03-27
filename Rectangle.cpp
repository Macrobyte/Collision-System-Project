#include "Rectangle.h"
#include "Pentagon.h"
#include "Circle.h"
#include "VUtils.h"

#pragma region Shape Overrides
void Rectangle::Draw(SDL_Renderer* renderer)
{
	SDL_Rect rect = { (int)GetPosition().x, (int)GetPosition().y, (int)_size.x, (int)_size.y };
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect);
}

void Rectangle::Update(float deltaTime)
{
	switch (GetMoveDirection())
	{
	case MoveDirection::LEFT:
		SetPosition(GetPosition() + Vector2(-50, 0) * deltaTime);
		break;
	case MoveDirection::RIGHT:
		SetPosition(GetPosition() + Vector2(50, 0) * deltaTime);
		break;
	case MoveDirection::UP:
		SetPosition(GetPosition() + Vector2(0, -50) * deltaTime);
		break;
	case MoveDirection::DOWN:
		SetPosition(GetPosition() + Vector2(0, 50) * deltaTime);
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region ICollidable Interface Methods
std::vector<Vector2> Rectangle::GetVertices() const
{
	std::vector<Vector2> vertices;
	vertices.push_back(GetPosition() - _size / 2);
	vertices.push_back(GetPosition() + Vector2(_size.x / 2, -_size.y) / 2);
	vertices.push_back(GetPosition() + _size / 2);
	vertices.push_back(GetPosition() + Vector2(-_size.x / 2, _size.y) / 2);
	return vertices;
}

std::vector<Vector2> Rectangle::GetNormals() const
{
	std::vector<Vector2> normals;
	normals.push_back(Vector2(0, 1));//up //TODO add normals to vector
	normals.push_back(Vector2(1, 0));//right
	return normals;
}

std::pair<float, float> Rectangle::ProjectOntoAxis(const Vector2& axis, float& min, float& max) const
{
	std::vector<Vector2> vertices = GetVertices();
	min = max = vertices[0].dot(axis);
	for (int i = 1; i < vertices.size(); i++) {
		float projection = vertices[i].dot(axis);
		min = (std::min)(min, projection);
		max = (std::max)(max, projection);
	}

	return std::make_pair(min, max);
}

void Rectangle::OnCollision(const ICollidable& other) const
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

bool Rectangle::Collides(const ICollidable& other) const
{
	return false;
}
#pragma endregion


Vector2 Rectangle::ClosestPoint(const Vector2& point) const
{
	// Calculate the point's position relative to the rectangle's center
	Vector2 diff = point - GetCenter();

	// Calculate the half-widths and half-heights of the rectangle
	float halfWidth = GetWidth() / 2.0f;
	float halfHeight = GetHeight() / 2.0f;

	// Clamp the point to the edges of the rectangle
	float x = VUtils::clamp(diff.x, -halfWidth, halfWidth);
	float y = VUtils::clamp(diff.y, -halfHeight, halfHeight);

	// Return the closest point on the rectangle
	return GetCenter() + Vector2(x, y);
}
