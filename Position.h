//
// Created by yasso on 4/27/2023.
//

#ifndef CHESS_GAME_POSITION_H
#define CHESS_GAME_POSITION_H

#include<bits/stdc++.h>

using namespace std;


class Position
{
private:
	int _x, _y;
	string _position;
public:
	Position();

	void setPosition(int, int);

	string getPosition(void);

	int getX();

	int getY();

    bool operator==(const Position& other) const;
};


#endif //CHESS_GAME_POSITION_H
