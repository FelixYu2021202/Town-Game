// Game by cosf
// v0.7.2
// build 2023.7.13
// unf
// for more details please go to http://ac.hfoj.net/blog/35/6464e26c426c19a595da2748#1684333164277

// Utilities

#include "tg.h"

// Game Board

GameBoard gb;

// Game Start
int main()
{
    if (gb.game_start())
    {
        cout << "Game did not exit normally." << endc;
        return -1;
    }
    return 0;
}
