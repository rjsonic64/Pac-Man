#include "pac-man.h"

#include <iostream>

bool Player::kbhit() {
    fd_set set;
    struct timeval tv = {0, 0};
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    return select(STDIN_FILENO + 1, &set, nullptr, nullptr, &tv) > 0;
}

// Movement
void Player::inputHandling(const char& input, Screen& plrScreen) {
    switch (input) {
        case 'w' :
            moveDirection(plrScreen, Player::Movement::Up);
            break;
        case 's' :
            moveDirection(plrScreen, Player::Movement::Down);
            break;
        case 'd' :
            moveDirection(plrScreen, Player::Movement::Right);
            break;
        case 'a' :
            moveDirection(plrScreen, Player::Movement::Left);
            break;
    }
}

void Player::moveDirection(Screen& plrScreen, Player::Movement direction) {
    switch (direction) {
        case Player::Movement::Up :
            plrScreen.relayPlayerInput(0, -1);
            break;
        case Player::Movement::Down :
            plrScreen.relayPlayerInput(0, 1);
            break;
        case Player::Movement::Right :
            plrScreen.relayPlayerInput(1, 0);
            break;
        case Player::Movement::Left :
            plrScreen.relayPlayerInput(-1, 0);
            break;
    }
}