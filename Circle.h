#pragma once
#include "Shape.h"
#include "ICircleCollidable.h"

class Circle : public Shape, public ICircleCollidable
{
public:
	Circle(Vector2 position, float speed, float radius, RGB color, std::string name, Vector2 direction) 
		: Shape(position, speed, color, name, direction), _radius(radius) {}
	~Circle() {}

#pragma region Shape Overrides
	void Draw(SDL_Renderer* renderer) override;	
	void Update(float deltaTime) override;
#pragma endregion

#pragma region Interface Overrides
	float GetRadius() const override { return _radius; }

	Vector2 GetPosition() const override { return Shape::GetPosition(); }
	ShapeType GetType() const override { return ShapeType::CIRCLE; }

	void OnCollision(ICollidable& other)override;
#pragma endregion

private:
	float _radius;
};

