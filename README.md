# Chess-Game

## Overview

Chess-Game is an advanced chess implementation developed as part of the Algorithms course at Egypt University of Informatics. This project showcases a fully functional chess game with both Player vs. Player (PvP) and Player vs. CPU modes, demonstrating the practical application of algorithmic concepts in game development.

## Key Features

- **Dual Game Modes**: 
  - Player vs. Player (PvP) for classic two-player matches
  - Player vs. CPU for solo play against an AI opponent
- **Advanced AI**: 
  - Utilizes the minimax algorithm with a depth of 2
  - Optimized with alpha-beta pruning for efficient decision-making
- **Complete Chess Ruleset**:
  - Supports all standard chess moves
  - Includes special moves like pawn promotion and castling
- **Graphical User Interface**: 
  - Built using SFML (Simple and Fast Multimedia Library) for a visually appealing and interactive experience

## Project Structure

The project is organized into several key components:

- `Board.cpp`, `Board.h`: Define the chess board and its operations
- `Game.cpp`, `Game.h`: Contain the core game logic and flow control
- `Graveyard.cpp`, `Graveyard.h`: Manage captured pieces
- `GUI.h`, `GUI.cpp`: Handle the graphical user interface using SFML
- `Position.h`, `Position.cpp`: Represent and manipulate chess positions
- `Tile.h`, `Tile.cpp`: Define individual tiles on the chess board
- `Troop.cpp`, `Troop.h`: Implement chess pieces (troops) and their movements
- `main.cpp`: Serves as the entry point of the application
- `CMakeLists.txt`: Configures the CMake build system

## Prerequisites

To run Chess-Game, ensure you have the following installed:

- C++ compiler (supporting C++11 or later)
- SFML Library (version 2.5 or later recommended)
- CMake (version 3.10 or later)

## Building and Running

1. Clone the repository:
   ```bash
   git clone https://github.com/Ayman-Marghani/Chess-Game.git
   ```


2. Navigate to the project directory:
   ```bash
   cd Chess-Game
   ```

3. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   ```

4. Generate the build files with CMake:
   ```bash
   cmake ..
   ```

5. Build the project:
   ```bash
   cmake --build .
   ```

6. Run the game:
   ```bash
   ./Chess-Game
   ```

## Gameplay Instructions
- Use the mouse to select and move chess pieces
- In PvP mode, players take turns making moves
- In CPU mode, make your move and the AI will respond automatically
- The game enforces all standard chess rules, including check and checkmate

## Development Team
This project was developed by:

- Ayman Marghani
- Ahmed Waleed
- Yassin Elsayed
- Mahmoud Ibrahim


## Contributing
We welcome contributions to improve Chess-Game. Please feel free to fork the repository, make changes, and submit pull requests.