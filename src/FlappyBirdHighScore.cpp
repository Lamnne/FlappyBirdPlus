#include "FlappyBirdPlus.h"
#include <fstream>

void FlappyBirdGame::loadHighScore()
{
    ifstream file("data/highscore.txt");
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    else
    {
        highScore = 0;
    }
}

void FlappyBirdGame::saveHighScore()
{
    ofstream file("data/highscore.txt");
    if (file.is_open())
    {
        file << highScore;
        file.close();
    }
}

void FlappyBirdGame::displayScore()
{
    SDL_Color textColor = { 255, 255, 255 };
    string scoreText = "Score: " + to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);
    SDL_Rect scoreRect = { 900, 60, 130, 40 };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
}

void FlappyBirdGame::displayhighScore()
{
    font = TTF_OpenFont("Font/cutefont.ttf", 30);
    SDL_Color textColor = {255, 255, 255};
    string highScoreText = "High Score: " + to_string(highScore);
    renderText(highScoreText, 900, 20, textColor);
    SDL_RenderPresent(renderer);
}
