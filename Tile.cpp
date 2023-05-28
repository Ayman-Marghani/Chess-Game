#include "Tile.h"

// Constructors
Tile::Tile()
{
    _troop_on_tile = nullptr;
};


Tile::Tile(int x, int y)
{
	_position.setPosition(x, y);
	_troop_on_tile = nullptr;

	_white_protect = 0;
	_black_protect = 0;
}

// Setters
void Tile::setColor(bool color)//true:white, false:black
{
	_color = color;
}

void Tile::setPosition(const Position &position)
{
	_position = position;
}
void Tile::setX_Y(int x, int y) {
    _position.setPosition(x, y);
}

void Tile::setTroopOnTile(Troop* troop)
{
	_troop_on_tile = troop;
    _troop_on_tile->setPosition(_position);
}

void Tile::setToZeroProtect() {
	_white_protect = 0;
	_black_protect = 0;
}

// Getters
Position Tile::getPosition() const
{
	return _position;
}

bool Tile::getColor() const
{
	return _color;
}

int Tile::getWhiteProtect() const
{
	return _white_protect;
}

int Tile::getBlackProtect() const
{
	return _black_protect;
}


Troop* Tile::getTroopOnTile() const
{
	return _troop_on_tile;
}

// Methods
void Tile::removeTroop()
{
_troop_on_tile = nullptr;
}


void Tile::incWhiteProtect()
{
	_white_protect++;
}

void Tile::incBlackProtect()
{
	_black_protect++;
}



bool Tile::promote()
{
	if (_troop_on_tile != nullptr) {
		if (_position.getX() == 0 && _troop_on_tile->getName() == "P") {
			_troop_on_tile->setName("Q");
            return true;
		} else if (_position.getX() == 7 && _troop_on_tile->getName() == "p") {
			_troop_on_tile->setName("q");
            return true;
		}
	}
    return false;
}
//bool Tile::isOccupied()
//{
////	return _troop_on_tile;
//}
