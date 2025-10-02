#include "FlappyBirdPlus.h"
#include <iostream>
bool FlappyBirdGame::isPositionValid(int x, int y, int width, int height)
{
    SDL_Rect shieldRect = { x, y, width, height };
    for (const auto& coin : coins)
    {
        if (!coin.collected)
        {
            SDL_Rect coinRect = { coin.x, coin.y, 100, 100 };
            if (SDL_HasIntersection(&shieldRect, &coinRect))
                return false;
        }
    }
    for (const auto& pipe : pipes)
    {
        SDL_Rect topPipeRect = { pipe.x, 0, PIPE_WIDTH, pipe.y };
        SDL_Rect bottomPipeRect = { pipe.x, pipe.y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipe.y - PIPE_GAP };
        if (SDL_HasIntersection(&shieldRect, &topPipeRect) || SDL_HasIntersection(&shieldRect, &bottomPipeRect))
            return false;
    }
    return true;
}

void FlappyBirdGame::generateShield()
{
    if (pipesPassed < 5) return;
    if (rand() % 10 < 9&&score>=8)
    {
        const int SHIELD_WIDTH = 50;
        const int SHIELD_HEIGHT = 50;
        const int MAX_SHIELDS = 1;
        if (shields.size() >= MAX_SHIELDS) return;
        int x, y;
        bool validPosition = false;
        int attempts = 0;
        const int MAX_ATTEMPTS = 10;
        while (!validPosition && attempts < MAX_ATTEMPTS)
        {
            x = rand() % (SCREEN_WIDTH - SHIELD_WIDTH - PIPE_WIDTH) + PIPE_WIDTH;
            y = rand() % (SCREEN_HEIGHT - SHIELD_HEIGHT - 50) + 50;
            validPosition = isPositionValid(x, y, SHIELD_WIDTH, SHIELD_HEIGHT);
            attempts++;
        }
        if (validPosition)
        {
            Shield newShield;
            newShield.x = x;
            newShield.y = y;
            newShield.collected = false;
            shields.push_back(newShield);
            pipesPassed = 0;
        }
    }
}

void FlappyBirdGame::checkShieldCollision()
{
    for (auto& shield : shields)
    {
        if (!shield.collected &&
                birdRect.x + BIRD_WIDTH >= shield.x && birdRect.x <= shield.x + 50 &&
                birdRect.y + BIRD_HEIGHT >= shield.y && birdRect.y <= shield.y + 50)
        {
            shield.collected = true;
            hasShield = true;
            shieldCount = 0;
            if (soundEnabled) Mix_PlayChannel(-1, shieldSound, 0);
        }
    }
}
