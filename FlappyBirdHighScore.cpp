#include "FlappyBirdPlus.h"
#include <fstream>

void FlappyBirdGame::loadHighScore()
{
    // Mở tệp điểm số cao nhất (highscore.txt)
    ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> highScore;  // Đọc điểm số từ tệp
        file.close();
    }
    else
    {
        highScore = 0;  // Nếu tệp không tồn tại, gán điểm số cao nhất là 0
    }
}

void FlappyBirdGame::saveHighScore()
{
    // Mở tệp để lưu điểm số cao nhất
    ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << highScore;  // Ghi điểm số cao nhất vào tệp
        file.close();
    }
}
void FlappyBirdGame::loadTotalCoins()
{
    ifstream file("totalcoins.txt");
    if (file.is_open())
    {
        file >> totalCoins;
        file.close();
    }
    else
    {
        totalCoins = 0;  // Nếu file chưa có, đặt totalCoins = 0
    }
}
void FlappyBirdGame::saveTotalCoins()
{
    ofstream file("totalcoins.txt");
    if (file.is_open())
    {
        file << totalCoins;
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
    SDL_Rect scoreRect = { 990, 60, 130, 40 };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);
    SDL_DestroyTexture(scoreTexture);
}

void FlappyBirdGame::displayhighScore()
{
    font = TTF_OpenFont("cutefont.ttf", 30);
    SDL_Color textColor = {255, 255, 255};
    string highScoreText = "High Score: " + to_string(highScore);
    renderText(highScoreText, 990, 20, textColor);  // Vị trí hiển thị điểm số cao nhất
    SDL_RenderPresent(renderer);
}
void FlappyBirdGame::displayCoinCount()
{
    SDL_Color textColor = {255, 255, 0}; // Màu vàng
    string coinText = "Coins: " + to_string(coinCount);
    renderText(coinText, 990, 100, textColor);
}

