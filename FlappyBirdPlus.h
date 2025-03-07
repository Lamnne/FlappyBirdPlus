#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BIRD_WIDTH = 50;
const int BIRD_HEIGHT = 50;
const int PIPE_WIDTH = 80;
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
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    void showMenu();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* birdTexture;
    SDL_Rect birdRect;
    SDL_Texture* playButtonTexture;
    SDL_Rect playButtonRect;  // Để xác định vị trí của nút play
    SDL_Texture* playAgainButtonTexture;
    SDL_Texture* exitButtonTexture;
    SDL_Rect playAgainButtonRect;
    SDL_Rect exitButtonRect;

    int birdY, birdVelocity, score;
    bool birdJumping;
    TTF_Font* font;
    std::vector<Pipe> pipes;
    std::vector<SDL_Texture*> backgroundTextures;
    SDL_Texture* currentBackground;
    size_t currentBackgroundIndex;

    SDL_Texture* pipeTopTexture;
    SDL_Texture* pipeBottomTexture;

    int pipeVelocity;
    Mix_Chunk* jumpSound;
    Mix_Chunk* crashSound;
    Mix_Chunk* clickSound;  // Thêm biến âm thanh click
    void showGameOverMenu();
    void updateGame();
    void render();
    void generatePipe();
    void displayScore();
    void resetGame();
    void startGame();
};

#endif // FLAPPY_BIRD_GAME_H
