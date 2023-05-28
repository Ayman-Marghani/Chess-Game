#ifndef CHESS_GAME_TILE_H
#define CHESS_GAME_TILE_H

#include "Position.h"
#include"Troop.h"

class Tile
{
private:
	bool _color; //true : white , false: black
	Position _position;
	Troop* _troop_on_tile;

public:
    int _white_protect;
    int _black_protect;

	//Constructors
	Tile();
	Tile(int, int);

	//Setters
	void setColor(bool);
	void setPosition(const Position &position);
    void setX_Y(int x, int y);
	void setToZeroProtect();
    void setTroopOnTile(Troop *);

    //Getters
	Troop* getTroopOnTile() const;
	Position getPosition() const;
	bool getColor() const;
	int getWhiteProtect() const;
	int getBlackProtect() const;

	//Methods
    void incWhiteProtect();
    void incBlackProtect();
	//bool isOccupied();
	bool isProtected();
	void removeTroop();//clears the tile whether it has a troop on it or not

    bool promote();
};

#endif //CHESS_GAME_TILE_H
