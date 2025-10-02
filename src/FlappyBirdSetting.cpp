#include "FlappyBirdPlus.h"

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void FlappyBirdGame::showSettings()
{
    bool quit = false;
    SDL_Event e;
    int volume = globalVolume;
    bool isDragging = false;
    while (!quit&&!shouldQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 600 && mouseX <= 950 && mouseY >= 180 && mouseY <= 230)
                {
                    isDragging = true;
                }
                if (mouseX >= 600 && mouseX <= 670 && mouseY >= 300 && mouseY <= 370)
                {
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    soundEnabled = true;
                }
                if (mouseX >= 750 && mouseX <= 830 && mouseY >= 300 && mouseY <= 370)
                {
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    soundEnabled = false;
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = false;
            }
            if (e.type == SDL_MOUSEMOTION && isDragging)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 595 && mouseX <= 595+355)
                {
                    volume = (mouseX - 595) * 128 / 355;
                    globalVolume=volume;
                    Mix_VolumeMusic(globalVolume);
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 0 && mouseX <= 130 && mouseY >= 0 && mouseY <= 70)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    showMenu();
                    return;
                }
            }
        }
        if(!shouldQuit)
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);

            font = TTF_OpenFont("Font/cutefont.ttf", 80);
            renderText("Settings", 450, 40, {255, 255, 255});

            font = TTF_OpenFont("Font/cutefont.ttf", 50);
            renderText("Audio", 350, 190, {255, 255, 255});
            renderText("Sounds", 350, 300, {255, 255, 255});
            renderText("ON", 600, 300, {255, 255, 255});
            renderText("OFF", 750, 300, {255, 255, 255});

            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect volumeBar = { 595, 220, 355, 5 };
            SDL_RenderFillRect(renderer, &volumeBar);

            SDL_Color volumeColor = {255, 255, 255, 255};
            int radius = 15;
            int circleX = 595 + (globalVolume * 355 / 128);
            int circleY = 210;
            drawCircle(renderer, circleX, circleY, radius, volumeColor);
            renderText("Back", 10, 10, {255, 255, 255});
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
    }
    Mix_VolumeMusic(globalVolume);
}
