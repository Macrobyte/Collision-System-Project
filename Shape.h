#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include "Vector2.h"

struct RGB
{
    RGB() : r(0), g(0), b(0) {}
    RGB(int r, int g, int b) : r(r), g(g), b(b) {}
    int r;
    int g;
    int b;    
};

enum ShapeType
{
    RECTANGLE,
    CIRCLE,
    PENTAGON
};

enum MoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Shape
{
public:
    Shape(ShapeType type, Vector2 position, RGB color, std::string name, MoveDirection direction) : _type(type), _position(position), _color(color), _name(name), _moveDirection(direction) {}
    virtual ~Shape() {}

	ShapeType GetType() const { return _type; }
	
    Vector2 GetPosition() const { return _position; }
    void SetPosition(Vector2 position) { _position = position; }

	RGB GetColor() const { return _color; }
	void SetColor(const RGB& color) { _color = color; }

    std::string GetName() const { return _name; }

	MoveDirection GetMoveDirection() const { return _moveDirection; }
	void SetMoveDirection(MoveDirection direction) { _moveDirection = direction; }
    
    virtual void Draw(SDL_Renderer* renderer) = 0;
    virtual void Update(float deltaTime) = 0;
private:
    ShapeType _type; 
    Vector2 _position;
	RGB _color; 
	std::string _name;
    std::vector<Vector2> _vertices;
    
	MoveDirection _moveDirection;
};

