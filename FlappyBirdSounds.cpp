#include "FlappyBirdPlus.h"

void FlappyBirdGame::playMenuMusic()
{
    // Dừng nhạc nếu đang phát và phát nhạc menu
    stopMusic();
    Mix_PlayMusic(menuMusic, -1);  // -1 có nghĩa là phát lặp lại vô hạn
}

void FlappyBirdGame::playGameMusic()
{
    // Dừng nhạc nếu đang phát và phát nhạc game
    stopMusic();
    Mix_PlayMusic(gameMusic, -1);  // -1 có nghĩa là phát lặp lại vô hạn
}

void FlappyBirdGame::stopMusic()
{
    if (Mix_PlayingMusic())
    {
        Mix_HaltMusic();  // Dừng nhạc hiện tại
    }
}


