#include "GUI.h"

// Square class to represent each square on the chess board
Square::Square() = default;

Square::Square(bool color) {
    setSize(sf::Vector2f(60, 60));

    setFillColor(color ? sf::Color::Red : sf::Color::Black);
}

Square::Square(int R, int G, int B, int A) {
    setSquare(R, G, B, A);
}

void Square::setSquare(int R, int G, int B, int A) {
    setSize(sf::Vector2f(60, 60));
    this->setFillColor(Color(R, G, B, A));
}

//Set the window size and name.
void GUI::setWindow() {
    window.create(VideoMode(1280, 720), "WeChess");
    window.setFramerateLimit(120);
}

//Constructor to create the tiles and the window.
GUI::GUI() {
    setWindow();
    Square white_obj(true);
    Square black_obj(false);
    white = white_obj;
    black = black_obj;
    white.setFillColor(sf::Color(115, 44, 11, 210));
    black.setFillColor(sf::Color(240, 210, 164, 210));
    BOARD_X = 400.0;
    BOARD_Y = 120;
    TILE_SIZE = 60;

    // Load the background image
    background_texture.loadFromFile("Img SRC/Wood background.jpg");
    background_sprite.setTexture(background_texture);
    background_sprite.setScale(1280.0 / 612.0, 720.0 / 408.0);

    // Load endgame images
    white_win_texture.loadFromFile("Img SRC/white_wins.png");
    white_win_sprite.setTexture(white_win_texture);
    white_win_sprite.setScale(1280.0 / 1600.0, 720.0 / 900.0);

    black_win_texture.loadFromFile("Img SRC/black_wins.png");
    black_win_sprite.setTexture(black_win_texture);
    black_win_sprite.setScale(1280.0 / 1600.0, 720.0 / 900.0);

    draw_texture.loadFromFile("Img SRC/draw.png");
    draw_sprite.setTexture(draw_texture);
    draw_sprite.setScale(1280.0 / 1600.0, 720.0 / 900.0);

    // Load white troops images
    troops_textures['P'].loadFromFile("Img SRC/White Troops/P.png");
    troops_sprites['P'].setTexture(troops_textures['P']);
    troops_textures['B'].loadFromFile("Img SRC/White Troops/B.png");
    troops_sprites['B'].setTexture(troops_textures['B']);
    troops_textures['Q'].loadFromFile("Img SRC/White Troops/Q.png");
    troops_sprites['Q'].setTexture(troops_textures['Q']);
    troops_textures['K'].loadFromFile("Img SRC/White Troops/K.png");
    troops_sprites['K'].setTexture(troops_textures['K']);
    troops_textures['N'].loadFromFile("Img SRC/White Troops/N.png");
    troops_sprites['N'].setTexture(troops_textures['N']);
    troops_textures['R'].loadFromFile("Img SRC/White Troops/R.png");
    troops_sprites['R'].setTexture(troops_textures['R']);

    // Load black troops images
    troops_textures['p'].loadFromFile("Img SRC/Black Troops/p.png");
    troops_sprites['p'].setTexture(troops_textures['p']);
    troops_textures['b'].loadFromFile("Img SRC/Black Troops/b.png");
    troops_sprites['b'].setTexture(troops_textures['b']);
    troops_textures['q'].loadFromFile("Img SRC/Black Troops/q.png");
    troops_sprites['q'].setTexture(troops_textures['q']);
    troops_textures['k'].loadFromFile("Img SRC/Black Troops/k.png");
    troops_sprites['k'].setTexture(troops_textures['k']);
    troops_textures['n'].loadFromFile("Img SRC/Black Troops/n.png");
    troops_sprites['n'].setTexture(troops_textures['n']);
    troops_textures['r'].loadFromFile("Img SRC/Black Troops/r.png");
    troops_sprites['r'].setTexture(troops_textures['r']);

    // Load the font of numbers and character in the border
    font.loadFromFile("Img SRC/Fonts/Roboto-Black.ttf");
    text.setFont(font);
    text.setCharacterSize(12);

    // Squares
    light.setSquare(80, 24, 5, 180);
    dark.setSquare(223, 200, 158, 180);
    light_red.setSquare(227, 89, 84, 210);
    dark_red.setSquare(251, 75, 34, 210);
    light_blue.setSquare(209, 226, 255, 210);
    dark_blue.setSquare(134, 170, 255, 210);
}

void GUI::promote(Troop *troop) {
    if (troop->getColor()) {
        troop = new Troop("Q", troop->getColor(), troop->getPosition());
    } else {
        troop = new Troop("q", troop->getColor(), troop->getPosition());
    }
}

//Check a given drawn tile, if it has a troop on it then draw it above the tile.
void GUI::printPiece(Tile &tile, float x, float y) {
    Troop *troop = tile.getTroopOnTile();
    if (troop != nullptr) {
        char troop_name = troop->getName()[0];
        troops_sprites[troop_name].setPosition(x, y);
        troops_sprites[troop_name].setScale(0.33, 0.33);
        window.draw(troops_sprites[troop_name]);
    }
}

//Print all 64 tiles with all pieces on them.
void GUI::printBorder(Board &board)
{
    float x = BOARD_X, y = BOARD_Y;
    for(int i = 0; i < 8; i++) {
        if(i % 2 == 0)
        {
            text.setFillColor(Color::Black);
        }
        else
        {
            text.setFillColor(Color::White);
        }
        text.setString(to_string(i+1));
        text.setPosition(x,y+i*TILE_SIZE);
        window.draw(text);
    }
    x = BOARD_X+50;
    y = BOARD_Y+8*TILE_SIZE - 18;
    for(int i = 0; i < 8; i++)
    {
        if(i % 2 != 0)
        {
            text.setFillColor(Color::Black);
        }
        else
        {
            text.setFillColor(Color::White);
        }
        text.setString(char(i+48+49));
        text.setPosition(x+i*TILE_SIZE,y);
        window.draw(text);
    }
}
void GUI::printBoard(Board &board) {
    float x, y = BOARD_Y;
    for (int i = 0; i < 8; i++) {
        x = BOARD_X;
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 != 0) {
                white.setPosition(x, y);
                window.draw(white);
            } else {
                black.setPosition(x, y);
                window.draw(black);
            }
            game._board._board[i][j].setToZeroProtect();
            printPiece(board._board[i][j], x, y);
            x += TILE_SIZE;
        }
        y += TILE_SIZE;
    }
}

void GUI::printAll(Board &board) {
    window.clear();
    window.draw(background_sprite);
    printGraveyard(board);
    printBoard(board);
    printBorder(board);
    window.display();
}
void GUI::printBoardHighlighted(Board &board, Troop *troop) {
    float x, y = BOARD_Y;
    for (int i = 0; i < 8; i++) {
        x = BOARD_X;
        for (int j = 0; j < 8; j++) {
            bool is_white = ((i + j) % 2 != 0);

            if (troop == nullptr) {
                if (is_white) {
                    white.setPosition(x, y);//White tile with no troop
                    window.draw(white);
                } else {
                    black.setPosition(x, y);//Black tile with no troop
                    window.draw(black);
                }
                printPiece(board._board[i][j], x, y);
                x += TILE_SIZE;
                continue;
            } else if (troop->getPosition().getX() == i && troop->getPosition().getY() == j) {
                if (is_white) {
                    light.setPosition(x, y);
                    window.draw(light);
                } else {
                    dark.setPosition(x, y);
                    window.draw(dark);
                }
            } else if (troop->foundInLegal(i, j) && !is_white &&
                       board._board[i][j].getTroopOnTile() != nullptr) //Enemy troop on legal white tile.
            {
                light_red.setPosition(x, y);
                window.draw(light_red);
            } else if (troop->foundInLegal(i, j) && is_white &&
                       board._board[i][j].getTroopOnTile() != nullptr)//Enemy troop on legal black tile.
            {
                dark_red.setPosition(x, y);
                window.draw(dark_red);
            } else if (troop->foundInLegal(i, j) && !is_white &&
                       !board._board[i][j].getTroopOnTile())//No troop on legal white tile
            {
                light_blue.setPosition(x, y);
                window.draw(light_blue);
            } else if (troop->foundInLegal(i, j) && is_white &&
                       !board._board[i][j].getTroopOnTile())//No troop on legal black tile
            {
                dark_blue.setPosition(x, y);
                window.draw(dark_blue);
            } else {
                if (is_white)//White tile with no troop
                {
                    white.setPosition(x, y);
                    window.draw(white);
                } else //Black tile with no troop
                {
                    black.setPosition(x, y);
                    window.draw(black);
                }
            }
            printPiece(board._board[i][j], x, y);
            x += TILE_SIZE;
        }
        y += TILE_SIZE;
    }
}

void GUI::printGraveyard(Board &board) {
    Tile whatever;
    float x = BOARD_X - TILE_SIZE;
    float y = BOARD_Y;
    auto troop = board._black_grave._grave.begin();
    while(troop != board._black_grave._grave.end()) {
        if (y > BOARD_Y + 7 * TILE_SIZE) {
            y = BOARD_Y;
            x -= TILE_SIZE;
        }
        whatever.setX_Y(x, y);
        whatever.setTroopOnTile(*troop);
        printPiece(whatever, x, y);
        y += TILE_SIZE;
        troop++;
    }
    x = BOARD_X + 8 * TILE_SIZE;
    y = BOARD_Y;
    troop = board._white_grave._grave.begin();
    while(troop != board._white_grave._grave.end()) {
        if (y > BOARD_Y + 7 * TILE_SIZE) {
            y = BOARD_Y;
            x += TILE_SIZE;
        }
        whatever.setX_Y(x, y);
        whatever.setTroopOnTile(*troop);
        printPiece(whatever, x, y);
        y += TILE_SIZE;
        troop++;
    }
}

void GUI::printAllHighlighted(Board &board, Troop *troop) {
    window.clear();
    window.draw(background_sprite);
    printBoardHighlighted(board, troop);
    printGraveyard(board);
    printBorder(board);
    window.display();
}

Tile GUI::clickTile(Board &board) {
    float mouse_x = Mouse::getPosition(window).x;
    float mouse_y = Mouse::getPosition(window).y;
    //Check for which tile in the board we clicked
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((mouse_x >= BOARD_X + (j * TILE_SIZE)) && (mouse_x <= BOARD_X + (j + 1) * TILE_SIZE) &&
                (mouse_y >= BOARD_Y + (i * TILE_SIZE)) && (mouse_y <= BOARD_Y + (i + 1) * TILE_SIZE)) {
                return board._board[i][j];
            }
        }
    }
}

bool GUI::isWithinBoard() const {
    float mouse_x = Mouse::getPosition(window).x;
    float mouse_y = Mouse::getPosition(window).y;
    //Check if the click is within the board bounds
    if ((mouse_x <= 880) && (mouse_x >= 400) &&
        (mouse_y >= 120) && (mouse_y <= 600)) {
        return true;
    } else return false;
}

// this function will return false if one of the kings will die, otherwise it will return true
//When the mouse button is clicked on a tile that has a troop.
bool GUI::clickOnTroop(Board &board, Tile &from_tile) {
    while (true) {
        Event event;
        window.pollEvent(event);
        if (event.type == Event::Closed) {
            window.close();
            break;
        }
        if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left)) {
            //Get if the click is on a tile or not, if not stop highlighting the current troop.
            if (isWithinBoard()) {
                Tile to_tile = clickTile(board);
                //if the to tile is a legal move
                if (from_tile.getTroopOnTile()->foundInLegal(to_tile.getPosition().getX(),
                                                             to_tile.getPosition().getY())) {
                    board.move(from_tile.getPosition(), to_tile.getPosition());

                    //Promotion Condition
                    if(board._board[to_tile.getPosition().getX()][to_tile.getPosition().getY()].promote())
                        board.last_move_stack.top().is_last_move_promote  = true;
                    //refresh the legal moves for all the pieces if the black has just played

                    if (game.num_moves % 2) {

                        game.storeBlackMoves();

                        game.storeWhiteMoves();
                    }
                        //refresh the legal moves for all the pieces if the white has just played
                    else {

                        game.storeWhiteMoves();

                        game.storeBlackMoves();
                    }

                    //increment the number of moves counter
                    game.num_moves++;

                }

            }
            break;

        }
        printAllHighlighted(board, from_tile.getTroopOnTile());
    }
    return true;
}

void GUI::endGame(int status)
{
    if (status == 1) {
        while(window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    break;
                }
                window.clear();
                window.draw(white_win_sprite);
                window.display();
            }
        }
    }
    else if (status == 2) {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    break;
                }
                window.clear();
                window.draw(black_win_sprite);
                window.display();
            }
        }
    }
    else if (status == 3) {
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                    break;
                }
                window.clear();
                window.draw(draw_sprite);
                window.display();
            }
        }
    }
}

//SFML functionality to display everything on screen.s
int GUI::display() {
    char game_mode = startScreen();
    int game_status;
    game.game_mode_on_game = game_mode;
    game._board.game_mode_on_board = game_mode;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            game_status = game.checkStatus();
            if (game_status != 0) {
                return game_status;
            }
            if (event.type == Event::Closed) {
                window.close();
                break;
            }
            if (game_mode == 'c' && game.num_moves % 2 != 0)
            {
                game_status = game.checkStatus();
                if (game_status != 0) {
                    return game_status;
                }
                game.makeMove();

                game.storeBlackMoves();
                game.storeWhiteMoves();

                game.num_moves++;
                continue;
            }
            if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left)) {
                game_status = game.checkStatus();
                if (game_status != 0) {
                    return game_status;
                }
                if (isWithinBoard()) {
                    //Check for which tile in the board we clicked
                    Tile current_tile = clickTile(game._board);
                    //Check if the tile has a valid troop.
                    if (current_tile.getTroopOnTile() != nullptr) {
                        //Go into the main function, to highlight.
                        if (current_tile.getTroopOnTile()->getColor() == (game.num_moves % 2 == 0)) {
                            clickOnTroop(game._board, current_tile);
                        }
                    }
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if(game._board.undoMove())
                    {
                        game.num_moves--;
                    }
                    //store_legal_moves
                    if (game.num_moves % 2) {
                        game.storeBlackMoves();
                        game.storeWhiteMoves();
                    }
                        //refresh the legal moves for all the pieces if the white has just played
                    else {
                        game.storeWhiteMoves();
                        game.storeBlackMoves();
                    }
                }
            }
        }
        printAll(game._board);
    }
}


bool GUI::isWithinRange(const Sprite& sprite, Mouse& mouse)
{
    float mouse_x = mouse.getPosition(window).x;
    float mouse_y = mouse.getPosition(window).y;
    float s_x = sprite.getPosition().x;
    float s_y = sprite.getPosition().y;
    float s_width = sprite.getGlobalBounds().width-25;
    float s_height = sprite.getGlobalBounds().height-25;

    if ((mouse_x < s_x + s_width) && (mouse_x > s_x) && (mouse_y < s_y + s_height) && (mouse_y > s_y))
    {
        return true;
    }
    return false;
}


char GUI::startScreen()
{
    Sprite bg;
    Texture texture;
    texture.loadFromFile("Img SRC/start_screen.png");
    bg.setTexture(texture);
    bg.setScale(1280.0/1920.0 , 720.0/1080.0);

    Sprite pvp;
    Texture texture_pvp;
    texture_pvp.loadFromFile("Img SRC/pvp.png");
    pvp.setPosition(500.0 , 360.0- 175);
    pvp.setTexture(texture_pvp);

    Sprite pvp_selected;
    Texture texture_pvp_selected;
    texture_pvp_selected.loadFromFile("Img SRC/pvp_selected.png");
    pvp_selected.setTexture(texture_pvp_selected);
    pvp_selected.setPosition(500.0 ,  360.0- 175);

    Sprite cpu;
    Texture texture_cpu;
    texture_cpu.loadFromFile("Img SRC/cpu.png");
    cpu.setPosition(500.0 , 360.0);
    cpu.setTexture(texture_cpu);

    Sprite cpu_selected;
    Texture texture_cpu_selected;
    texture_cpu_selected.loadFromFile("Img SRC/cpu_selected.png");
    cpu_selected.setTexture(texture_cpu_selected);
    cpu_selected.setPosition(500.0 , 360.0);

    while(window.isOpen())
    {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {

                window.close();
                return 'x';
            }
            while(isWithinRange(pvp,mouse))
            {
                window.pollEvent(event);
                if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
                {
                    window.clear();
                    return 'p';
                }
                window.clear();
                window.draw(bg);
                window.draw(pvp_selected);
                window.draw(cpu);
                window.display();
            }
            while( isWithinRange(cpu,mouse))
            {

                window.pollEvent(event);
                if(event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Left))
                {
                    window.clear();
                    return 'c';
                }
                window.clear();
                window.draw(bg);
                window.draw(pvp);
                window.draw(cpu_selected);
                window.display();
            }

            window.clear();
            window.draw(bg);
            window.draw(pvp);
            window.draw(cpu);
            window.display();
        }
    }
}