#include "FlappyBirdPlus.h"

void FlappyBirdGame::renderText(const string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

void FlappyBirdGame::render()
{
    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, currentBackground, nullptr, &backgroundRect);

    SDL_Rect birdRect = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };
    if (airplaneActive && airplane.active)
{
    if (airplaneTexture)
    {
        SDL_Rect airplaneRect = { airplane.x - 60, airplane.y, 200, 150 };
        SDL_RenderCopy(renderer, airplaneTexture, nullptr, &airplaneRect);
    }
    for (auto& b : airplane.bullets)
    {
        if (b.active && bulletTexture)
        {
            SDL_Rect bulletRect = { b.x, b.y + 30, 10, 4 };
            SDL_RenderCopy(renderer, bulletTexture, nullptr, &bulletRect);
        }
    }
}

    if (hasShield)
    {
        SDL_SetTextureAlphaMod(birdTexture, 100);
    }
    else
    {
        SDL_SetTextureAlphaMod(birdTexture, 255);
    }
    SDL_RenderCopy(renderer, birdTexture, nullptr, &birdRect);

    for (auto& pipe : pipes)
    {
        SDL_Rect topPipeRect = { pipe.x, 0, PIPE_WIDTH, pipe.y };
        SDL_RenderCopy(renderer, pipeTopTexture, nullptr, &topPipeRect);

        SDL_Rect bottomPipeRect = { pipe.x, pipe.y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipe.y - PIPE_GAP };
        SDL_RenderCopy(renderer, pipeBottomTexture, nullptr, &bottomPipeRect);
    }

    for (auto& coin : coins)
    {
        if (!coin.collected)
        {
            SDL_Rect coinRect = { coin.x, coin.y, 100, 100 };
            SDL_RenderCopy(renderer, coinTexture, nullptr, &coinRect);
        }
    }

    for (auto& shield : shields)
    {
        if (!shield.collected)
        {
            SDL_Rect shieldRect = { shield.x, shield.y, 50, 50 };
            SDL_RenderCopy(renderer, shieldTexture, nullptr, &shieldRect);
        }
    }

    displayCoinCount();
    displayScore();
    displayhighScore();
}
