#include "Graveyard.h"


Graveyard::Graveyard()
{
    _score = 0;
}

//Graveyard::~Graveyard() {
// _grave.clear();
//}


int Graveyard::getScore() {return _score;}

void Graveyard::addTroop( Troop *troop)
{
    if(troop != nullptr) {
        _score+=troop->getValue();
        _grave.push_back(troop);
        troop->_alive = false;
    }

}

bool Graveyard::getColor()
{
    return _color;
}


Troop* Graveyard::pop()
{
    Troop *last_elem = _grave.back();
    _grave.pop_back();
    return last_elem;
}

list<Troop*> Graveyard::getGrave(){return _grave;}