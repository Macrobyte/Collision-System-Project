#pragma once
#include "ICollidable.h"

class IPolygonCollidable : public ICollidable
{
public:
	virtual ~IPolygonCollidable() {}

	virtual std::vector<Vector2> GetVertices() const = 0;

	virtual std::vector<Vector2> GetNormals() const = 0;
};

