//
// Created by yasso on 4/30/2023.
//

#include "Game.h"

Game::Game() {
    GeneratePieces();
    storeWhiteMoves();
    storeBlackMoves();
    num_moves = 0;
}

Game::~Game() {
    delete king_black;
    delete king_white;

    int white_sz = _white_pieces.size();
    for (int i = 0; i < white_sz; i++) {
        delete _white_pieces[i];
    }

    int black_sz = _black_pieces.size();
    for (int i = 0; i < black_sz; i++) {
        delete _black_pieces[i];
    }
    _white_pieces.clear();
    _black_pieces.clear();
}

void Game::storeBlackMoves() {
    num_of_legal_moves_for_black = 0;

    king_white->attackers.clear();

    int black_sz = _black_pieces.size();
    for (int i = 0; i < black_sz; i++) {
        if (_black_pieces[i]->_alive) {
            _black_pieces[i]->_all_possible.clear();
            _black_pieces[i]->_all_legal.clear();
            storeAllMoves(_black_pieces[i]);
            storeAllLegal(_black_pieces[i]);

            num_of_legal_moves_for_black += _black_pieces[i]->_all_legal.size();
        }
    }

    king_black->_all_possible.clear();
    king_black->_all_legal.clear();
    storeAllMoves(king_black);
    storeAllLegalKing(king_black);

    num_of_legal_moves_for_black += king_black->_all_legal.size();
}

void Game::storeWhiteMoves() {
    num_of_legal_moves_for_white = 0;

    // store the moves for kings
    king_black->attackers.clear();

    int white_sz = _white_pieces.size();
    for (int i = 0; i < white_sz; i++) {
        if (_white_pieces[i]->_alive) {

            _white_pieces[i]->_all_possible.clear();
            _white_pieces[i]->_all_legal.clear();
            storeAllMoves(_white_pieces[i]);
            storeAllLegal(_white_pieces[i]);

            num_of_legal_moves_for_white += _white_pieces[i]->_all_legal.size();
        }
    }



    king_white->_all_possible.clear();
    king_white->_all_legal.clear();

    storeAllMoves(king_white);
    storeAllLegalKing(king_white);

    num_of_legal_moves_for_white += king_white->_all_legal.size();
}

void Game::storeBlackValidMoves() {
    int attackers_sz = king_black->attackers.size();
    if (attackers_sz <= 1) {
        int black_sz = _black_pieces.size();
        for (int i = 0; i < black_sz; i++) {
            if (_black_pieces[i]->_alive) {
                _black_pieces[i]->_all_valid_if_checked.clear();
                storeAllValidIfChecked(_black_pieces[i]);
            }
        }
    }
    king_black->_all_valid_if_checked.clear();
    storeAllKingValidIfChecked(king_black);
}

void Game::storeWhiteValidMoves() {
    int attackers_sz = king_white->attackers.size();
    if (attackers_sz <= 1) {
        int white_sz = _white_pieces.size();
        for (int i = 0; i < white_sz; i++) {
            if (_white_pieces[i]->_alive) {
                _white_pieces[i]->_all_valid_if_checked.clear();
                storeAllValidIfChecked(_white_pieces[i]);
            }
        }
    }
    king_white->_all_valid_if_checked.clear();
    storeAllKingValidIfChecked(king_white);
}

void Game::GeneratePieces() {
    Position pos;

    pos.setPosition(0, 2);
    Troop *bishop_black1 = new Troop("b", false, pos);
    _black_pieces.push_back(bishop_black1);
    pos.setPosition(0, 5);
    Troop *bishop_black2 = new Troop("b", false, pos);
    _black_pieces.push_back(bishop_black2);
    //Generate 2 black Bishop
    _board._board[0][2].setTroopOnTile(bishop_black1);
    _board._board[0][5].setTroopOnTile(bishop_black2);

    pos.setPosition(7, 2);
    Troop *bishop_white1 = new Troop("B", true, pos);
    _white_pieces.push_back(bishop_white1);
    pos.setPosition(7, 5);
    Troop *bishop_white2 = new Troop("B", true, pos);
    _white_pieces.push_back(bishop_white2);
//	// Generate 2 white Bishop
    _board._board[7][2].setTroopOnTile(bishop_white1);
    _board._board[7][5].setTroopOnTile(bishop_white2);

    pos.setPosition(0, 4);
    king_black = new Troop("k", false, pos);
//	// Generate black king
    _board._board[0][4].setTroopOnTile(king_black);

    pos.setPosition(7, 4);
    king_white = new Troop("K", true, pos);
//	// Generate white king
    _board._board[7][4].setTroopOnTile(king_white);

    pos.setPosition(0, 1);
    Troop *knight_black1 = new Troop("n", false, pos);
    _black_pieces.push_back(knight_black1);
    pos.setPosition(0, 6);
    Troop *knight_black2 = new Troop("n", false, pos);
    _black_pieces.push_back(knight_black2);
//	// Generate 2 black Knight
    _board._board[0][1].setTroopOnTile(knight_black1);
    _board._board[0][6].setTroopOnTile(knight_black2);

    pos.setPosition(7, 1);
    Troop *knight_white1 = new Troop("N", true, pos);
    _white_pieces.push_back(knight_white1);

    pos.setPosition(7, 6);
    Troop *knight_white2 = new Troop("N", true, pos);
    _white_pieces.push_back(knight_white2);
//	// Generate 2 white Knight
    _board._board[7][1].setTroopOnTile(knight_white1);
    _board._board[7][6].setTroopOnTile(knight_white2);
//
//	// Generate pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        // black pawns
        pos.setPosition(1, i);
        Troop *pawn_black = new Troop("p", false, pos);
        _black_pieces.push_back(pawn_black);
        _board._board[1][i].setTroopOnTile(pawn_black);
//		// white pawns
        //_board._board[1][i].setTroopOnTile(pawn_black);

        pos.setPosition(6, i);
        Troop *pawn_white = new Troop("P", true, pos);
        _white_pieces.push_back(pawn_white);
        _board._board[6][i].setTroopOnTile(pawn_white);
    }

    pos.setPosition(0, 3);
    Troop *queen_black = new Troop("q", false, pos);
    _black_pieces.push_back(queen_black);
//	// Generate black queen
    _board._board[0][3].setTroopOnTile(queen_black);
    pos.setPosition(7, 3);
    Troop *queen_white = new Troop("Q", true, pos);
    _white_pieces.push_back(queen_white);
//	// Generate white queen
    _board._board[7][3].setTroopOnTile(queen_white);
//

    pos.setPosition(0, 0);
    Troop *rook_black1 = new Troop("r", false, pos);
    _black_pieces.push_back(rook_black1);
    pos.setPosition(0, 7);
    Troop *rook_black2 = new Troop("r", false, pos);
    _black_pieces.push_back(rook_black2);
//	// Generate 2 black rook
    _board._board[0][0].setTroopOnTile(rook_black1);
    _board._board[0][7].setTroopOnTile(rook_black2);
//
    pos.setPosition(7, 0);
    Troop *rook_white1 = new Troop("R", true, pos);
    _white_pieces.push_back(rook_white1);
    pos.setPosition(7, 7);
    Troop *rook_white2 = new Troop("R", true, pos);
    _white_pieces.push_back(rook_white2);
//	// Generate 2 white rook
    _board._board[7][0].setTroopOnTile(rook_white1);
    _board._board[7][7].setTroopOnTile(rook_white2);
}


void Game::storeAllMoves(Troop *troop) {
    if (troop->getName() == "N" || troop->getName() == "n") {
        storeKnightMoves(troop);
    } else if (troop->getName() == "P" || troop->getName() == "p") {
        storePawnMoves(troop);
    } else if (troop->getName() == "K" || troop->getName() == "k") {
        storeKingMoves(troop);
    } else if (troop->getName() == "B" || troop->getName() == "b") {
        storeDiagonalMoves(troop);
    } else if (troop->getName() == "R" || troop->getName() == "r") {
        storeCrossMoves(troop);
    } else if (troop->getName() == "Q" || troop->getName() == "q") {
        storeDiagonalMoves(troop);
        storeCrossMoves(troop);
    }
}


// this function will return true if the position has a piece
bool Game::checkCurPos(int x, int y, Troop *troop) {
    Position cur_pos;
    cur_pos.setPosition(x, y);
    Troop *cur_troop = _board._board[x][y].getTroopOnTile();
    // if there isn't a piece on the cur_pos add cur_pos to all_possible vector
    if (cur_troop == nullptr) {
        //...
        troop->_all_possible.push_back(cur_pos);

        if (tolower(troop->getName()[0]) == 'p') return false;

        if (troop->getColor()) _board._board[x][y].incWhiteProtect();
        else _board._board[x][y].incBlackProtect();

        return false;
    }
        // if there is a piece from the same team add its position to all_protected vector then break
    else if (cur_troop != nullptr && cur_troop->getColor() == troop->getColor()) {
        //...
        if (troop->getColor()) _board._board[x][y].incWhiteProtect();
        else _board._board[x][y].incBlackProtect();

        troop->_all_protected.push_back(cur_pos);

        return true;
    }
        // if there is a piece from the other team add its position to all_possible vector then break
    else{
        if(cur_troop->getColor() != troop->getColor())
        {
            if (troop->getColor()) _board._board[x][y].incWhiteProtect();
            else _board._board[x][y].incBlackProtect();

            troop->_all_possible.push_back(cur_pos);

            // Add as an attacker to the king of the opp if he can access its tile
            if (!troop->getColor() && cur_troop->getName() == "K") {
                king_white->attackers.push_back(troop);
            } else if (troop->getColor() && cur_troop->getName() == "k") {
                king_black->attackers.push_back(troop);
            }
        }
    }
    return true;
}

// Tell us if the king can be on a specific square
bool Game::kingCanMove(Position p, Troop *king) {
    //white -> getblack
    //black -> getwhite

    Position pos = p;
    int pos_x = pos.getX(), pos_y = pos.getY();
    if (king->getColor()) {
        if (_board._board[pos_x][pos_y].getBlackProtect()) return false;
    }

    if (!king->getColor()) {
        if (_board._board[pos_x][pos_y].getWhiteProtect()) return false;
    }

    return true;
}

bool Game::isValidPosition(int x, int y) {
    return (x >= 0 && x < BOARD_SIZE) && (y >= 0 && y < BOARD_SIZE);
}

void Game::storeCrossMoves(Troop *troop) {
    Position troop_pos = troop->getPosition();
    Tile tile = _board._board[troop_pos.getX()][troop_pos.getY()];
    // horizontal (right)
    for (int x = troop_pos.getX() + 1; x < BOARD_SIZE; x++) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, troop_pos.getY(), troop))
            break;
    }
    // horizontal (left)
    for (int x = troop_pos.getX() - 1; x >= 0; x--) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, troop_pos.getY(), troop))
            break;

    }
    // Vertical (up)
    for (int y = troop_pos.getY() + 1; y < BOARD_SIZE; y++) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(troop_pos.getX(), y, troop))
            break;
    }
    // vertical (down)
    for (int y = troop_pos.getY() - 1; y >= 0; y--) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(troop_pos.getX(), y, troop))
            break;
    }
}

void Game::storeDiagonalMoves(Troop *troop) {
    Position troop_pos = troop->getPosition();
    Tile tile = _board._board[troop_pos.getX()][troop_pos.getY()];
    int pos_x = troop_pos.getX();
    int pos_y = troop_pos.getY();

    // down right
    for (int x = pos_x + 1, y = pos_y + 1; x < BOARD_SIZE && y < BOARD_SIZE; x++, y++) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, y, troop)) break;
    }

    // up left
    for (int x = pos_x - 1, y = pos_y - 1; x >= 0 && y >= 0; x--, y--) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, y, troop))
            break;
    }
    // down left
    for (int x = pos_x + 1, y = pos_y - 1; x < BOARD_SIZE && y >= 0; x++, y--) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, y, troop))
            break;
    }
    // up right
    for (int x = pos_x - 1, y = pos_y + 1; x >= 0 && y < BOARD_SIZE; x--, y++) {
        // if there is a piece in the current position break from the loop
        if (checkCurPos(x, y, troop))
            break;
    }
}


void Game::storePawnMoves(Troop *troop) {
    //coef for different directions
    int coef;
    if(troop->getColor())
        coef = -1;
    else
        coef = 1;

    //Pawn position
    int pawn_pos_x = troop->getPosition().getX();
    int pawn_pos_y= troop->getPosition().getY();

    if(isValidPosition(pawn_pos_x+coef, pawn_pos_y )) {

        if(_board._board[pawn_pos_x+coef][pawn_pos_y].getTroopOnTile() == nullptr){
            checkCurPos(pawn_pos_x + coef, pawn_pos_y, troop);
            if(isValidPosition(pawn_pos_x+2*coef, pawn_pos_y )) {
                if (troop->_first_move && _board._board[pawn_pos_x + 2 * coef][pawn_pos_y].getTroopOnTile() ==
                                          nullptr)//forward moves //if no piece infront of it and still in the first move
                {
                    checkCurPos(pawn_pos_x + (2 * coef), pawn_pos_y, troop);
                }
            }
        }
    }
    if(isValidPosition(pawn_pos_x+coef, pawn_pos_y-1 ))//left diag
    {
        if(troop->getColor())
            _board._board[pawn_pos_x+coef][pawn_pos_y-1].incWhiteProtect();
        else
            _board._board[pawn_pos_x+coef][pawn_pos_y-1].incBlackProtect();

        if(_board._board[pawn_pos_x+coef][pawn_pos_y-1].getTroopOnTile() != nullptr) {
            checkCurPos(pawn_pos_x + coef, pawn_pos_y - 1, troop);//left diag
        }

//        else if (_board._board[pawn_pos_x+coef][pawn_pos_y-1].getTroopOnTile() == nullptr) {
//
//            if (canEnpassant(pawn_pos_x + coef, pawn_pos_y - 1, troop)) {
//
//                Position pos;
//                pos.setPosition(pawn_pos_x + coef, pawn_pos_y - 1);
//                troop->_all_possible.push_back(pos);
//            }
//        }
    }

    if(isValidPosition(pawn_pos_x+coef, pawn_pos_y+1 ))//right diag
    {
        if(troop->getColor())
            _board._board[pawn_pos_x+coef][pawn_pos_y+1].incWhiteProtect();
        else
            _board._board[pawn_pos_x+coef][pawn_pos_y+1].incBlackProtect();

        if( _board._board[pawn_pos_x+coef][pawn_pos_y+1].getTroopOnTile() != nullptr){
            checkCurPos(pawn_pos_x + coef, pawn_pos_y + 1, troop);//left diag
        }
//        else if (_board._board[pawn_pos_x+coef][pawn_pos_y+1].getTroopOnTile() == nullptr) {
//            if (canEnpassant(pawn_pos_x + coef, pawn_pos_y + 1, troop)) {
//                Position pos;
//                pos.setPosition(pawn_pos_x + coef, pawn_pos_y + 1);
//                troop->_all_possible.push_back(pos);
//            }
//        }
    }

}

void Game::storeKnightMoves(Troop *troop) {
    Position troop_pos = troop->getPosition();
    Tile tile = _board._board[troop_pos.getX()][troop_pos.getY()];
    int pos_x = troop_pos.getX();
    int pos_y = troop_pos.getY();
    if (isValidPosition(pos_x + 1, pos_y + 2))
        checkCurPos(pos_x + 1, pos_y + 2, troop);
    if (isValidPosition(pos_x + 1, pos_y - 2))
        checkCurPos(pos_x + 1, pos_y - 2, troop);

    if (isValidPosition(pos_x - 1, pos_y + 2))
        checkCurPos(pos_x - 1, pos_y + 2, troop);
    if (isValidPosition(pos_x - 1, pos_y - 2))
        checkCurPos(pos_x - 1, pos_y - 2, troop);

    if (isValidPosition(pos_x + 2, pos_y + 1))
        checkCurPos(pos_x + 2, pos_y + 1, troop);
    if (isValidPosition(pos_x + 2, pos_y - 1))
        checkCurPos(pos_x + 2, pos_y - 1, troop);
    if (isValidPosition(pos_x - 2, pos_y + 1))
        checkCurPos(pos_x - 2, pos_y + 1, troop);
    if (isValidPosition(pos_x - 2, pos_y - 1))
        checkCurPos(pos_x - 2, pos_y - 1, troop);
}

void Game::storeKingMoves(Troop *king) {
    Position troop_pos = king->getPosition();
    Tile tile = _board._board[troop_pos.getX()][troop_pos.getY()];
    int pos_x = troop_pos.getX();
    int pos_y = troop_pos.getY();
    // up (y - 1) (x - 1, x, x + 1)
    if (isValidPosition(pos_x - 1, pos_y - 1))
        checkCurPos(pos_x - 1, pos_y - 1, king);
    if (isValidPosition(pos_x, pos_y - 1))
        checkCurPos(pos_x, pos_y - 1, king);
    if (isValidPosition(pos_x + 1, pos_y - 1))
        checkCurPos(pos_x + 1, pos_y - 1, king);
    // down (y + 1) (x - 1, x, x + 1)
    if (isValidPosition(pos_x - 1, pos_y + 1))
        checkCurPos(pos_x - 1, pos_y + 1, king);
    if (isValidPosition(pos_x, pos_y + 1))
        checkCurPos(pos_x, pos_y + 1, king);
    if (isValidPosition(pos_x + 1, pos_y + 1))
        checkCurPos(pos_x + 1, pos_y + 1, king);
    // same row: y (x - 1, x + 1)
    if (isValidPosition(pos_x - 1, pos_y))
        checkCurPos(pos_x - 1, pos_y, king);
    if (isValidPosition(pos_x + 1, pos_y))
        checkCurPos(pos_x + 1, pos_y, king);

    if (game_mode_on_game != 'c') canCastle(king);
}


bool Game::isCheck(Troop *king) {
    //white -> getblack
    //black -> getwhit
    if (king->attackers.size() != 0) {
        return true;
    }
    return false;
}

// Input: pointer to troop, pointer to king
// this function checks _all_possible moves and stores the legal moves in _all_legal
void Game::storeAllLegal(Troop *troop) {
// Output explanation: left = 1 | right = 2 | above = 3 | below = 4 | above & left = 5 | below & right = 6 | above & right = 7 | below & left = 8

    Position king_pos;
    if (troop->getColor())
        king_pos = king_white->getPosition();
    else {
        king_pos = king_black->getPosition();
    }

    int king_x = king_pos.getX(), king_y = king_pos.getY();

    int n = troop->_all_possible.size();

    int val = isCoveringKing(troop);

    if (val == 0) {
//       troop->_all_legal = troop->_all_possible;
        for (int i = 0; i < n; ++i) {
            troop->_all_legal.push_back(troop->_all_possible[i]);
        }
    }
        // rows
    else if (val <= 2) {
        for (int i = 0; i < n; ++i) {
            if (troop->_all_possible[i].getX() == king_x) {
                troop->_all_legal.push_back(troop->_all_possible[i]);
            }
        }
    }
        // columns
    else if (val <= 4) {
        for (int i = 0; i < n; ++i) {
            if (troop->_all_possible[i].getY() == king_y) {
                troop->_all_legal.push_back(troop->_all_possible[i]);
            }
        }
    }

        // diagonal NEEDS TESTING: MIGHT CAUSE ERRORS

    else {
        for (int i = 0; i < n; i++) {
            if (abs(troop->_all_possible[i].getX() - king_x) == abs(troop->_all_possible[i].getY() - king_y)) {
                troop->_all_legal.push_back(troop->_all_possible[i]);
            }
        }
    }
}

void Game::storeAllLegalKing(Troop *king) {
    int vec_size = king->_all_possible.size();
    for (int i = 0; i < vec_size; ++i) {
        // if the king can move to a position in _all_possible, push that position to _all_legal
        if (kingCanMove(king->_all_possible[i], king)) {
            king->_all_legal.push_back(king->_all_possible[i]);
        }
    }
}

// Input: pointer to troop and pointer to king
// Output: 0 if the troop isn't covering the king, a number if the troop is covering the king
// Output explanation: left = 1 | right = 2 | above = 3 | below = 4 | above & left = 5 | below & right = 6 | above & right = 7 | below & left = 8
// x less below | x more above | y less left | y more right
int Game::isCoveringKing(Troop *troop) {
    Position troop_pos = troop->getPosition();
    int troop_x = troop_pos.getX(), troop_y = troop_pos.getY();
    Position king_pos;
    if (troop->getColor())
        king_pos = king_white->getPosition();
    else
        king_pos = king_black->getPosition();

    int king_x = king_pos.getX(), king_y = king_pos.getY();

    // If troop and king are in the same row
    if (troop_x == king_x) {
        // if the troop is left to the king
        if (troop_y < king_y) {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int i = king_y - 1; i > troop_y; i--) {//I think we need to check in both directions
                if (_board._board[troop_x][i].getTroopOnTile() != nullptr) {
                    if (_board._board[troop_x][i].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 1 (true)
            for (int i = troop_y - 1; i >= 0; i--) {
                if (_board._board[troop_x][i].getTroopOnTile() != nullptr) {
                    if (_board._board[troop_x][i].getTroopOnTile()->getCross() == true &&
                        _board._board[troop_x][i].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 1;
                    }
                    return 0;
                }
            }
        }
            // if the troop is right to the king
        else {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int i = king_y + 1; i < troop_y; i++) {
                if (_board._board[troop_x][i].getTroopOnTile() != nullptr) {
                    if (_board._board[troop_x][i].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 2 (true)
            for (int i = troop_y + 1; i < BOARD_SIZE; i++) {
                if (_board._board[troop_x][i].getTroopOnTile() != nullptr) {
                    if (_board._board[troop_x][i].getTroopOnTile()->getCross() &&
                        _board._board[troop_x][i].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 2;
                    }
                    return 0;
                }
            }
        }
    }
    // If troop and king are in the same column
    if (troop_y == king_y) {
        // if the troop above the king
        if (king_x > troop_x) {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int i = king_x - 1; i > troop_x; i--) {
                if (_board._board[i][troop_y].getTroopOnTile() != nullptr) {
                    if (_board._board[i][troop_y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 3 (true)
            for (int i = troop_x - 1; i >= 0; i--) {
                if (_board._board[i][troop_y].getTroopOnTile() != nullptr) {
                    if (_board._board[i][troop_y].getTroopOnTile()->getCross() == true &&
                        _board._board[i][troop_y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 3;
                    }
                    return 0;
                }
            }
        }
            // If the troop below the king
        else {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int i = king_x + 1; i < troop_x; i++) {
                if (_board._board[i][troop_y].getTroopOnTile() != nullptr) {
                    if (_board._board[i][troop_y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 4 (true)
            for (int i = troop_x + 1; i < BOARD_SIZE; i++) {
                if (_board._board[i][troop_y].getTroopOnTile() != nullptr) {
                    if (_board._board[i][troop_y].getTroopOnTile()->getCross() == true &&
                        _board._board[i][troop_y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 4;
                    }
                    return 0;
                }
            }
        }
    }


    // If troop and king are in the same diagonal
    if (abs(troop_x - king_x) == abs(troop_y - king_y)) {
        // Troop above & left to the king
        if (king_x > troop_x && king_y > troop_y) {
            // if there is already another piece that is covering the king -> return 0 (false)s
            //northwest
            for (int x = king_x - 1, y = king_y - 1; x > troop_x && y > troop_y; x--, y--) {
                if (_board._board[x][y].getTroopOnTile() != nullptr) {
                    if (_board._board[x][y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 5 (true)
            for (int x = troop_x - 1, y = troop_y - 1; x >= 0 && y >= 0; x--, y--) {
                if (_board._board[x][y].getTroopOnTile()) {
                    if (_board._board[x][y].getTroopOnTile()->getDiagonal() &&
                        _board._board[x][y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 5;
                    }
                    return 0;
                }
            }
        }
        // Troop below & right to the king
        if (king_x < troop_x && king_y < troop_y) {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int x = king_x + 1, y = king_y + 1; x < troop_x && y < troop_y; x++, y++) {
                if (_board._board[x][y].getTroopOnTile() != nullptr) {
                    if (_board._board[x][y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 6 (true)
            for (int x = troop_x + 1, y = troop_y + 1; x < BOARD_SIZE && y < BOARD_SIZE; x++, y++) {
                if (_board._board[x][y].getTroopOnTile()) {
                    if (_board._board[x][y].getTroopOnTile()->getDiagonal() &&
                        _board._board[x][y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 6;
                    }
                    return 0;
                }
            }
        }
        // Troop above & right
        if (king_x > troop_x && king_y < troop_y) {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int x = king_x - 1, y = king_y + 1; x > troop_x && y < troop_y; x--, y++) {
                if (_board._board[x][y].getTroopOnTile() != nullptr) {
                    if (_board._board[x][y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 7 (true)
            for (int x = troop_x - 1, y = troop_y + 1; x >= 0 && y <= BOARD_SIZE; x--, y++) {
                if (_board._board[x][y].getTroopOnTile()) {
                    if (_board._board[x][y].getTroopOnTile()->getDiagonal() &&
                        _board._board[x][y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 7;
                    }
                    return 0;
                }
            }
        }
        // Troop below & left
        if(king_x < troop_x && king_y > troop_y) {
            // if there is already another piece that is covering the king -> return 0 (false)
            for (int x = king_x + 1, y = king_y - 1; x < troop_x && y > troop_y; x++, y--) {
                if (_board._board[x][y].getTroopOnTile() != nullptr) {
                    if (_board._board[x][y].getTroopOnTile()->getColor() == troop->getColor()) {
                        return 0;
                    }
                }
            }
            // if there is an opponent piece that is threatening the king from the same direction -> return 8 (true)
            for (int x = troop_x + 1, y = troop_y - 1; x < BOARD_SIZE && y >= 0; x++, y--) {
                if (_board._board[x][y].getTroopOnTile()) {
                    if (_board._board[x][y].getTroopOnTile()->getDiagonal() &&
                        _board._board[x][y].getTroopOnTile()->getColor() != troop->getColor()) {
                        return 8;
                    }
                    return 0;
                }
            }
        }
    }
    return 0;
}

void Game::storeAllKingValidIfChecked(Troop* king) {
    vector<Troop*> vec_attackers = king->attackers;
    int sz_attacker = vec_attackers.size();

    Position king_pos = king->getPosition();
    int king_x = king_pos.getX(), king_y = king_pos.getY();

    Troop* attacker;
    Position attacker_pos;
    int attacker_x, attacker_y;

    int sz_king = king->_all_legal.size();

    vector<Position> threat_positions;

    for (int i = 0;i < sz_attacker; ++i) {
        attacker = vec_attackers[i];
        attacker_pos = attacker->getPosition();
        attacker_x = attacker_pos.getX();
        attacker_y = attacker_pos.getY();

        if(vec_attackers[i]->getName() == "P" || vec_attackers[i]->getName() == "p")
        {
            int coef;
            if(vec_attackers[i]->getColor()){coef = -1;}
            else{coef = 1;}
            Position threat_pos;
            threat_pos.setPosition(vec_attackers[i]->getPosition().getX()+coef,vec_attackers[i]->getPosition().getY()-1);
            threat_positions.push_back(threat_pos);
            threat_pos.setPosition(vec_attackers[i]->getPosition().getX()+coef,vec_attackers[i]->getPosition().getY()+1);
            threat_positions.push_back(threat_pos);
        }
        if (vec_attackers[i]->getName() == "Q" || vec_attackers[i]->getName() == "q" || vec_attackers[i]->getName() == "R" ||
            vec_attackers[i]->getName() == "r") {
            // If attacker and king are in the same row
            if (attacker_x == king_x) {
                for (int j = 0; j < sz_king; ++j) {
                    if (king->_all_legal[j].getX() == attacker_x && king->_all_legal[j].getY() != attacker_y) {
                        threat_positions.push_back(king->_all_legal[j]);
                    }
                }
            }
            // If troop and king are in the same column
            if (attacker_y == king_y) {
                for (int j = 0; j < sz_king; ++j) {
                    if (king->_all_legal[j].getY() == attacker_y && king->_all_legal[j].getX() != attacker_x) {
                        threat_positions.push_back(king->_all_legal[j]);
                    }
                }
            }
        }
        if (vec_attackers[i]->getName() == "Q" || vec_attackers[i]->getName() == "q" || vec_attackers[i]->getName() == "B" ||
            vec_attackers[i]->getName() == "b") {
            // If troop and king are in the same diagonal
            if (abs(attacker_x - king_x) == abs(attacker_y - king_y)) {
                for (int j = 0; j < sz_king; ++j) {
                    if ((abs(attacker_x - king->_all_legal[j].getX()) == abs(attacker_y - king->_all_legal[j].getY()))
                        && (attacker_x != king->_all_legal[j].getX() || attacker_y != king->_all_legal[j].getY())) {
                        threat_positions.push_back(king->_all_legal[j]);
                    }
                }
            }
        }
    }
    int sz_threat = threat_positions.size();
    int pos_x, pos_y;
    bool is_found;

    for (int i = 0; i < sz_king; i++) {
        is_found = false;

        for (int j = 0; j < sz_threat; j++) {
            if (king->_all_legal[i] == threat_positions[j]) {
                is_found = true;
                break;
            }
        }
        // if the move is not found
        if(!is_found && kingCanMove(king->_all_legal[i], king)) {
            king->_all_valid_if_checked.push_back(king->_all_legal[i]);
        }
    }
}

void Game::storeAllValidIfChecked(Troop *troop) {
    Troop *attacker;
    Position king_pos;

    if (troop->getColor()) {
        attacker = king_white->attackers[0];
        king_pos = king_white->getPosition();
    } else {
        attacker = king_black->attackers[0];
        king_pos = king_black->getPosition();
    }
    Position attacker_pos = attacker->getPosition();

    int attacker_x = attacker_pos.getX(), attacker_y = attacker_pos.getY();
    int king_x = king_pos.getX(), king_y = king_pos.getY();

    Position troop_pos = troop->getPosition();
    int troop_x = troop_pos.getX(), troop_y = troop_pos.getY();
    int sz_troop = troop->_all_legal.size();

    if (attacker->getName() == "N" || attacker->getName() == "n" || attacker->getName() == "P" ||
        attacker->getName() == "p") {
        for (int i = 0; i < sz_troop; ++i) {
            if (troop->_all_legal[i] == attacker_pos) {
                if (tolower(troop->getName()[0]) == 'p' && troop_y == attacker_y) {
                    continue;
                }
                troop->_all_valid_if_checked.push_back(troop->_all_legal[i]);
            }
        }
    }
    vector<Position> threat_positions;
    Position pos;
    // set the positions between the king and the attacker

    if (attacker_x == king_x) {
        // if the troop is left to the king
        if (king_y > attacker_y) {
            for (int i = king_y - 1; i >= attacker_y; i--) {
                pos.setPosition(attacker_x, i);
                threat_positions.push_back(pos);
            }
        }
            // if the troop is right to the king
        else {
            for (int i = king_y + 1; i <= attacker_y; i++) {
                pos.setPosition(attacker_x, i);
                threat_positions.push_back(pos);
            }
        }
    }

        // If troop and king are in the same column
    else if (king_y == attacker_y) {
        // if the troop above the king
        if (king_x > attacker_x) {
            for (int i = king_x - 1; i >= attacker_x; i--) {
                pos.setPosition(i, attacker_y);
                threat_positions.push_back(pos);
            }

        }
            // If the troop below the king
        else {
            for (int i = king_x + 1; i <= attacker_x; i++) {
                pos.setPosition(i, attacker_y);
                threat_positions.push_back(pos);
            }
        }
    }
        // If troop and king are in the same diagonal
    else if (abs(attacker_x - king_x) == abs(attacker_y - king_y)) {
        // Troop above & left to the king
        if (king_x > attacker_x && king_y > attacker_y) {
            for (int x = king_x - 1, y = king_y - 1; x >= attacker_x && y >= attacker_y; x--, y--) {
                pos.setPosition(x, y);
                threat_positions.push_back(pos);
            }

        }
            // Troop below & right to the king
        else if (king_x < attacker_x && king_y < attacker_y) {
            for (int x = king_x + 1, y = king_y + 1; x <= attacker_x && y <= attacker_y; x++, y++) {
                pos.setPosition(x, y);
                threat_positions.push_back(pos);
            }
        }
            // Troop above & right
        else if (king_x > attacker_x && king_y < attacker_y) {
            for (int x = king_x - 1, y = king_y + 1; x >= attacker_x && y <= attacker_y; x--, y++) {
                pos.setPosition(x, y);
                threat_positions.push_back(pos);
            }
        }
            // Troop below & left
        else {
            for (int x = king_x + 1, y = king_y - 1; x <= attacker_x && y >= attacker_y; x++, y--) {
                pos.setPosition(x, y);
                threat_positions.push_back(pos);
            }
        }
    }

    int sz_threat = threat_positions.size();

    // Set all the positions that can get the king out from the check to the vector _all_valid_if_checked
    // by check if the move is on the threat positions or not

    for (int i = 0; i < sz_troop; i++) {
        for (int j = 0; j < sz_threat; j++) {
            if (troop->_all_legal[i] == threat_positions[j]) {
                if (tolower(troop->getName()[0]) == 'p' && troop_y == attacker_y && threat_positions[j] == attacker_pos){
                    continue;
                }
                troop->_all_valid_if_checked.push_back(threat_positions[j]);
                break;
            }
        }
    }

}

void Game::moveBlackMovesValidToLegal() {
    int black_sz = _black_pieces.size();
    for (int i = 0; i < black_sz; i++) {
        if (_black_pieces[i]->_alive) {
            _black_pieces[i]->_all_legal.clear();
            _black_pieces[i]->_all_legal = _black_pieces[i]->_all_valid_if_checked;
        }
    }
    king_black->_all_legal.clear();
    king_black->_all_legal = king_black->_all_valid_if_checked;
}

void Game::moveWhiteMovesValidToLegal() {
    int white_sz = _white_pieces.size();
    for (int i = 0; i < white_sz; i++) {
        if (_white_pieces[i]->_alive) {
            _white_pieces[i]->_all_legal.clear();
            _white_pieces[i]->_all_legal = _white_pieces[i]->_all_valid_if_checked;
        }
    }
    king_white->_all_legal.clear();
    king_white->_all_legal = king_white->_all_valid_if_checked;
}

bool Game::isMate(Troop *king) {
    int attackers_sz = king->attackers.size();
    if (attackers_sz > 1) {
        if (king->_all_valid_if_checked.size() != 0) {
            return false;
        } else {
            // king->_all_legal.clear();
            return true;
        }
    }
    //Flag for if a piece can protect the king
    bool flag = false;

    if (attackers_sz == 1) {
        // if king is black, call storeAllValidIfChecked on all _black_pieces
        if (king->getName() == "k") {
            int black_size = _black_pieces.size();
            for (int i = 0; i < black_size; i++) {
                if (_black_pieces[i]->_alive && _black_pieces[i]->_all_valid_if_checked.size() != 0)
                {
                    flag = true;
                    break;
                }
            }

        } else {
            // if king is white, call storeAllValidIfChecked on all _white_pieces
            int white_size = _white_pieces.size();
            for (int i = 0; i < white_size; i++) {
                if (_white_pieces[i]->_alive && _white_pieces[i]->_all_valid_if_checked.size() != 0) {
                    flag = true;
                    break;
                }
            }
        }
    }
    if (!flag && king->_all_valid_if_checked.size() == 0) {
        return true;
    }
    return false;
}

bool Game::stalemate() {
    // White
    if (num_moves % 2 == 0) {
        if (!num_of_legal_moves_for_white) return 1;
    }
    else if (num_moves % 2) {
        if (!num_of_legal_moves_for_black) return 1;
    }

    return 0;
}

//bool Game::insufficient() {
//    bool white_ins = false, black_ins = false;
//
//    if (!white_number) {
//        white_ins = true;
//    }
//    else if (white_number == 1) {
//        int sz_white = _white_pieces.size();
//
//        for (int i = 0; i < sz_white; ++i) {
//            if (_white_pieces[i]->_alive && (tolower(_white_pieces[i]->getName()[i]) == 'b' || tolower(_white_pieces[i]->getName()[i]) == 'n')) {
//                white_ins = true;
//            }
//        }
//    }
//
//    if (!black_number) {
//        white_ins = true;
//    }
//    else if (black_number == 1) {
//        int sz_white = _black_pieces.size();
//
//        for (int i = 0; i < sz_white; ++i) {
//            if (_black_pieces[i]->_alive && (tolower(_black_pieces[i]->getName()[i]) == 'b' || tolower(_black_pieces[i]->getName()[i]) == 'n')) {
//                black_ins = true;
//            }
//        }
//    }
//
//    return white_ins && black_ins;
//}


int Game::checkStatus() {
    // king ischeck
    // black will play
    //If black turn and checked
    if (isCheck(king_black)) {
        storeBlackValidMoves();

        if (isMate(king_black)) {
            //endGame(true);
            return 1;
        } else {
            // forced moves
            moveBlackMovesValidToLegal();
        }
    }
        //If white turn and checked
    else if (isCheck(king_white)) {
        storeWhiteValidMoves();
        if (isMate(king_white)) {
            //endGame(false);
            return 2;
        } else {
            // forced moves
            moveWhiteMovesValidToLegal();
        }
    }
    else if (stalemate()) {
        // for draw
        return 3;
    }
    return 0;
}

void Game::canCastle(Troop *troop) {
    if (troop == nullptr || !troop->_first_move || isCheck(troop)) return;

    int i;
    int start = 5, end = 5;
    bool l = false, r = false;//flags indicating whether left and right rooks are available for castling
    Position pos;

    if (troop->getColor())//if white
        i = 7;
    else
        i = 0;

    if (_board._board[i][0].getTroopOnTile() != nullptr) {
        if (_board._board[i][0].getTroopOnTile()->_first_move) {
            l = true;
            start = 1;
        }
    }
    if (_board._board[i][7].getTroopOnTile() != nullptr) {
        if (_board._board[i][7].getTroopOnTile()->_first_move) {
            r = true;
            end = 8;
        }
    }
    if (!l && !r) { return;}//if rooks not available for castling

    if (l && _board._board[i][1].getTroopOnTile() == nullptr && _board._board[i][2].getTroopOnTile() == nullptr &&
        _board._board[i][3].getTroopOnTile() == nullptr) {
            pos.setPosition(i, 2);
            troop->_all_possible.push_back(pos);
    }
    if (r && _board._board[i][5].getTroopOnTile() == nullptr && _board._board[i][6].getTroopOnTile() == nullptr) {
        pos.setPosition(i, 6);
        troop->_all_possible.push_back(pos);
    }
}
//
//bool Game::canEnpassant(int x, int y, Troop* pawn) {
//    Troop *opp_pawn;
//    if (pawn->getColor()) {
//        opp_pawn = _board._board[x+1][y].getTroopOnTile();
//    }
//    else {
//        opp_pawn = _board._board[x-1][y].getTroopOnTile();
//    }
//
//    if (opp_pawn != nullptr) {
//        if (opp_pawn->getColor() != pawn->getColor() && num_moves == opp_pawn->move_when_first_move) {
//            return true;
//        }
//    }
//    return false;
//}
//



void Game::makeMove() {
        minimax(2, INT_MIN, INT_MAX, false);
        _board.move(minimax_move.first, minimax_move.second);
}
//Black is the maximizer -> cpu
//White is the minimizer -> player
int Game::minimax(int depth, int alpha, int beta, bool color) {
    vector<pair<Position, Position>> black_moves = storeBlackMovesForMinimax();
    vector<pair<Position, Position>> white_moves = storeWhiteMovesForMinimax();

    int game_status = checkStatus();
    if (game_status == 1) {
        return INT_MIN;
    }
    else if (game_status == 2) {
        return INT_MAX;
    }
    else if (game_status == 3) {
        return 0;
    }


    if (depth == 0) {
        if(color)
        {
            return evaluatePosition(_black_pieces,_white_pieces,king_black,color);
        }
        else
        {
            return evaluatePosition(_black_pieces,_white_pieces,king_white,color);
        }
    }

    if (!color) {
        int maximum = INT_MIN;
        for (auto& i : black_moves) {
            // play the move
            _board.move(i.first, i.second);
            num_moves++;

            int game_status = checkStatus();
            if (game_status == 1) {
                _board.undoMove();
                num_moves--;
                return INT_MIN;
            }
            else if (game_status == 2) {
                _board.undoMove();
                num_moves--;
                return INT_MAX;
            }
            else if (game_status == 3) {
                _board.undoMove();
                num_moves--;
                return 0;
            }

            storeBlackMoves();
            storeWhiteMoves();

            int val = minimax(depth - 1, alpha, beta, true);

            _board.undoMove();
            num_moves--;

            storeWhiteMoves();
            storeBlackMoves();
            _board.setTilesToZeroProtect();

            if (val > maximum) {
                maximum = val;
                minimax_move = i;
            }

            alpha = max(alpha, maximum);
            if (beta <= alpha)
                break; // Beta cutoff
        }
        return maximum;
    }
    else {
        int minimum = INT_MAX;
        for (auto& i : white_moves) {
            // play the move
            _board.move(i.first, i.second);
            num_moves++;

            int game_status = checkStatus();
            if (game_status == 1) {
                _board.undoMove();
                num_moves--;
                return INT_MIN;
            }
            else if (game_status == 2) {
                _board.undoMove();
                num_moves--;
                return INT_MAX;
            }
            else if (game_status == 3) {
                _board.undoMove();
                num_moves--;
                return 0;
            }

            storeWhiteMoves();
            storeBlackMoves();

            int val = minimax(depth - 1, alpha, beta, false);

            _board.undoMove();
            num_moves--;

            storeBlackMoves();
            storeWhiteMoves();
            _board.setTilesToZeroProtect();

            if (val < minimum) {
                minimum = val;
            }

            beta = min(beta, minimum);
            if (beta <= alpha)
                break; // Alpha cutoff
        }
        return minimum;
    }
}

vector<pair<Position, Position>> Game::storeBlackMovesForMinimax()
{
    // black moves
    vector<pair<Position, Position>> black_moves;
    int sz_black = _black_pieces.size();
    int sz_piece;
    for (int i = 0; i < sz_black; ++i) {
        sz_piece = _black_pieces[i]->_all_legal.size();
        if (_black_pieces[i]->_alive) {
            for (int j = 0; j < sz_piece; j++) {
                black_moves.push_back(make_pair(_black_pieces[i]->getPosition(), _black_pieces[i]->_all_legal[j]));
            }
        }
    }
    int sz_king_black = king_black->_all_legal.size();
    for(int i =0; i < sz_king_black; i++)
    {
        black_moves.push_back(make_pair(king_black->getPosition(), king_black->_all_legal[i]));
    }
    return black_moves;

}

vector<pair<Position, Position>> Game::storeWhiteMovesForMinimax() {
    vector<pair<Position, Position>> white_moves;
    // White moves
    white_moves.clear();
    int sz_white = _white_pieces.size();
    int sz_piece;
    for (int i = 0; i < sz_white; ++i) {
        sz_piece = _white_pieces[i]->_all_legal.size();
        if (_white_pieces[i]->_alive) {
            for (int j = 0; j < sz_piece; j++) {
                white_moves.push_back(make_pair(_white_pieces[i]->getPosition(), _white_pieces[i]->_all_legal[j]));
            }
        }
    }
    int sz_king_white = king_white->_all_legal.size();
    for(int i = 0; i < sz_king_white; i++)
    {
        white_moves.push_back(make_pair(king_white->getPosition(), king_white->_all_legal[i]));
    }
    return white_moves;
}

//Black -> maximizer
//White -> minimizer
int Game::evaluatePosition(vector<Troop*> black_pieces,vector<Troop*> white_pieces, Troop* opp_king, bool color) {
    int score = 0;
    int coef = 1;

    if(color)// if white, coef = -1 to return negative score
    {
        coef = -1;
    }
    // Loop over all of my troops, increase the material and move values, and increase more if my pieces are towards the opponent.
    for (auto &i : black_pieces) {
        if (i->_alive) {
            score += i->getValue()*100;
            score += i->_all_legal.size();
            for (auto &j : i->_all_legal) {
                if (j.getX() > 3) {
                    score += 10;
                }
            }
        }
    }
    //Loop over all of the opponents troops, decrease the material and move values, and decrease more if the opponents pieces are towards my side..
    for (auto &i : white_pieces) {
        if (i->_alive) {
            score -= i->getValue()*100;//minimize opponent troops;
            score -= i->_all_legal.size();
            for (auto &j : i->_all_legal) {
                if (j.getX() < 5) {
                    score -= 10;
                }
            }
        }
    }

    if (isCheck(opp_king)) {
        score += 50;
    }

    return (score);
}



