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
            if (_collidables[i]->GetType() == POLYGON && _collidables[j]->GetType() == POLYGON) {
                if (SAT::PolygonPolygonCollision(*dynamic_cast<IPolygonCollidable*>(_collidables[i]), *dynamic_cast<IPolygonCollidable*>(_collidables[j]))){
                    _collidables[i]->OnCollision(*_collidables[j]);
                    _collidables[j]->OnCollision(*_collidables[i]);
                }
            }
            else if (_collidables[i]->GetType() == CIRCLE && _collidables[j]->GetType() == CIRCLE) {
                if (SAT::CircleCircleCollision(*dynamic_cast<ICircleCollidable*>(_collidables[i]), *dynamic_cast<ICircleCollidable*>(_collidables[j]))) {
                    _collidables[i]->OnCollision(*_collidables[j]);
                    _collidables[j]->OnCollision(*_collidables[i]);
                }
            }


            
            // Check for collision between a polygon and a circle
            //if (_collidables[i]->GetType() == POLYGON && _collidables[j]->GetType() == CIRCLE) {
            //    if (SAT::PolygonCircleCollision(*dynamic_cast<IPolygonCollidable*>(_collidables[i]), *dynamic_cast<ICircleCollidable*>(_collidables[j]))) {
            //        _collidables[i]->OnCollision(*_collidables[j]);
            //        _collidables[j]->OnCollision(*_collidables[i]);
            //    }
            //}
            //else if (_collidables[i]->GetType() == CIRCLE && _collidables[j]->GetType() == POLYGON) {
            //    if (SAT::PolygonCircleCollision(*dynamic_cast<IPolygonCollidable*>(_collidables[j]), *dynamic_cast<ICircleCollidable*>(_collidables[i]))) {
            //        _collidables[i]->OnCollision(*_collidables[j]);
            //        _collidables[j]->OnCollision(*_collidables[i]);
            //    }
            //}
            //// Check for collision between two polygons
            //else if (_collidables[i]->GetType() == POLYGON && _collidables[j]->GetType() == POLYGON) {
            //    if (SAT::PolygonPolygonCollision(*dynamic_cast<IPolygonCollidable*>(_collidables[i]), *dynamic_cast<IPolygonCollidable*>(_collidables[j]))) {
            //        _collidables[i]->OnCollision(*_collidables[j]);
            //        _collidables[j]->OnCollision(*_collidables[i]);
            //    }
            //}
        }
    }
}
