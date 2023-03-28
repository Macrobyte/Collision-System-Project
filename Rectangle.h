#pragma once
#include "Shape.h"
#include "ICollidable.h"

class Rectangle : public Shape, public ICollidable
{
public:
	Rectangle(Vector2 position, Vector2 size, RGB color, std::string name, MoveDirection direction) : Shape(position, color, name, direction), _size(size) {}
	~Rectangle() {}
	
#pragma region Getters
	float GetWidth() const { return _size.x; }
	float GetHeight() const { return _size.y; }
	Vector2 GetCenter() const { return Shape::GetPosition() + _size / 2; }
#pragma endregion

#pragma region Shape Overrides
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;
	
#pragma endregion

#pragma region ICollidable Interface Methods
	//std::vector<Vector2> GetVertices() const override;
	//std::vector<Vector2> GetNormals() const override;

	//void OnCollision(const ICollidable& other) const override;
	//bool Collides(const ICollidable& other) const override;
	
#pragma endregion
	
	Vector2 ClosestPoint(const Vector2& point) const;
	
private:
	Vector2 _size;
	
	
	
};

