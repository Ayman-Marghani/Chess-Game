#pragma once

using namespace std;

#ifndef CHESS_GAME_TROOP_H
#define CHESS_GAME_TROOP_H

#include <bits/stdc++.h>
#include "Position.h"

class Troop
{
private:
	string _name;
	bool _color;
	Position _position;
//	int _value; // value of the piece
public:
    vector<Troop*> attackers;

	vector<Position> _all_possible; // All possible moves that can be made by a piece (such that the square is in the board and the there's no piece from the same color on it and you can raech it)
	vector<Position> _all_protected; // All protected pieces
	vector<Position> _all_legal;
    vector<Position> _all_valid_if_checked;

    bool _alive;
    bool _first_move;
    int num_moves;
    // ON which round the pawn plays it's first move
    int move_when_first_move;

	//Constructors
	Troop();
    Troop(const string& name, bool color, const Position& position);

    // Destructor
//    ~Troop();

	//Setters
	void setColor(bool color);

	void setName(const string& name);

	void setPosition(const Position &position);

//	void setValue(int value);

	//Getters
	bool getColor() const;

	string getName() const;

	Position getPosition() const;

	int getValue() const;

    bool getCross() const;

    bool getDiagonal() const;

	//Methods
    bool foundInLegal(int x,int y);

    bool foundInLegalIfChecked(int x,int y);

    // void kill();
    //bool canPromote();
    //bool canEnpassant();
};

#endif //CHESS_GAME_TROOP_H
