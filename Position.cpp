//
// Created by yasso on 4/27/2023.
//

#include "Position.h"

Position::Position() = default;

void Position::setPosition(int x, int y)
{
	_x = x;
	_y = y;
	_position = to_string(char(97 + y)) + to_string(1 + x); // 'a' = 97
}

int Position::getX()
{
	return _x;
}

int Position::getY()
{
	return _y;
}
string Position::getPosition()
{
	return _position;
}

bool Position::operator==(const Position& other) const {
    return _x == other._x && _y == other._y;
}