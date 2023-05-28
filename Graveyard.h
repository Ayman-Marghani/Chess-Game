#include <iostream>
#include <vector>
#include "Troop.h"
#pragma once
class Graveyard
{
private:
    int _score;
public:
    //Add troop to grave
    Graveyard();
    list<Troop*> _grave;
    bool _color;
//    ~Graveyard();
    void addTroop( Troop* troop);
    list<Troop*> getGrave();
    bool getColor();
    int getScore();
    Troop* pop();
};