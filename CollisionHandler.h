#pragma once
#include <vector>
#include "ICollidable.h"

class CollisionHandler
{
public:

	static void AddCollidable(ICollidable* collidable);
	
	static void HandleCollisions();
	
private:
	static std::vector<ICollidable*> _collidables;
};

