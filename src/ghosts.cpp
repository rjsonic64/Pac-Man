#include "ghosts.h"
#include "screen.h"

#include <vector>
#include <iostream>

void Ghosts::setMovement(std::pair<int, int>& coords, Screen& screen, Movement move) {
    switch (move) {
        case Movement::Up :
            screen.relayGhostInput(coords, -1, 0);
            break;
        case Movement::Down :
            screen.relayGhostInput(coords, 1, 0);
            break;
        case Movement::Left :
            screen.relayGhostInput(coords, 0, -1);
            break;
        case Movement::Right :
            screen.relayGhostInput(coords, 0, 1);
            break;
    }
}

void Ghosts::setGhostPosition(std::pair<int, int> coords, int key) {
    ghosts.at(key).loc = coords;
}

// Behaviours
void Ghosts::Follow(Screen& screen, Ghost& caller, std::pair<int, int>& ghostCoords, std::pair<int, int>& plrCoords) {
    // splitting the values returned from checkTiles function every frame instead of calling it multiple times
    int intersections = checkTiles(screen, ghostCoords, plrCoords, caller.currentDir).first;
    Movement newDir = checkTiles(screen, ghostCoords, plrCoords, caller.currentDir).second;

    switch (caller.currentDir) {
        case Movement::Up :
            if (screen.isWallUp(ghostCoords)) {
               caller.currentDir = newDir;
               break;
            }

            if (intersections >= 2) {
                caller.currentDir = newDir;
                std::cout << intersections;
            }
            break;
        case Movement::Down :
            if (screen.isWallDown(ghostCoords)) {
                caller.currentDir = newDir;
                break;
            }

            if (intersections >= 2) {
                caller.currentDir = newDir;
                std::cout << intersections;
            }
            break;
        case Movement::Left :
            if (screen.isWallLeft(ghostCoords)) {
                caller.currentDir = newDir;
                break;
            }

            if (intersections >= 2) {
                caller.currentDir = newDir;
                std::cout << intersections;
            }
            break;
        case Movement::Right :
            if (screen.isWallRight(ghostCoords)) {
                caller.currentDir = newDir;
                break;
            }

            if (intersections >= 2) {
                caller.currentDir = newDir;
                std::cout << intersections;
            }
            break;
    }
    
    setMovement(ghostCoords, screen, caller.currentDir);
}

// The formula is literally called the distance formula- remember that!!
std::pair<int, Ghosts::Movement> Ghosts::checkTiles(Screen& screen, std::pair<int, int>& ghostCoords, std::pair<int, int>& plrCoords, Movement currDirection) {
    int distLeft = 0;
    int distRight = 0;
    int distUp = 0;
    int distDown = 0;

    std::vector<int> distances;
    std::vector<Movement> options;

    // Cancel out reverse movement each frame/tile
    bool cancelUp = false;
    bool cancelDown = false;
    bool cancelLeft = false;
    bool cancelRight = false;

    int intersections = 0;

    switch (currDirection) {
        case Movement::Up :
            cancelDown = true;
            break;
        case Movement::Down :
            cancelUp = true;
            break;
        case Movement::Left :
            cancelRight = true;
            break;
        case Movement::Right :
            cancelLeft = true;
            break;
    }

    if (!screen.isWallLeft(ghostCoords) && !cancelRight) {
        distLeft = abs((ghostCoords.second - 1) - plrCoords.second) + abs(ghostCoords.first - plrCoords.first);
        distances.push_back(distLeft);
        options.push_back(Movement::Left);
        intersections++;
    }
    if (!screen.isWallRight(ghostCoords) && !cancelLeft) {
        distRight = abs((ghostCoords.second + 1) - plrCoords.second) + abs(ghostCoords.first - plrCoords.first);
        distances.push_back(distRight);
        options.push_back(Movement::Right);
        intersections++;
    }
    if (!screen.isWallDown(ghostCoords) && !cancelUp) {
        distDown = abs(ghostCoords.second - plrCoords.second) + abs((ghostCoords.first + 1) - plrCoords.first);
        distances.push_back(distDown);
        options.push_back(Movement::Down);
        intersections++;
    }
    if (!screen.isWallUp(ghostCoords) && !cancelDown) {
        distUp = abs(ghostCoords.second - plrCoords.second) + abs((ghostCoords.first - 1) - plrCoords.first);
        distances.push_back(distUp);
        options.push_back(Movement::Up);
        intersections++;
    }

    int minIndex = 0;
    for (size_t i = 1; i < distances.size(); i ++) {
        if (distances[i] < distances[minIndex]) {
            minIndex = i;
        }
    }

    return {intersections, options[minIndex]};
}