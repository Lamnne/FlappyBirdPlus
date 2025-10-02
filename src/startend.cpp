#include "FlappyBirdPlus.h"

void FlappyBirdGame::Start()
{
    bool blockingInput = true;
    playStartMusic();
    SDL_RenderClear(renderer);
    font = TTF_OpenFont("Font/cutefont.ttf", 330);
    for (int i = 3; i > 0; i--)
    {
        renderText(std::to_string(i), 500, 110, {255, 255, 255});
        SDL_RenderPresent(renderer);
        Uint32 startTime = SDL_GetTicks();
        while (SDL_GetTicks() - startTime < 1000)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {}
        }
        SDL_RenderClear(renderer);
    }
    font = TTF_OpenFont("Font/cutefont.ttf", 190);
    renderText("START!!!", 260, 200, {255, 255, 255});
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    blockingInput = false;
}


void FlappyBirdGame::End()
{
    bool blockingInput = true;
    playOverMusic();
    SDL_Color colors[] = {{255, 0, 0},{0, 255, 0},{0, 0, 255},{255, 255, 0},{255, 0, 255},{0, 255, 255},{255, 165, 0},{75, 0, 130},{255, 20, 147},{255,255,255}};
    for (int i = 0; i < 10; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        font = TTF_OpenFont("Font/cutefont.ttf", 180);
        renderText("GAME OVER!", 100, 200, colors[i]);
        SDL_RenderPresent(renderer);
        Uint32 startTime = SDL_GetTicks();
        while (SDL_GetTicks() - startTime < 100)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {}
        }
    }
    blockingInput = false;
}
