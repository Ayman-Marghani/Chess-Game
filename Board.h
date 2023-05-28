#ifndef CHESS_GAME_BOARD_H
#define CHESS_GAME_BOARD_H

#include<bits/stdc++.h>
#include "Tile.h"
#include "Graveyard.h"
using namespace std;

struct Move{
        public:
        pair<Position,Position>last_move; //from, to
        Troop *killed_last_move;
        bool is_last_move_castling = false;
        bool is_last_move_check = false;
		bool is_last_move_promote = false;
};


class Board
{
private:
	const int BOARD_SIZE = 8;

//    pair<Position,Position>last_move; //from, to
//    Troop *killed_last_move;
//    bool is_last_move_castling;

    //Generate all 64 tiles with their colors and respective positions on the board.
    void GenerateTiles();
public:
	stack<Move> last_move_stack;
    char game_mode_on_board;
    Graveyard _white_grave,_black_grave;
    Tile _board[8][8];

    // Constructor
	Board();

    // Methods
	pair<int, int> strToIndices(string pos);

	void whiteProtect(int i, int j, int is_protect);

	void blackProtect(int i, int j, int is_protect);

	void move(Position,Position);
    bool undoMove();//returns true if there is troop that came back to life

    void setTilesToZeroProtect();
    bool enPassantMove(Position, Position);
};

#endif //CHESS_GAME_BOARD_H
