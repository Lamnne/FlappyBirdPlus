#include "FlappyBirdPlus.h"

void FlappyBirdGame::playMenuMusic()
{
    stopMusic();
    Mix_PlayMusic(menuMusic, -1);
}

void FlappyBirdGame::playGameMusic()
{
    stopMusic();
    Mix_PlayMusic(gameMusic, -1);
}

void FlappyBirdGame::playOverMusic()
{
    stopMusic();
    Mix_PlayMusic(overMusic,0);
}

void FlappyBirdGame::playStartMusic()
{
    stopMusic();
    Mix_PlayMusic(startMusic,0);
}

void FlappyBirdGame::stopMusic()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();
    }
}

