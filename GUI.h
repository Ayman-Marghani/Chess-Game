#include<bits/stdc++.h>
using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tile.h"
#include "Board.h"
#include "Graveyard.h"
#include "Game.h"

using namespace sf;
#ifndef CHESS_GAME_GUI_H
#define CHESS_GAME_GUI_H

class Square : public sf::RectangleShape
{
public:
	Square();

	Square(bool);
    Square(int R, int G, int B, int A);

    void setSquare(int R, int G, int B, int A);
};

class GUI
{
private:
    float BOARD_X;
    float BOARD_Y;
    float TILE_SIZE;

    Mouse mouse;
    RenderWindow window;

    // textures and sprites
    Texture background_texture;
    Sprite background_sprite;
    Texture white_win_texture;
    Sprite white_win_sprite;
    Texture black_win_texture;
    Sprite black_win_sprite;
    Texture draw_texture;
    Sprite draw_sprite;

    map<char, Texture> troops_textures;
    map<char, Sprite> troops_sprites;
    Font font;
    Text text;

    // Squares
    Square white;
    Square black;
    Square light;
    Square dark;
    Square light_red;
    Square dark_red;
    Square light_blue;
    Square dark_blue;
public:
    Game game;

	GUI();

	void setWindow();

    void printGraveyard(Board &board);

	void printPiece(Tile &tile, float x, float y);

	void printBoard(Board &board);

	int display();

    void endGame(int win_team);

    void printBorder(Board &board);

    void promote(Troop* troop);

	bool clickOnTroop(Board &board, Tile &from_tile);

    void printBoardHighlighted(Board& board,Troop *troop);

    void printAllHighlighted(Board& board, Troop *troop);

	void printAll(Board &board);

	Tile clickTile(Board &board);

	bool isWithinBoard() const;

    char startScreen();
    bool isWithinRange(const Sprite& sprite, Mouse& mouse);
};

#endif //CHESS_GAME_GUI_H
