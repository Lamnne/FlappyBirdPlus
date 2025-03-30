#include "FlappyBirdPlus.h"

int main(int argc, char* argv[])
{
    FlappyBirdGame game;
    game.showMenu();
    while (!game.shouldQuit)
    {
        SDL_Delay(16);
    }
    return 0;
}
