#pragma once

#include <utility>
#include <optional>
#include <iostream>

class Screen;

class Ghosts {
private:
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

    std::unordered_map<int, Ghost> ghosts;

public:
    Ghosts() {
        Ghost Blinky;
        Blinky.currentDir = Movement::Up;
        ghosts.insert({1, Blinky});
    }

    // General movement
    void setMovement(std::pair<int, int>&, Screen&, Movement);

    // Define positions
    void setGhostPosition(std::pair<int, int>, int key);
    std::pair<int, Movement> checkTiles(Screen&, std::pair<int, int>&, std::pair<int, int>&, Movement);

    // Behaviours
    void Follow(Screen&, Ghost&, std::pair<int, int>&, std::pair<int, int>&);

    // Blinky
    void blinkyBehaviour(Screen&);
};