#include "FlappyBirdPlus.h"
#include <algorithm>
#include <iostream>
#define BIRD_X 100

void FlappyBirdGame::run()
{
    SDL_Event e;
    playGameMusic();
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            else if ((e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)) ||
                     (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT))
            {
                GRAVITY = 1;
                birdVelocity = -JUMP_STRENGTH;
                if (soundEnabled)Mix_PlayChannel(-1, jumpSound, 0);
            }
        }
        if (!shouldQuit)
        {
            updateGame();
            render();
            SDL_Delay(16);
        }
    }
}

void FlappyBirdGame::updateGame()
{
    birdVelocity += GRAVITY;
    birdY += birdVelocity;
    if (birdY < 0) birdY = 0;
    if (birdY + BIRD_HEIGHT > SCREEN_HEIGHT)birdY = SCREEN_HEIGHT - BIRD_HEIGHT;
    birdRect.y = birdY;
    for (auto& shield : shields)
    {
        shield.x -= pipeVelocity;
    }
    shieldTimer++;
    if (shieldTimer >= 300 && shields.size() < 1)
    {
        generateShield();
        shieldTimer = 0;
    }
    checkShieldCollision();
    for (auto& coin : coins)
    {
        coin.x -= pipeVelocity;
    }
    checkCoinCollision();
    coins.erase(remove_if(coins.begin(), coins.end(), [](const Coin& c)
    {
        return c.x < -20;
    }), coins.end());

    shields.erase(remove_if(shields.begin(), shields.end(), [](const Shield& s)
    {
        return s.x < -20;
    }), shields.end());
    if (!pipes.empty() && pipes.back().x < SCREEN_WIDTH - 300)
    {
        generatePipe();
    }
    vector<Pipe> remainingPipes;

    for (const auto& pipe : pipes)
    {
        if (pipe.x + PIPE_WIDTH > 0)
        {
            remainingPipes.push_back(pipe);
        }
    }
    pipes = remainingPipes;
    for (auto& pipe : pipes)
    {
        pipe.x -= pipeVelocity;
        if (hasShield)
        {
            if (pipe.x + PIPE_WIDTH <= BIRD_WIDTH && !pipe.hasPassed)
            {
                pipe.hasPassed = true;
                score++;
                shieldCount++;
                if (score % 10 == 0)
                {
                    pipeVelocity++;
                }
                if (score % 5 == 0)
                {
                    currentBackgroundIndex = (currentBackgroundIndex + 1) % 5;
                    currentBackground = backgroundTextures[currentBackgroundIndex];
                }
                if (shieldCount >= 3)
                {
                    hasShield = false;
                    shieldCount = 0;
                }
            }
            continue;
        }
        else
        {
            if (pipe.x + PIPE_WIDTH <= BIRD_WIDTH&&pipe.hasPassed==false)
            {
                score++;
                pipesPassed++;
                pipe.hasPassed = true;
                if (score % 10 == 0)
                {
                    pipeVelocity++;
                }
                if (score % 5 == 0)
                {
                    currentBackgroundIndex = (currentBackgroundIndex + 1) % 5;
                    currentBackground = backgroundTextures[currentBackgroundIndex];
                }
            }
            bool hitPipe = (pipe.x < BIRD_X + BIRD_WIDTH && pipe.x + PIPE_WIDTH > BIRD_X) &&
                                         (birdY < pipe.y || birdY + BIRD_HEIGHT > pipe.y + PIPE_GAP) &&
                                         (pipe.x + PIPE_WIDTH > BIRD_X);
            bool hitGroundOrCeiling = (birdY + BIRD_HEIGHT >= SCREEN_HEIGHT || birdY <= 0);
            if (hitPipe || hitGroundOrCeiling)
            {
                if (soundEnabled) Mix_PlayChannel(-1, crashSound, 0);
                SDL_Delay(200);
                totalCoins += coinCount;
                saveTotalCoins();
                coinCount = 0;
                End();
                showGameOverMenu();
                return;
            }
        }
    }
}

void FlappyBirdGame::resetGame()
{
    GRAVITY = 0;
    birdY = SCREEN_HEIGHT / 2-100;
    birdVelocity = 0;
    score = 0;
    coinCount = 0;
    pipes.clear();
    coins.clear();
    shields.clear();
    hasShield = false;
    shieldCount = 0;
    shieldTimer = 0;
    generatePipe();
    pipeVelocity = INITIAL_PIPE_VELOCITY;
    currentBackground = backgroundTextures[0];
    currentBackgroundIndex = 0;
}

void FlappyBirdGame::startGame()
{
    loadskin();
    resetGame();
    Start();
    run();
}
