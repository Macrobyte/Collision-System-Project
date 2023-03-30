#pragma once
#include "Shape.h"
#include "IPolygonCollidable.h"

class Polygon : public Shape, public IPolygonCollidable
{
public:
	Polygon(Vector2 position, float speed, RGB color, std::string name, Vector2 direction, std::vector<Vector2> vertices)
		: Shape(position, speed, color, name, direction), _vertices(vertices), _originalVertices(vertices) { UpdateVertices(); }
	~Polygon() {}

#pragma region Shape Overrides
	void Draw(SDL_Renderer* renderer) override;
	void Update(float deltaTime) override;
#pragma endregion

#pragma region Interface Overrides
	std::vector<Vector2> GetVertices() const override { return _vertices; }
    std::vector<Vector2> GetNormals() const override;
	
	void SetPosition(Vector2 position) override { Shape::SetPosition(position); UpdateVertices(); }
	Vector2 GetPosition() const override { return Shape::GetPosition(); }
	ShapeType GetType() const  override { return ShapeType::POLYGON; }

	void OnCollision(ICollidable& other) override;
#pragma endregion
	
private:
	std::vector<Vector2> _vertices;
	std::vector<Vector2> _originalVertices;
	void UpdateVertices();
};

