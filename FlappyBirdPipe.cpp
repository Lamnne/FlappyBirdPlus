#include "FlappyBirdPlus.h"

void FlappyBirdGame::generatePipe()
{
    int pipeHeight = rand() % (SCREEN_HEIGHT - PIPE_GAP);
    pipes.push_back({ SCREEN_WIDTH, pipeHeight, false });
}
