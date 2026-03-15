#include "ghosts.h"
#include "screen.h"

#include <vector>
#include <string>
#include <iostream>

void Ghosts::setMovement(std::pair<int, int>& coords, Screen& screen, Movement move, int key) {
    switch (move) {
        case Movement::Up :
            screen.relayGhostInput(coords, -1, 0, key);
            break;
        case Movement::Down :
            screen.relayGhostInput(coords, 1, 0, key);
            break;
        case Movement::Left :
            screen.relayGhostInput(coords, 0, -1, key);
            break;
        case Movement::Right :
            screen.relayGhostInput(coords, 0, 1, key);
            break;
    }
}

void Ghosts::setGhostPosition(std::pair<int, int> coords, int key) {
    ghosts[key].loc = coords;
}

// Behaviours
void Ghosts::Follow(Screen& screen, Ghost& caller, std::pair<int, int>& plrCoords, int key) {
    // splitting the values returned from checkTiles function every frame instead of calling it multiple times
    auto collisionCheck = checkTiles(screen, caller.loc, plrCoords, caller.currentDir);
    int intersections = collisionCheck.first;
    Movement newDir = collisionCheck.second;

    bool hitwall = false;

    switch (caller.currentDir) {
        case Movement::Up :
            hitwall = screen.isWallUp(caller.loc);
            break;
        case Movement::Down :
            hitwall = screen.isWallDown(caller.loc);
            break;
        case Movement::Left :
            hitwall = screen.isWallLeft(caller.loc);
            break;
        case Movement::Right :
            hitwall = screen.isWallRight(caller.loc);
            break;
    }

    if (hitwall || intersections >= 2) {
        caller.currentDir = newDir;
    }

    int index;
    switch (key) {
        case 1 :
            index = 0;
            break;
    }
    
    setMovement(caller.loc, screen, caller.currentDir, index);
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

    bool isWallUp = false;
    bool isWallDown = false;

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

    if (!screen.isWallLeft(ghostCoords) && !cancelLeft) {
        distLeft = abs((ghostCoords.second - 1) - plrCoords.second) + abs(ghostCoords.first - plrCoords.first);
        distances.push_back(distLeft);
        options.push_back(Movement::Left);
        intersections++;
    }
    if (!screen.isWallRight(ghostCoords) && !cancelRight) {
        distRight = abs((ghostCoords.second + 1) - plrCoords.second) + abs(ghostCoords.first - plrCoords.first);
        distances.push_back(distRight);
        options.push_back(Movement::Right);
        intersections++;
    }
    if (!screen.isWallDown(ghostCoords) && !cancelDown) {
        distDown = abs(ghostCoords.second - plrCoords.second) + abs((ghostCoords.first + 1) - plrCoords.first);
        distances.push_back(distDown);
        options.push_back(Movement::Down);
        intersections++;
    } else {
        isWallDown = true;
    }
    if (!screen.isWallUp(ghostCoords) && !cancelUp) {
        distUp = abs(ghostCoords.second - plrCoords.second) + abs((ghostCoords.first - 1) - plrCoords.first);
        distances.push_back(distUp);
        options.push_back(Movement::Up);
        intersections++;
    } else {
        isWallUp = true;
    }

    // Evaluate Y distance(Prioritize Y gap over X)
    int rawYGhost = ghostCoords.first;
    int rawYPlr = plrCoords.first;

    if (rawYGhost - rawYPlr > 0) {
        if (!cancelUp && !isWallUp) return {intersections, Movement::Up};
    }
    if (rawYGhost - rawYPlr < 0) {
        if (!cancelDown && !isWallDown) return {intersections, Movement::Down};
    }

    int minIndex = 0;
    for (size_t i = 1; i < distances.size(); i ++) {
        if (distances[i] < distances[minIndex]) {
            minIndex = i;
        }
    }

    return {intersections, options[minIndex]};
}