cmake_minimum_required(VERSION 3.21.1)
project(Chess_Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chess_Game main.cpp Board.cpp Board.h Tile.cpp Tile.h Position.cpp Position.h Troop.cpp Troop.h Graveyard.h Graveyard.cpp Game.cpp Game.h GUI.cpp GUI.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(Chess_Game sfml-system sfml-window sfml-graphics sfml-audio)