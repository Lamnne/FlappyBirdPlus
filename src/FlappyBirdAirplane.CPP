#include "FlappyBirdPlus.h"

void FlappyBirdGame::spawnAirplane()
{
    airplane = { SCREEN_WIDTH, 100 + rand() % (SCREEN_HEIGHT - 200), true, {} };
    airplaneActive = true;
    airplaneTimer = 600;
}
