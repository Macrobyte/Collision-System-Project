#pragma once
#include "Shape.h"
#include "ICollidable.h"

class Pentagon : public Shape, public ICollidable
{
public:
    Pentagon( Vector2 position, float radius, RGB color, std::string name, MoveDirection direction) : Shape(ShapeType::PENTAGON, position, color, name, direction), _radius(radius) {};
	~Pentagon() {}
	
#pragma region Getters
	float GetRadius() const { return _radius; }

#pragma endregion
	
#pragma region Shape Overrides
    void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;
	
#pragma endregion

#pragma region Interface Methods
	std::vector<Vector2> GetVertices() const override;
	std::vector<Vector2> GetNormals() const override;
	
	void OnCollision(const ICollidable& other) const override;
	bool Collides(const ICollidable& other) const override;
	
#pragma endregion

private:
    float _radius;
};

