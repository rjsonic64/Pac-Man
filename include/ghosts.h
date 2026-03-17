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

    enum class ghostType {
        Blinky
    };

    struct Ghost {
        ghostType currentGhost;
        Movement currentDir;
        Behaviour currentBehaviour;
        std::pair<int, int> loc;
    };

    std::vector<Ghost> ghosts;

public:
    Ghosts() {
        Ghost Blinky;
        Blinky.currentGhost = ghostType::Blinky;
        Blinky.currentBehaviour = Behaviour::Follow;
        Blinky.currentDir = Movement::Up;
        ghosts.push_back(Blinky);
    }

    void ghostLoop(Screen&);
    void updateGhosts(Screen&, Ghost&, Behaviour);

    // General movement
    void setMovement(std::pair<int, int>&, Screen&, Movement, ghostType);
    auto sendGhostToScreen(ghostType);

    // Define positions
    void setGhostPosition(std::pair<int, int>, int key);
    std::pair<int, Movement> checkTiles(Screen&, std::pair<int, int>&, std::pair<int, int>&, Movement);

    // Behaviours
    void Follow(Screen&, Ghost&, std::pair<int, int>&, ghostType);
};