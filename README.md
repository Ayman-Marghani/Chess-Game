# Chess-Game

This chess game project was developed as part of the Algorithms course in the second term of the second year at Egypt University of Informatics. 
The project team consisted of Ayman Talat, Ahmed Waleed, Yassin Elsayed, and Mahmoud Ibrahim.
The game is implemented in C++ and utilizes the SFML (Simple and Fast Multimedia Library) as the GUI library. The development was done using the CLion IDE.

## Project Structure

- `Board.cpp`, `Board.h`: Implementations and declarations of the chess board functionality.
- `Game.cpp`, `Game.h`: Implementations and declarations of the main game logic.
- `Graveyard.cpp`, `Graveyard.h`: Implementations and declarations of the graveyard (captured pieces) functionality.
- `GUI.h`, `GUI.cpp`: Implementation of the graphical user interface using SFML.
- `Position.h`, `Position.cpp`: Implementations and declarations of the chess positions.
- `Tile.h`, `Tile.cpp`: Implementations and declarations of the chess tiles on the board.
- `Troop.cpp`, `Troop.h`: Implementations and declarations of the chess troops (pieces).
- `main.cpp`: The main entry point of the program.
- `CMakeLists.txt`: The CMake build configuration file.
- `.idea/`, `cmake-build-debug/`: Folders related to the IDE and build system.

## Game Features


- Two game modes: Player vs. Player (PvP) and Player vs. CPU.
- In the CPU mode, the game utilizes the minimax algorithm with a depth of 2 and optimized with alpha-beta pruning.
- Support for pawn promotion and castling.

## Prerequisites

Before running the game, ensure that you have the following dependencies installed:

- C++ compiler
- SFML Library

## Getting Started

1. Clone the repository:

   ```shell
   git clone https://github.com/Ayman-Talat/Chess-Game.git
   ```

2. Compile the code using CMake:

   ```shell
   cd Chess-Game/
   cmake .
   make
   ```

3. Run the game:

   ```shell
   ./Chess-Game.exe
   ```
