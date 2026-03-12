#include "screen.h"
#include "pac-man.h"
#include "ghosts.h"

#include<thread>
#include<chrono>
#include <iostream>

using namespace std;

int main() {
    Ghosts ghost;
    Screen screen(ghost);
    Player plr;

    bool GameLoop = true;
    char input = 'w';

    while (GameLoop) {
        if (screen.hasAllPickups()) break;

        if (plr.kbhit()) {
            char c;
            read(STDIN_FILENO, &c, 1);
            
            switch (c) {
                case 'w' :
                    input = 'w';
                    break;
                case 's' :
                    input = 's';
                    break;
                case 'a' :
                    input = 'a';
                    break;
                case 'd' :
                    input = 'd';
                    break;
            }
        }

        plr.inputHandling(input, screen);
        ghost.blinkyBehaviour(screen);
        screen.updateMap();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    return 0;
}