#include "FlappyBirdPlus.h"
#include <fstream>

using namespace std;

void FlappyBirdGame::loadTotalCoins()
{
    ifstream file("data/totalcoins.txt");
    if (file.is_open())
    {
        file >> totalCoins;
        file.close();
    }
    else
    {
        totalCoins = 0;
    }
}

void FlappyBirdGame::saveTotalCoins()
{
    ofstream file("data/totalcoins.txt");
    if (file.is_open())
    {
        file << totalCoins;
        file.close();
    }
}

void FlappyBirdGame::displayCoinCount()
{
    SDL_Color textColor = {255, 255, 0};
    string coinText = "Coins: " + to_string(coinCount);
    renderText(coinText, 900, 100, textColor);
}

void FlappyBirdGame::generateCoin(int pipeX, int pipeY)
{
    Coin newCoin;
    newCoin.x = pipeX + PIPE_WIDTH / 2;
    newCoin.y = pipeY;
    newCoin.collected = false;
    coins.push_back(newCoin);
}

void FlappyBirdGame::checkCoinCollision()
{
    for (auto& coin : coins)
    {
        if (!coin.collected &&
                birdRect.x + BIRD_WIDTH >= coin.x && birdRect.x <= coin.x + 50 &&
                birdRect.y + BIRD_HEIGHT >= coin.y && birdRect.y <= coin.y + 50)
        {
            coin.collected = true;
            coinCount++;
            if (soundEnabled)Mix_PlayChannel(-1, coinSound, 0);
        }
    }
}

