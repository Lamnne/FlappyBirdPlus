#include "FlappyBirdPlus.h"
#include<iostream>
void FlappyBirdGame::renderText(const string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textSurface == nullptr)
    {
        cerr << "SDL_ttf: Error creating surface for text: " << TTF_GetError() << endl;
        return;
    }

    SDL_FreeSurface(textSurface);
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}
void FlappyBirdGame::render()
{

    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, currentBackground, nullptr, &backgroundRect);

    SDL_Rect renderQuad = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };
    SDL_RenderCopy(renderer, birdTexture, nullptr, &renderQuad);

    for (auto& pipe : pipes)
    {
        SDL_Rect topPipeRect = { pipe.x, 0, PIPE_WIDTH, pipe.y };
        SDL_RenderCopy(renderer, pipeTopTexture, nullptr, &topPipeRect);

        SDL_Rect bottomPipeRect = { pipe.x, pipe.y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipe.y - PIPE_GAP };
        SDL_RenderCopy(renderer, pipeBottomTexture, nullptr, &bottomPipeRect);
    }

    // Vẽ đồng xu
    for (auto& coin : coins)
    {
        if (!coin.collected)
        {
            SDL_Rect coinRect = { coin.x, coin.y,100, 100 };
            SDL_RenderCopy(renderer, coinTexture, nullptr, &coinRect);
        }
    }
    displayCoinCount();
    displayScore();
    displayhighScore();
}
