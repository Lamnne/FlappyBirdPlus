#include "FlappyBirdPlus.h"
#include <algorithm>
using namespace std;

void FlappyBirdGame::generatePipe()
{
    int pipeHeight = rand() % (SCREEN_HEIGHT - PIPE_GAP - 100);
    bool direction = rand() % 2;
    bool isMoving = (rand() % 100 < 30);
    pipes.push_back({ SCREEN_WIDTH, pipeHeight, false, direction, isMoving });
    if (rand() % 100 < 30)
    {
        int coinY = pipeHeight + PIPE_GAP / 2 - 55;
        if (!isMoving && rand() % 100 < 30)
    {
        int coinY = pipeHeight + PIPE_GAP / 2 - 55;
        if (coinY < 50) coinY = 50;
else if (coinY > SCREEN_HEIGHT - 50) coinY = SCREEN_HEIGHT - 50;

        generateCoin(SCREEN_WIDTH + PIPE_WIDTH / 2 - 100, coinY);
    }
    }
}
