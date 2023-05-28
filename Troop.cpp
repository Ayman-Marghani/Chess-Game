#include "Troop.h"

// Constructors
Troop::Troop() = default;

Troop::Troop(const string& name, bool color, const Position& position)
{
    _name = name;
    _color = color;
    _position = position;
    _first_move = true;
    _alive = true;
    num_moves = 0;

}

// Destructor
//Troop::~Troop() {
// attackers.clear();
// _all_possible.clear();
// _all_protected.clear();
// _all_legal.clear();
// _all_valid_if_checked.clear();
//}

// Setters
void Troop::setColor(bool color)
{
	_color = color;
}

void Troop::setName(const string& name)
{
	_name = name;
}

void Troop::setPosition(const Position &position)
{
	_position = position;
}

//void Troop::setValue(int value)
//{
//	_value = value;
//}

// Getters
string Troop::getName() const
{
	return _name;
}

bool Troop::getColor() const
{
	return _color;
}

Position Troop::getPosition() const
{
	return _position;
}

int Troop::getValue() const
{
	if(std::tolower(_name[0]) == 'p'){return 1;}
    else if(std::tolower(_name[0]) == 'n'){return 3;}
    else if(std::tolower(_name[0]) == 'b'){return 3;}
    else if(std::tolower(_name[0]) == 'r'){return 5;}
    else if(std::tolower(_name[0]) == 'q'){return 9;}
    else if(std::tolower(_name[0]) == 'k'){return -1;}
    return 0;

}

bool Troop::getCross() const
{
    return tolower(_name[0]) == 'q' || tolower(_name[0]) == 'r';
}
bool Troop::getDiagonal() const
{
    return tolower(_name[0]) == 'q' || tolower(_name[0]) == 'b';
}

// Methods
//void Troop::kill()
//{
//}

bool Troop::foundInLegal(int x,int y)
{
    int sz = _all_legal.size();
    for(int i = 0; i < sz; i++)
    {
        if(_all_legal[i].getX() == x && _all_legal[i].getY() == y){
            return true;
        }
    }
    return false;
}

bool Troop::foundInLegalIfChecked(int x,int y)
{
    int sz = _all_valid_if_checked.size();
    for(int i = 0; i < sz; i++)
    {
        if(_all_valid_if_checked[i].getX() == x && _all_valid_if_checked[i].getY() == y){
            return true;
        }
    }
    return false;
}


