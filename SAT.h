#pragma once
#include <vector>
#include "ICollidable.h"
#include "Circle.h"

class SAT {
public:
	static bool Collides(const ICollidable& shape1, const ICollidable& shape2);
	
private:
	static void ProjectOntoAxis(const Vector2& axis, const std::vector<Vector2>& vertices, float& min, float& max);
	
	
	
	static float dot(const Vector2& a, const Vector2& b) {
		return a.x * b.x + a.y * b.y;
	}
};