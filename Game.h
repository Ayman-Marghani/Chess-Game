#pragma once
#ifndef CHESS_GAME_GAME_H
#define CHESS_GAME_GAME_H

#include<bits/stdc++.h>
#include"Troop.h"
#include"Board.h"
#include"Graveyard.h"
#include"Position.h"

class Game
{
private:
	const int BOARD_SIZE = 8;

    pair<Position, Position> minimax_move;

	void storeCrossMoves(Troop* troop);

	void storeDiagonalMoves(Troop* troop);

	void storePawnMoves(Troop* troop);

	void storeKingMoves(Troop* troop);

	void storeKnightMoves(Troop* troop);

public:
//    int black_number;
//    int white_number;
    char game_mode_on_game;

    int num_moves;

    int num_of_legal_moves_for_white;
    int num_of_legal_moves_for_black;

    Board _board;

    Troop* king_black;
    Troop* king_white;

    vector<Troop*> _white_pieces;
    vector<Troop*> _black_pieces;

	Game();

    ~Game();

    void storeBlackMoves();
    void storeWhiteMoves();

    void storeBlackValidMoves();
    void storeWhiteValidMoves();

    void makeMove();

    vector<pair<Position, Position>> storeBlackMovesForMinimax();
    vector<pair<Position, Position>> storeWhiteMovesForMinimax();

    int minimax(int depth, int alpha, int beta, bool color);

	void GeneratePieces();

	void storeAllMoves(Troop* troop);

	bool checkCurPos(int x, int y, Troop* troop);
    bool kingCanMove(Position p, Troop* king);
	bool isCheck(Troop* king);
    bool isMate(Troop* king);
    bool stalemate();
//    bool insufficient();

    // 0 if game is con
    // 1 if mate
    // 2 if stalemate

    int checkStatus();


	bool isValidPosition(int x, int y);

    void promote(Troop* troop);

    // store all legal moves
    int isCoveringKing(Troop * troop);

    void storeAllLegal(Troop* troop);

    void storeAllLegalKing(Troop* troop);

    void storeAllValidIfChecked(Troop* troop);

    void storeAllKingValidIfChecked(Troop* king);

    void moveBlackMovesValidToLegal();
    void moveWhiteMovesValidToLegal();

    void canCastle(Troop*);
    bool canEnpassant(int x, int y, Troop* pawn);
    int evaluatePosition(vector<Troop*>,vector<Troop*>, Troop*, bool);
};


#endif //CHESS_GAME_GAME_H
