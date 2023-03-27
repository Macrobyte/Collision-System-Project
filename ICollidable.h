#pragma once
#include "Vector2.h"

class ICollidable {
public:
	virtual ~ICollidable() {}
	
	virtual std::vector<Vector2> GetVertices() const = 0;
	
	virtual std::vector<Vector2> GetNormals() const = 0;
	
	virtual std::pair<float, float> ProjectOntoAxis(const Vector2& axis, float& min, float& max) const = 0;
	
	virtual void OnCollision(const ICollidable& other) const = 0;
	
	virtual bool Collides(const ICollidable& other) const = 0;
};
