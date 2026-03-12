#pragma once

#include "screen.h"

#include <iostream>

class Player {
private:
    enum class Movement {
        Up,
        Down,
        Left,
        Right
    };

public:
    // Input
    bool kbhit();
    void inputHandling(const char& c, Screen&);

    // Movement
    void moveDirection(Screen&, Player::Movement);
};

// Player/AI header