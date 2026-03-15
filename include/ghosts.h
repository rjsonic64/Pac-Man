#pragma once

#include <utility>
#include <optional>
#include <string>
#include <vector>
#include <iostream>

class Screen;

class Ghosts {
private:
    enum class Behaviour {
        Follow
    };

    enum class Movement {
        Up,
        Down,
        Left,
        Right
    };

    struct Ghost {
        Movement currentDir;
        std::pair<int, int> loc;
    };

    std::vector<Ghost> ghosts;

public:
    Ghosts() {
        Ghost Blinky;
        Blinky.currentDir = Movement::Up;
        ghosts.push_back(Blinky);
    }

    // General movement
    void setMovement(std::pair<int, int>&, Screen&, Movement, int);

    // Define positions
    void setGhostPosition(std::pair<int, int>, int key);
    std::pair<int, Movement> checkTiles(Screen&, std::pair<int, int>&, std::pair<int, int>&, Movement);

    // Behaviours
    void Follow(Screen&, Ghost&, std::pair<int, int>&, int);

    // Blinky
    void blinkyBehaviour(Screen&);
};