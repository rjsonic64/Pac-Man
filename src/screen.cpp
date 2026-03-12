#include "screen.h"
#include"ghosts.h"

#include <iostream>

void Screen::setBlockingFalse() {
    Screen::setNonBlocking(false);
}

std::vector<std::vector<Screen::TileType>> Screen::Init(std::vector<std::string>& map, Ghosts& ghosts) {
    std::vector<std::vector<TileType>> initMap((int)map.size(), std::vector<TileType>((int)map[0].length()));

    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[0].length(); x++) {
            switch (map[y][x]) {
                case '#' :
                    initMap[y][x] = TileType::Wall;
                    break;
                case '-' :
                    initMap[y][x] = TileType::Fence;
                    break;
                case '.' :
                    initMap[y][x] = TileType::Pellet;
                    pelletCount++;
                    break;
                case ' ' :
                    initMap[y][x] = TileType::Empty;
                    break;
                case 'P' :
                    initMap[y][x] = TileType::Player;
                    break;
                case 'B' :
                    initMap[y][x] = TileType::Blinky;
                    ghosts.setGhostPosition(std::make_pair(y, x), 1);
                    break;
            }
        }
    }

    return initMap;
}

void Screen::updateMap() {
    auto ref = TileMap;

    for (size_t y = 0; y < ref.size(); y++) {
        for (size_t x = 0; x < ref[0].size(); x++) {
            switch (ref[y][x]) {
                case TileType::Wall :
                    std::cout << '#';
                    break;
                case TileType::Fence :
                    std::cout << '-';
                    break;
                case TileType::Pellet :
                    std::cout << '.';
                    break;
                case TileType::Empty :
                    std::cout << ' ';
                    break;
                case TileType::Player :
                    std::cout << 'P';
                    break;
                case TileType::Blinky :
                    std::cout << 'B';
                    break;
            }
        }
        std::cout << '\n';
    }
}

// Screen-Object Interaction
std::pair<int, int> Screen::playerCoord(std::vector<std::vector<Screen::TileType>>& ref) {
    for (size_t y = 0; y < ref.size(); y++) {
        for (size_t x = 0; x < ref[0].size(); x++) {
            if (ref[y][x] == Screen::TileType::Player) {
                return std::make_pair(y, x);
            }
        }
    }
    return std::make_pair(0, 0); // error case
}

bool Screen::hasAllPickups() {
    if (pelletCount <= 0) return true;
    return false;
}

void Screen::relayPlayerInput(int inputChangeX, int inputChangeY) { // Input Reader/Collision check
    TileMap[plrCoords.first][plrCoords.second] = TileType::Empty;

    if (TileMap[plrCoords.first + inputChangeY][plrCoords.second] == TileType::Pellet) {
        pelletCount--;
    }
    if (TileMap[plrCoords.first][plrCoords.second + inputChangeX] == TileType::Pellet) {
        pelletCount--;
    }

    plrCoords.first = (TileMap[plrCoords.first + inputChangeY][plrCoords.second] == TileType::Wall || TileMap[plrCoords.first + inputChangeY][plrCoords.second] == TileType::Fence) ? plrCoords.first : plrCoords.first + inputChangeY;
    plrCoords.second = (TileMap[plrCoords.first][(plrCoords.second + inputChangeX + (int)TileMap[0].size()) % (int)TileMap[0].size()] == TileType::Wall || TileMap[plrCoords.first][(plrCoords.second + inputChangeX + (int)TileMap[0].size()) % (int)TileMap[0].size()] == TileType::Fence) ? plrCoords.second : (plrCoords.second + inputChangeX + (int)TileMap[0].size()) % (int)TileMap[0].size();

    TileMap[plrCoords.first][plrCoords.second] = TileType::Player;
}

std::pair<int, int> Screen::getPlr() {
    return plrCoords;
}

void Screen::relayGhostInput(std::pair<int, int>& coords, int inputChangeY, int inputChangeX) {
    TileType prev = TileMap[coords.first][coords.second];
    TileMap[coords.first][coords.second] = TileType::Empty;

    coords.first += inputChangeY;
    coords.second += inputChangeX;

    TileMap[coords.first][coords.second] = prev;
}

// Ghost Collision detection
bool Screen::isWallUp(std::pair<int, int>& coords) {
    if (TileMap[coords.first - 1][coords.second] == TileType::Wall) return true;
    return false;
}

bool Screen::isWallDown(std::pair<int, int>& coords) {
    if (TileMap[coords.first + 1][coords.second] == TileType::Wall) return true;
    return false;
}

bool Screen::isWallLeft(std::pair<int, int>& coords) {
    if (TileMap[coords.first][coords.second - 1] == TileType::Wall) return true;
    return false;
}

bool Screen::isWallRight(std::pair<int, int>& coords) {
    if (TileMap[coords.first][coords.second + 1] == TileType::Wall) return true;
    return false;
}