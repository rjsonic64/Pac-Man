#include "ghosts.h"
#include "screen.h"

#include <iostream>

void Ghosts::blinkyBehaviour(Screen& screen) {
    auto& blinky = ghosts.at(1);
    std::pair<int, int> plr = screen.getPlr();

    Follow(screen, blinky, blinky.loc, plr);
}