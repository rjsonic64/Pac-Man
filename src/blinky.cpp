#include "ghosts.h"
#include "screen.h"

#include <iostream>

void Ghosts::blinkyBehaviour(Screen& screen) {
    auto& blinky = ghosts[0];
    std::pair<int, int> plr = screen.getPlr();

    Follow(screen, blinky, plr, 1);
}