#include "Pentagon.h"
#include "Circle.h"
#include "Rectangle.h"

#pragma region Shape Overrides
void Pentagon::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, GetColor().r, GetColor().g, GetColor().b, SDL_ALPHA_OPAQUE);

	//std::vector<Vector2> vertices = GetVertices();
	/*for (int i = 0; i < vertices.size(); ++i)
	{
		SDL_RenderDrawLine(renderer,
			(int)vertices[i].x, (int)vertices[i].y,
			vertices[(static_cast<unsigned long long>(i) + 1) % vertices.size()].x, vertices[(static_cast<unsigned long long>(i) + 1) % vertices.size()].y);
	}*/
}

//void Pentagon::Update(float deltaTime)
//{
//	switch (GetMoveDirection())
//	{
//	case MoveDirection::LEFT:
//		SetPosition(GetPosition() + Vector2(-50, 0) * deltaTime);
//		break;
//	case MoveDirection::RIGHT:
//		SetPosition(GetPosition() + Vector2(50, 0) * deltaTime);
//		break;
//	case MoveDirection::UP:
//		SetPosition(GetPosition() + Vector2(0, -50) * deltaTime);
//		break;
//	case MoveDirection::DOWN:
//		SetPosition(GetPosition() + Vector2(0, 50) * deltaTime);
//		break;
//	default:
//		break;
//	}
//}
#pragma endregion

#pragma region ICollidable Interface Methods
//std::vector<Vector2> Pentagon::GetVertices() const
//{
//	std::vector<Vector2> vertices;
//	const int numSide = 5;
//	const float angleIncrement = 2 * M_PI / numSide;
//	for (int i = 0; i < numSide; ++i) //++i
//	{
//		float angle = i * angleIncrement + M_PI / 2.0f;
//		Vector2 vertex = Vector2(GetPosition().x + _radius * cos(angle),
//			GetPosition().y + _radius * sin(angle));
//		vertices.push_back(vertex);
//	}
//	return vertices;
//}
//
//std::vector<Vector2> Pentagon::GetNormals() const
//{
//	std::vector<Vector2> normals;
//	std::vector<Vector2> vertices = GetVertices();
//	for (int i = 0; i < vertices.size(); ++i)
//	{
//		Vector2 edge = vertices[(static_cast<unsigned long long>(i) + 1) % vertices.size()] - vertices[i];
//		Vector2 normal = Vector2(-edge.y, edge.x);
//		normal.normalize();
//		normals.push_back(normal);
//	}
//	return normals;
//}
//
//void Pentagon::OnCollision(const ICollidable& other) const
//{
//	// Try to cast the other object to a Rectangle
//	const Rectangle* rectangle = dynamic_cast<const Rectangle*>(&other);
//	if (rectangle != nullptr) {
//
//		std::cout << this->GetName() << " collided with " << rectangle->GetName() << std::endl;
//	}
//
//	// Try to cast the other object to a Circle
//	const Circle* circle = dynamic_cast<const Circle*>(&other);
//	if (circle != nullptr) {
//
//		std::cout << this->GetName() << " collided with " << circle->GetName() << std::endl;
//
//		return;
//	}
//
//	// Try to cast the other object to a Pentagon
//	const Pentagon* pentagon = dynamic_cast<const Pentagon*>(&other);
//	if (pentagon != nullptr) {
//
//		//std::cout << this->GetName() << " collided with " << pentagon->GetName() << std::endl;
//
//		return;
//	}
//}
//
//bool Pentagon::Collides(const ICollidable& other) const
//{
//	return false;
//}
#pragma endregion



