#pragma once
#include "Shape.h"
#include "IPolygonCollidable.h"

class Polygon : public Shape, public IPolygonCollidable
{
public:
	Polygon(Vector2 position, RGB color, std::string name, MoveDirection direction, std::vector<Vector2> vertices) : Shape(position, color, name, direction), _vertices(vertices) {}
	~Polygon() {}

#pragma region Shape Overrides
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;

#pragma endregion

#pragma region Interface Methods
	std::vector<Vector2> GetVertices() const override;
    std::vector<Vector2> GetNormals() const override;

	Vector2 GetPosition() const override;
	ShapeType GetType() const override;

	void OnCollision(const ICollidable& other) const override;
#pragma endregion
private:
	std::vector<Vector2> _vertices;

};

