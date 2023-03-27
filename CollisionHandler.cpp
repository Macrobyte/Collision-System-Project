#include "CollisionHandler.h"
#include "SAT.h"

std::vector<ICollidable*> CollisionHandler::_collidables = std::vector<ICollidable*>();


void CollisionHandler::AddCollidable(ICollidable* collidable)
{
	_collidables.push_back(collidable);
}

void CollisionHandler::HandleCollisions()
{
	for (size_t i = 0; i < _collidables.size(); ++i) {
		for (size_t j = i + 1; j < _collidables.size(); ++j) {
			if (SAT::Collides(*_collidables[i], *_collidables[j])) {
				_collidables[i]->OnCollision(*_collidables[j]);
				_collidables[j]->OnCollision(*_collidables[i]);
			}
		}
	}
}
