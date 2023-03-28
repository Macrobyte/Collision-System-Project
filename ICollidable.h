#pragma once
#include "Vector2.h"
#include <vector>

enum ShapeType
{
	CIRCLE,
	POLYGON
};

class ICollidable {
public:
	virtual ~ICollidable() {}

	virtual Vector2 GetPosition() const = 0;	

	virtual ShapeType GetType() const = 0;
	
	virtual void OnCollision(const ICollidable& other) const = 0;

private:
	ShapeType _shapeType;
};
