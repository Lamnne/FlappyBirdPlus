#ifndef FLAPPY_BIRD_GAME_H
#define FLAPPY_BIRD_GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;
const int BIRD_WIDTH = 70;
const int BIRD_HEIGHT = 60;
const int PIPE_WIDTH = 100;
const int PIPE_GAP = 220;
const int INITIAL_PIPE_VELOCITY = 4;
const int JUMP_STRENGTH = 14;

struct Pipe
{
    int x, y;
    bool hasPassed;
    bool movingUp;
    bool isMoving = false;
};

struct Coin
{
    int x, y;
    bool collected;
};

struct Shield
{
    int x, y;
    bool collected = false;
};

struct Bullet {
    float x, y;
    bool active;
};

struct Airplane {
    float x, y;
    float speed;
    bool active;
    bool movingUp;
    int moveTimer;
    int timer;
    vector<Bullet> bullets;
};

class FlappyBirdGame
{
public:
    FlappyBirdGame();
    ~FlappyBirdGame();
    int GRAVITY = 0;
    void renderText(const string& text, int x, int y, SDL_Color color);
    void showMenu();
    void showSettings();
    void run();
    void playMenuMusic();
    void playGameMusic();
    void stopMusic();
    void showGameOverMenu();
    void updateGame();
    void render();
    void generatePipe();
    void displayScore();
    void displayhighScore();
    void resetGame();
    void startGame();
    void loadHighScore();
    void saveHighScore();
    void generateCoin(int pipeX, int pipeY);
    void checkCoinCollision();
    void displayCoinCount();
    void loadTotalCoins();
    void saveTotalCoins();
    void showWardrobe();
    void loadskin();
    void loadchoose();
    void loadmenuskin();
    void Start();
    void End();
    void playOverMusic();
    void playStartMusic();
    void resetRenderer();
    void loadUnlockedSkins();
    void saveUnlockedSkins();
    bool sure();
    void oops();
    bool shouldQuit;
    void generateShield();
    void checkShieldCollision();
    bool isPositionValid(int x, int y, int width, int height);
    void spawnAirplane();
private:
    SDL_Window* window;

    SDL_Renderer* renderer;

    SDL_Texture* menuBackgroundTexture;
    SDL_Rect bgRect;

    SDL_Texture* wardrobebackgroundTexture;
    SDL_Rect wbgRect;

    SDL_Texture* birdTexture;
    SDL_Rect birdRect;

    SDL_Texture* birdloadTexture;
    SDL_Rect birdloadRect;

    SDL_Texture* birdchooseTexture;
    SDL_Rect birdchooseRect;

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

    SDL_Texture* wardrobeButtonTexture;
    SDL_Rect wardrobeButtonRect;

    SDL_Texture* coinTexture;

    SDL_Texture* shieldTexture;

    SDL_Texture* rightTexture;
    SDL_Rect rightRect;

    SDL_Texture* leftTexture;
    SDL_Rect leftRect;

    SDL_Texture* lockTexture;
    SDL_Rect lockRect;

    SDL_Texture* unlockTexture;
    SDL_Rect unlockRect;

    SDL_Texture* ynTexture;
    SDL_Rect ynRect;

    SDL_Texture* oopTexture;
    SDL_Rect oopRect;

    SDL_Texture* airplaneTexture;
    SDL_Rect airplaneRect;

    SDL_Texture* bulletTexture;
    SDL_Rect bulletRect;

    int birdY, birdVelocity, score;
    bool birdJumping;
    int pipeVelocity;
    int highScore;
    int coinCount;
    int skin;
    int choose;
    int totalCoins = 0;
    int globalVolume = 50;
    bool soundEnabled = true;
    bool unlockedSkins[11] = {true, false, false, false, false, false, false, false, false, false};
    int skinPrices[11] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450};
    bool hasShield;
    int shieldCount;
    int shieldTimer;
    int pipesPassed = 0;
    Airplane airplane;
    bool airplaneActive = false;
    int airplaneTimer = 0;
    TTF_Font* font;
    vector<Coin> coins;
    vector<SDL_Texture*> backgroundTextures;
    SDL_Texture* currentBackground;
    size_t currentBackgroundIndex;

    vector<Pipe> pipes;
    SDL_Texture* pipeTopTexture;
    SDL_Texture* pipeBottomTexture;
    size_t pipeTopTextureIndex;
    size_t pipeBottomTextureIndex;
    vector<Shield> shields;
    Mix_Music* menuMusic;
    Mix_Music* gameMusic;
    Mix_Music* overMusic;
    Mix_Music* startMusic;
    Mix_Chunk* jumpSound;
    Mix_Chunk* crashSound;
    Mix_Chunk* clickSound;
    Mix_Chunk* coinSound;
    Mix_Chunk* shieldSound;
};

#endif
