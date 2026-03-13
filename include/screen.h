#pragma once

#include "ghosts.h"

#include <termios.h>
#include <unistd.h>
#include <utility>
#include <vector>
#include <iostream>

class Ghosts;

class Screen {
private:
    enum class TileType {
        Empty,
        Wall,
        Fence,
        Pellet,
        Player,
        Blinky
    };
    std::vector<std::string> map = {
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#@#  #.#   #.##.#   #.#  #@#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "     #.##### ## #####.#     ",
        "     #.##          ##.#     ",
        "     #.## ###--### ##.#     ",
        "######.## #      # ##.######",
        "      .   #   B  #   .      ",
        "######.## #      # ##.######",
        "     #.## ######## ##.#     ",
        "     #.##     P    ##.#     ",
        "     #.## ######## ##.#     ",
        "######.## ######## ##.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#@..##.......  .......##..@#",
        "###.##.##.########.##.##.###",
        "###.##.##.########.##.##.###",
        "#......##....##....##......#",
        "#.##########.##.##########.#",
        "#.##########.##.##########.#",
        "#..........................#",
        "############################"
    };

    int pelletCount;
    std::vector<std::vector<TileType>> TileMap;

    // Player location
    std::pair<int, int> plrCoords;

    std::vector<std::vector<TileType>> Init(std::vector<std::string>&, Ghosts&);
    static std::pair<int, int> playerCoord(std::vector<std::vector<TileType>>&);

    void setNonBlocking(bool enable) {
        struct termios ttystate;
        tcgetattr(STDIN_FILENO, &ttystate);

        if (enable) {
            ttystate.c_lflag &= ~ICANON; // disable line buffering
            ttystate.c_lflag &= ~ECHO;   // disable echo
            ttystate.c_cc[VMIN] = 0;     // min chars to read
            ttystate.c_cc[VTIME] = 0;    // no timeout
        } else {
            ttystate.c_lflag |= ICANON;  // restore canonical mode
            ttystate.c_lflag |= ECHO;    // restore echo
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

public:
    Screen(Ghosts& ghosts) : pelletCount(0), TileMap(Init(map, ghosts)), plrCoords(playerCoord(TileMap)) { setNonBlocking(true); }

    // Setup
    bool hasAllPickups();

    // Manage Screen
    void updateMap();
    void setBlockingFalse();

    // Screen-Object Interaction
    void relayPlayerInput(int, int);
    std::pair<int, int> getPlr();

    void relayGhostInput(std::pair<int, int>&, int, int);

    // Ghost collision detection
    bool isWallUp(std::pair<int, int>&);
    bool isWallDown(std::pair<int, int>&);
    bool isWallLeft(std::pair<int, int>&);
    bool isWallRight(std::pair<int, int>&);
};

// Screen/Renderer header file