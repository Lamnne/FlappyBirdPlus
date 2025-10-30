#include "FlappyBirdPlus.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#define BIRD_X 100
bool pipesMoving = false;
int movingGroupStart = 0;
int movingGroupEnd = 0;
int moveWaveTimer = 0;

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
            else if ((e.type == SDL_KEYDOWN &&
                     (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)) ||
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


    if (!airplaneActive && pipesSinceLastAirplane > 5)
    {
        int chance = rand() % 100;
        if (chance <= 50)
        {
            airplaneActive = true;
            airplane.active = true;
            airplane.y = 50 + rand() % (SCREEN_HEIGHT - 150);
            airplane.movingUp = true;
            airplane.speed = 4 + rand() % 5;
            airplane.moveTimer = 0;
            airplane.bullets.clear();
            airplaneTimer = 600;
            pipes.clear();
            pipesSinceLastAirplane = 0;
        }
    }


    if (airplaneActive && airplane.active)
    {
        if (airplane.movingUp)airplane.y -= 2;
        else airplane.y += 2;
        if (airplane.y < 50) airplane.movingUp = false;
        if (airplane.y > SCREEN_HEIGHT - 100) airplane.movingUp = true;
        airplane.moveTimer++;
        if (airplane.moveTimer % 60 == 0)
        {
            Bullet b{ airplane.x - 20, airplane.y + 20, true };
            airplane.bullets.push_back(b);
        }
        for (auto& b : airplane.bullets)
        {
            b.x -= 8;
            if (b.x < 0) b.active = false;
            bool hitBird = (b.active &&
                            b.x < 100 + BIRD_WIDTH &&
                            b.x + 10 > 100 &&
                            b.y < birdY + BIRD_HEIGHT &&
                            b.y + 4 > birdY);
            bool hitGroundOrCeiling = (birdY + BIRD_HEIGHT >= SCREEN_HEIGHT || birdY <= 0);
            if ((hitBird || hitGroundOrCeiling)&&!hasShield)
            {
                if (soundEnabled) Mix_PlayChannel(-1, crashSound, 0);
                SDL_Delay(200);
                End();
                showGameOverMenu();
                return;
            }
        }
        airplane.bullets.erase(remove_if(airplane.bullets.begin(), airplane.bullets.end(),[](const Bullet& b){ return !b.active;}), airplane.bullets.end());
        airplaneTimer--;
        if (airplaneTimer <= 0)
        {
            airplaneActive = false;
            airplane.active = false;
            score++;
            airplane.bullets.clear();
            generatePipe();
        }
    }
    else
    {
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
            if (pipe.isMoving)
            {
                int moveSpeedY = 1;
                if (pipe.movingUp)
                {
                    pipe.y -= moveSpeedY;
                    if (pipe.y < 50)
                        pipe.movingUp = false;
                }
                else
                {
                    pipe.y += moveSpeedY;
                    if (pipe.y > SCREEN_HEIGHT - PIPE_GAP - 150)
                        pipe.movingUp = true;
                }
            }
            if (hasShield)
            {
                if (pipe.x + PIPE_WIDTH <= BIRD_WIDTH && !pipe.hasPassed)
                {
                    pipe.hasPassed = true;
                    pipesSinceLastAirplane++;
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
                        pipeTopTextureIndex = (pipeTopTextureIndex + 1) % 5;
                        pipeBottomTextureIndex = (pipeBottomTextureIndex + 1) % 5;
                        pipeTopTexture = pipeTops[pipeTopTextureIndex];
                        pipeBottomTexture = pipeBottoms[pipeBottomTextureIndex];
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
                        pipeTopTextureIndex = (pipeTopTextureIndex + 1) % 5;
                        pipeBottomTextureIndex = (pipeBottomTextureIndex + 1) % 5;
                        pipeTopTexture = pipeTops[pipeTopTextureIndex];
                        pipeBottomTexture = pipeBottoms[pipeBottomTextureIndex];
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
    if (pipesMoving)
    {
        moveWaveTimer--;
        if (moveWaveTimer <= 0)
        {
            pipesMoving = false;
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
    pipeTopTexture = pipeTops[0];
    pipeTopTextureIndex = 0;
    pipeBottomTexture = pipeBottoms[0];
    pipeBottomTextureIndex = 0;
    generatePipe();
    pipeVelocity = INITIAL_PIPE_VELOCITY;
    currentBackground = backgroundTextures[0];
    currentBackgroundIndex = 0;
    airplaneActive = false;
    airplane.active = false;
    airplane.bullets.clear();
    airplane.x = SCREEN_WIDTH - 150;
    airplane.y = SCREEN_HEIGHT / 2;
    airplane.movingUp = true;
    airplane.timer = 0;
    airplane.speed = 0;
    airplane.moveTimer = 0;
    backgroundX = 0;
    backgroundSpeed = 2;
    airplaneTimer = 0;
}

void FlappyBirdGame::startGame()
{
    loadskin();
    resetGame();
    Start();
    run();
}
