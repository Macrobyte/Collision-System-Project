#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "SAT.h"
#include "Vector2.h"

struct RGB
{
    RGB() : r(0), g(0), b(0) {}
    RGB(int r, int g, int b) : r(r), g(g), b(b) {}
    int r;
    int g;
    int b;    
};

class Shape
{
public:
    Shape(Vector2 position, float speed, RGB color, std::string name, Vector2 direction)
        : _position(position), _velocity(speed * direction), _color(color), _name(name), _moveDirection(direction) {}
    virtual ~Shape() {}
	
    Vector2 GetPosition() const { return _position; }
    virtual void SetPosition(Vector2 position) { _position = position; }

    RGB GetColor() const { return _color; }
    virtual void SetColor(const RGB& color) { _color = color; }

    std::string GetName() const { return _name; }

    Vector2 GetMoveDirection() const { return _moveDirection; }
	void SetMoveDirection(Vector2 direction) { _moveDirection = direction; }

    void SetVelocity(Vector2 velocity) {
        _velocity = velocity;
        _moveDirection = _velocity.normalized();
    }

    Vector2 GetVelocity() const {
        return _velocity;
    }
    
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void Update(float deltaTime) = 0;
private: 
    Vector2 _position;
    Vector2  _velocity;
	Vector2 _moveDirection;
	RGB _color;
    
	std::string _name;
    
};

