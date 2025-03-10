#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include<ostream>
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int BIRD_WIDTH = 60;
const int BIRD_HEIGHT = 60;
const int PIPE_WIDTH = 100;
const int PIPE_GAP = 220; // Khoang cach giua ong tren va ong duoi
const int INITIAL_PIPE_VELOCITY = 4;
const int GRAVITY = 1;
const int JUMP_STRENGTH = 14;

struct Pipe
{
    int x, y;
    bool hasPassed;
};

class FlappyBirdGame
{
public:
    FlappyBirdGame();
    ~FlappyBirdGame();
    void renderText(const string& text, int x, int y, SDL_Color color);
    void showMenu();
    void showSettings();
    void run();
    void loadMusic();
    void playMenuMusic();
    void playGameMusic();
    void stopMusic();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* menuBackgroundTexture;
    SDL_Rect bgRect;

    SDL_Texture* birdTexture;
    SDL_Rect birdRect;

    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;

    SDL_Texture* playAgainButtonTexture;
    SDL_Rect playAgainButtonRect;

    SDL_Texture* exitButtonTexture;
    SDL_Rect exitButtonRect;

    SDL_Texture* backtomenuButtonTexture;
    SDL_Rect backtomenuButtonRect;

    SDL_Texture* settingButtonTexture;
    SDL_Rect settingButtonRect;
    int birdY, birdVelocity, score;
    bool birdJumping;

    TTF_Font* font;

    vector<SDL_Texture*> backgroundTextures;
    SDL_Texture* currentBackground;
    size_t currentBackgroundIndex;

    vector<Pipe> pipes;
    SDL_Texture* pipeTopTexture;
    SDL_Texture* pipeBottomTexture;
    size_t pipeTopTextureIndex;
    size_t pipeBottomTextureIndex;

    int pipeVelocity;
    int highScore;
    Mix_Chunk* jumpSound;
    Mix_Chunk* crashSound;
    Mix_Chunk* clickSound;
    Mix_Music* menuMusic;
    Mix_Music* gameMusic;
    void showGameOverMenu();
    void updateGame();
    void render();
    void generatePipe();
    void displayScore();
    void displayhighScore();
    void resetGame();
    void startGame();
    void loadHighScore();  // Hàm đọc điểm số cao nhất từ tệp
    void saveHighScore();  // Hàm ghi điểm số cao nhất vào tệp
};

#endif // FLAPPY_BIRD_GAME_H
