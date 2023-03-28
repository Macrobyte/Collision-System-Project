#pragma once
#include "ICollidable.h"

class ICircleCollidable : public ICollidable
{
public:
	virtual ~ICircleCollidable() {}

	virtual float GetRadius() const = 0;
};

