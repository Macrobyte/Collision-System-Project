#pragma once
#include "Shape.h"
#include "ICircleCollidable.h"

class Circle : public Shape, public ICircleCollidable
{
public:
	Circle(Vector2 position, float radius, RGB color, std::string name, MoveDirection direction) : Shape(position, color, name, direction), _radius(radius) {}
	~Circle() {}

#pragma region Shape Overrides
	void Draw(SDL_Renderer* renderer) override;	
	void Update(float deltaTime) override;
	
#pragma endregion

#pragma region Interface Methods
	float GetRadius() const override;

	Vector2 GetPosition() const override;
	ShapeType GetType() const override;

	void OnCollision(const ICollidable& other) const override;	
#pragma endregion

private:
	float _radius;
};

