#include "FlappyBirdPlus.h"

void FlappyBirdGame::resetRenderer()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void FlappyBirdGame::showMenu()
{
    SDL_Event e;
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN &&
                e.button.button == SDL_BUTTON_LEFT &&
                e.type != SDL_QUIT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= playButtonRect.x &&
                    mouseX <= 740 &&
                    mouseY >= playButtonRect.y &&
                    mouseY <= playButtonRect.y + playButtonRect.h)
                {
                    resetRenderer();
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    startGame();
                    return;
                }
                if (mouseX >= exitButtonRect.x &&
                    mouseX <= 780 &&
                    mouseY >= exitButtonRect.y &&
                    mouseY <= exitButtonRect.y + exitButtonRect.h)
                {
                    shouldQuit = true;
                    break;
                }
                if (mouseX >= settingButtonRect.x &&
                    mouseX <= settingButtonRect.x + settingButtonRect.w &&
                    mouseY >= settingButtonRect.y &&
                    mouseY <= settingButtonRect.y + settingButtonRect.h)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    showSettings();
                    return;
                }
                if (mouseX >= wardrobeButtonRect.x &&
                    mouseX <= 850 &&
                    mouseY >= wardrobeButtonRect.y &&
                    mouseY <= wardrobeButtonRect.y + wardrobeButtonRect.h)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    showWardrobe();
                    return;
                }
            }
        }
        if(!shouldQuit)
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);

            font = TTF_OpenFont("Font/cutefont.ttf", 100);
            renderText("Flappy Bird", 350, 40, {255, 255, 255});
            font = TTF_OpenFont("Font/cutefont.ttf", 35);
            renderText("Playy", 630, 240, {255, 255, 255});
            renderText("Exit :(( ", 630, 450, {255, 255, 255});
            renderText("Wardrobe", 630, 345, {255, 255, 255});

            playButtonRect = { 500, 220, 95, 95};
            SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);

            exitButtonRect = { 500, 430, 95, 95 };
            SDL_RenderCopy(renderer, exitButtonTexture, nullptr, &exitButtonRect);
            SDL_RenderCopy(renderer, settingButtonTexture, nullptr, &settingButtonRect);

            wardrobeButtonRect = {500, 325, 95, 95};
            SDL_RenderCopy(renderer, wardrobeButtonTexture, nullptr, &wardrobeButtonRect);

            font = TTF_OpenFont("Font/cutefont.ttf", 30);
            renderText("Coins: " + to_string(totalCoins), 900, 10, {255, 255, 255});

            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
}

void FlappyBirdGame::showGameOverMenu()
{
    SDL_Event e;
    playMenuMusic();
    if (score > highScore)
    {
        highScore = score;
        saveHighScore();
    }
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN &&
                e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= backtomenuButtonRect.x &&
                    mouseX <= 800 &&
                    mouseY >= backtomenuButtonRect.y &&
                    mouseY <= backtomenuButtonRect.y + backtomenuButtonRect.h)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    showMenu();
                    return;
                }
                if (mouseX >= playAgainButtonRect.x &&
                    mouseX <= 744 &&
                    mouseY >= playAgainButtonRect.y &&
                    mouseY <= playAgainButtonRect.y + playAgainButtonRect.h)
                {
                    resetRenderer();
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    startGame();
                    return;
                }
                if (mouseX >= exitButtonRect.x &&
                    mouseX <= 688 &&
                    mouseY >= exitButtonRect.y &&
                    mouseY <= exitButtonRect.y + exitButtonRect.h)
                {
                    shouldQuit = true;
                    break;
                }
            }
        }
        if(!shouldQuit)
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);

            font = TTF_OpenFont("Font/cutefont.ttf", 50);
            renderText("Game Over!!", 480, 70, {255, 255, 255});
            renderText("High Score: " + to_string(highScore), 450, 120, {255, 255, 255});

            font = TTF_OpenFont("Font/cutefont.ttf", 30);
            renderText("Play again", 600, 220, {255, 255, 255});
            renderText("Exit", 600, 420, {255, 255, 255});
            renderText("Back to Menu", 600, 320, {255, 255, 255});
            exitButtonRect = { 490, 400, 90, 90 };

            SDL_RenderCopy(renderer, backtomenuButtonTexture, nullptr, &backtomenuButtonRect);
            SDL_RenderCopy(renderer, playAgainButtonTexture, nullptr, &playAgainButtonRect);
            SDL_RenderCopy(renderer, exitButtonTexture, nullptr, &exitButtonRect);
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
}
