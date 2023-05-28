//
// Created by yasso on 4/27/2023.
//

#include "Board.h"

Board::Board()
{
	GenerateTiles();
}

pair<int, int> Board::strToIndices(string pos)
{
	pair<int, int> index;
	index.first = pos[0] - 'a';
	index.second = pos[1] - '1';

	return index;
}

void Board::whiteProtect(int i, int j, int is_protect)
{
//	pair<bool, int> pair1 = _board[i][j].getWhiteProtect();
//	pair1.second += is_protect;
//	if (pair1.second == 0)
//	{
//		pair1.first = false;
//	}
//
//	_board[i][j].setWhiteProtect(pair1);
}

void Board::blackProtect(int i, int j, int is_protect)
{
//	int pair1 = _board[i][j].getBlackProtect();
//	pair1 += is_protect;
//
//	_board[i][j].setBlackProtect(pair1);
}

void Board::GenerateTiles()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			Tile tile(i,j);
			if ((i + j) % 2 == 0)
			{
				tile.setColor(false);
			}
			else
			{ tile.setColor(true); }

			_board[i][j] = tile;
		}
	}
}

//bool Board::enPassantMove(Position from, Position to) {
//    if (to.getY() != from.getY() && _board[to.getX()][to.getY()].getTroopOnTile() == nullptr) {
//        return true;
//    }
//    return false;
//}

void Board::move(Position from, Position to)
{
    Move last_move;

    //bool is_enpassant = false;

    Troop * killed = _board[to.getX()][to.getY()].getTroopOnTile();
    if (_board[from.getX()][from.getY()].getTroopOnTile() != nullptr)//Check if from tile has a troop first.
    {
//        if (tolower(_board[from.getX()][from.getY()].getTroopOnTile()->getName()[0]) == 'p') {
//            cout << "pawwwwn\n";
//            is_enpassant = enPassantMove(from, to);
//        }
//        cout << "enpassant: " << is_enpassant << '\n';
//        int coff;
//
//        if (is_enpassant) {
//
//            if (_board[from.getX()][from.getY()].getTroopOnTile()->getColor()) {
//                cout << "white\n";
//                coff = 1;
//            }
//            else {
//                cout << "black\n";
//                coff = -1;
//            }
//            to.setPosition(to.getX()+coff, to.getY());
//
//            killed = _board[to.getX()][to.getY()].getTroopOnTile();
//        }


        //cout << killed << " ||| " << _board[to.getX()][to.getY()].getTroopOnTile() << '\n';

        if (killed != nullptr)//Check if the to tile does have a troop.
        {
            if (killed->getName() == "K" || killed->getName() == "k") {
            }
            //If the color of the troop is different, kill the to troop, Otherwise do nothing.
            if (_board[to.getX()][to.getY()].getTroopOnTile()->getColor() !=
                _board[from.getX()][from.getY()].getTroopOnTile()->getColor())
            {
                killed->_alive = false;
                //Kills, moves the from troop to the to_tile, then removes the from troop.
                _board[to.getX()][to.getY()].removeTroop();

//                if (is_enpassant) _board[to.getX()-coff][to.getY()].setTroopOnTile(_board[from.getX()][from.getY()].getTroopOnTile());
                _board[to.getX()][to.getY()].setTroopOnTile(_board[from.getX()][from.getY()].getTroopOnTile());
                _board[from.getX()][from.getY()].getTroopOnTile()->_first_move = false;
                _board[from.getX()][from.getY()].removeTroop();
            }
        }
            //If the to tile doesn't have a troop, just move the troop.
        else
        {

            Troop *from_troop = _board[from.getX()][from.getY()].getTroopOnTile();

            int i;
            if(from_troop->getColor())
                i = 7;
            else
                i = 0;

            if(from_troop->getName()=="k" || from_troop->getName()=="K" )
            {
                // if the king has attackers
                if (from_troop->attackers.size()) {
                    last_move.is_last_move_check = true;
                }
                if(to.getX()==i && game_mode_on_board != 'c')
                {
                    if(to.getY() == 2 && from_troop->_first_move)
                    {
                        _board[i][3].setTroopOnTile(_board[i][0].getTroopOnTile());
                        _board[i][3].getTroopOnTile()->_first_move = false;
                        _board[i][3].getTroopOnTile()->num_moves++;
                        _board[i][0].removeTroop();
                    }
                    else if (to.getY() == 6 && from_troop->_first_move)
                    {
                        _board[i][5].setTroopOnTile(_board[i][7].getTroopOnTile());
                        _board[i][5].getTroopOnTile()->_first_move = false;
                        _board[i][5].getTroopOnTile()->num_moves++;
                        _board[i][7].removeTroop();
                    }
                    last_move.is_last_move_castling = true;
                }

                _board[to.getX()][to.getY()].setTroopOnTile(_board[from.getX()][from.getY()].getTroopOnTile());
                _board[from.getX()][from.getY()].getTroopOnTile()->_first_move = false;
                _board[from.getX()][from.getY()].getTroopOnTile()->num_moves++;
                _board[from.getX()][from.getY()].removeTroop();
            }
            else{
            _board[to.getX()][to.getY()].setTroopOnTile(_board[from.getX()][from.getY()].getTroopOnTile());//If the color of the troop is the same, kill the to troop.
            _board[from.getX()][from.getY()].getTroopOnTile()->_first_move = false;
            _board[from.getX()][from.getY()].getTroopOnTile()->num_moves++;
            _board[from.getX()][from.getY()].removeTroop();
            }
        }
    }

    last_move.last_move = {from,to};
    last_move.killed_last_move = killed;
    last_move_stack.push(last_move);

    if (killed != nullptr) {
        if (killed->getColor()) {
            _white_grave.addTroop(killed);
        } else {
            _black_grave.addTroop(killed);
        }

    }
}

bool Board::undoMove() {
    Position from,to;
    if(last_move_stack.size()) {
        Move last_move = last_move_stack.top();
        last_move_stack.pop();
        to = last_move.last_move.first;
        from = last_move.last_move.second;
        Troop *troop = _board[from.getX()][from.getY()].getTroopOnTile();

        if (last_move.is_last_move_castling && tolower(troop->getName()[0]) == 'k' && game_mode_on_board != 'c') {
            int i;
            if (troop->getColor())
                i = 7;
            else
                i = 0;

            if (from.getY() == 2) {

                    _board[i][0].setTroopOnTile(_board[i][3].getTroopOnTile());//return left rook to it's old position
                    _board[i][0].getTroopOnTile()->_first_move = true;
                    _board[i][0].getTroopOnTile()->num_moves--;
                    _board[i][3].removeTroop();

            } else if (from.getY() == 6) {//right rook

                    _board[i][7].setTroopOnTile(_board[i][5].getTroopOnTile());
                    _board[i][7].getTroopOnTile()->_first_move = true;
                    _board[i][7].getTroopOnTile()->num_moves--;
                    _board[i][5].removeTroop();

            }
            last_move.is_last_move_castling = false;
        }

        if (last_move.is_last_move_check) {
        }

        _board[to.getX()][to.getY()].setTroopOnTile(troop);
        _board[from.getX()][from.getY()].removeTroop();
        troop->num_moves--;
        //  || ((troop->getName() == "p" && troop->getPosition().getX() == 1) || (troop->getName() == "P" && troop->getPosition().getX() == 6))
        if (troop->num_moves == 0 || ((troop->getName() == "p" && troop->getPosition().getX() == 1) || (troop->getName() == "P" && troop->getPosition().getX() == 6))) {
            troop->_first_move = true;
        }

        if (last_move.killed_last_move) {
            _board[from.getX()][from.getY()].setTroopOnTile(last_move.killed_last_move);
            if (last_move.killed_last_move->getColor()) {
                _white_grave.pop()->_alive = true;
            } else { _black_grave.pop()->_alive = true; }
            last_move.killed_last_move = nullptr;
        }
        return true;
    }
    return false;
}

void Board::setTilesToZeroProtect() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            _board[i][j].setToZeroProtect();
        }
    }
}

