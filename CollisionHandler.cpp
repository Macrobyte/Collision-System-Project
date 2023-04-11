#include "CollisionHandler.h"
#include "SAT.h"

std::vector<ICollidable*> CollisionHandler::_collidables = std::vector<ICollidable*>();

/// <summary>
/// This function adds a new ICollidable object to the list of collidables managed by the CollisionHandler. 
/// The ICollidable object represents an object in the simulation that can collide with other objects. 
/// The object is added to the end of the _collidables vector, which stores pointers to all of the collidables.
/// </summary>
/// <param name="collidable"></param>
void CollisionHandler::AddCollidable(ICollidable* collidable)
{
	_collidables.push_back(collidable);
}

/// <summary>
/// This function handles collisions between the collidables in the _collidables vector. 
/// It does this by iterating over all pairs of collidables and checking their types to determine which collision detection algorithm to use.
/// In this case SAT (Separating Axis Theorem)
/// </summary>
void CollisionHandler::HandleCollisions()
{
    for (size_t i = 0; i < _collidables.size(); ++i) {
        for (size_t j = i + 1; j < _collidables.size(); ++j) {
            if (_collidables[i]->GetType() == POLYGON && _collidables[j]->GetType() == POLYGON) {
                if (SAT::PolygonPolygonCollision(*static_cast<IPolygonCollidable*>(_collidables[i]), *static_cast<IPolygonCollidable*>(_collidables[j]))){
                    _collidables[i]->OnCollision(*_collidables[j]);
                    _collidables[j]->OnCollision(*_collidables[i]);
                }
            }
            else if (_collidables[i]->GetType() == CIRCLE && _collidables[j]->GetType() == CIRCLE) {
                if (SAT::CircleCircleCollision(*static_cast<ICircleCollidable*>(_collidables[i]), *static_cast<ICircleCollidable*>(_collidables[j]))) {
                    _collidables[i]->OnCollision(*_collidables[j]);
                    _collidables[j]->OnCollision(*_collidables[i]);
                }
            }
            else if (_collidables[i]->GetType() == POLYGON && _collidables[j]->GetType() == CIRCLE) {
                if (SAT::PolygonCircleCollision(*static_cast<IPolygonCollidable*>(_collidables[i]), *static_cast<ICircleCollidable*>(_collidables[j]))) {
                    _collidables[i]->OnCollision(*_collidables[j]);
                    _collidables[j]->OnCollision(*_collidables[i]);
                }
            }
            else if (_collidables[i]->GetType() == CIRCLE && _collidables[j]->GetType() == POLYGON) {
                if (SAT::PolygonCircleCollision(*static_cast<IPolygonCollidable*>(_collidables[j]), *static_cast<ICircleCollidable*>(_collidables[i]))) {
					_collidables[i]->OnCollision(*_collidables[j]);
					_collidables[j]->OnCollision(*_collidables[i]);
				}
            }
        }
    }
}
