#pragma once
#include "Vector2.h"

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
	
	virtual void OnCollision(ICollidable& other) = 0;
};
