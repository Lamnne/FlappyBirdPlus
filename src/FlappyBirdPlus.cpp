#include "FlappyBirdPlus.h"
#include <ctime>
#include <iostream>

FlappyBirdGame::FlappyBirdGame() :
    shouldQuit(false),
    birdY(SCREEN_HEIGHT / 2),
    birdVelocity(0),
    score(0),
    birdJumping(false),
    pipeVelocity(INITIAL_PIPE_VELOCITY),
    currentBackgroundIndex(0)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    window = SDL_CreateWindow("Flappy Bird",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    menuBackgroundTexture = IMG_LoadTexture(renderer, "image/menu_background.jpg");
    bgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    wardrobebackgroundTexture = IMG_LoadTexture(renderer, "image/wardrobebackground.jpg");
    wbgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    settingButtonTexture= IMG_LoadTexture(renderer, "image/setting_button.png");
    settingButtonRect = { 10, 10, 50, 50};

    playButtonTexture = IMG_LoadTexture(renderer, "image/play_button.png");
    playButtonRect = { 510, 300, 200, 200};

    playAgainButtonTexture = IMG_LoadTexture(renderer, "image/play_again_button.png");
    playAgainButtonRect = { 490, 200, 90, 90 };

    exitButtonTexture = IMG_LoadTexture(renderer, "image/exit_button.png");
    exitButtonRect = { 490, 400, 90, 90 };

    wardrobeButtonTexture = IMG_LoadTexture(renderer, "image/wardrobe_button.png");
    wardrobeButtonRect = { 490, 400, 90, 90 };

    backtomenuButtonTexture = IMG_LoadTexture(renderer, "image/back_to_menu_button.png");
    backtomenuButtonRect = { 490, 300, 90, 90 };

    font = TTF_OpenFont("Font/cutefont.ttf", 100);

    srand(time(0));

    backgroundTextures =
    {
        IMG_LoadTexture(renderer, "image/background1.jpg"),
        IMG_LoadTexture(renderer, "image/background2.jpg"),
        IMG_LoadTexture(renderer, "image/background3.jpg"),
        IMG_LoadTexture(renderer, "image/background4.jpg"),
        IMG_LoadTexture(renderer, "image/background5.jpg")
    };

    pipeTops =
    {
        IMG_LoadTexture(renderer, "image/pipe_top1.png"),
        IMG_LoadTexture(renderer, "image/pipe_top2.png"),
        IMG_LoadTexture(renderer, "image/pipe_top3.png"),
        IMG_LoadTexture(renderer, "image/pipe_top4.png"),
        IMG_LoadTexture(renderer, "image/pipe_top5.png")
    };

    pipeBottoms =
    {
        IMG_LoadTexture(renderer, "image/pipe_bottom1.png"),
        IMG_LoadTexture(renderer, "image/pipe_bottom2.png"),
        IMG_LoadTexture(renderer, "image/pipe_bottom3.png"),
        IMG_LoadTexture(renderer, "image/pipe_bottom4.png"),
        IMG_LoadTexture(renderer, "image/pipe_bottom5.png")
    };

    pipeTopTexture = pipeTops[pipeTopTextureIndex];
    pipeBottomTexture = pipeBottoms[pipeBottomTextureIndex];

    birdRect = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };

    coinTexture = IMG_LoadTexture(renderer, "image/coin.png");
    coinSound = Mix_LoadWAV("audio/coin_sound.mp3");

    shieldTexture = IMG_LoadTexture(renderer, "image/shield.png");
    shieldSound = Mix_LoadWAV("audio/shield_sound.mp3");

    airplaneTexture = IMG_LoadTexture(renderer, "image/airplane.png");

    bulletTexture = IMG_LoadTexture(renderer, "image/bullet.png");

    jumpSound = Mix_LoadWAV("audio/jump_sound.mp3");

    crashSound = Mix_LoadWAV("audio/crash_sound.mp3");

    clickSound = Mix_LoadWAV("audio/click_sound.mp3");

    menuMusic = Mix_LoadMUS("audio/menu_music.mp3");

    gameMusic = Mix_LoadMUS("audio/game_music.mp3");

    overMusic = Mix_LoadMUS("audio/over_music.mp3");

    startMusic = Mix_LoadMUS("audio/start_music.mp3");

    backgroundX = 0;
    backgroundSpeed = 2;
    playMenuMusic();
    loadTotalCoins();
    hasShield = false;
    shieldCount = 0;
    shieldTimer = 0;
    skin=0;
    choose=0;
    generatePipe();
    loadskin();
    loadHighScore();
    airplane.active = false;
    airplane.x = SCREEN_WIDTH - 200;
    airplane.y = SCREEN_HEIGHT / 2;
    airplane.movingUp = true;
    airplane.timer = 0;
    airplane.moveTimer = 0;
}

FlappyBirdGame::~FlappyBirdGame()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    SDL_DestroyTexture(menuBackgroundTexture);
    for (auto& texture : backgroundTextures)
    {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(wardrobebackgroundTexture);
    SDL_DestroyTexture(wardrobeButtonTexture);
    SDL_DestroyTexture(playButtonTexture);
    SDL_DestroyTexture(exitButtonTexture);
    SDL_DestroyTexture(playAgainButtonTexture);
    SDL_DestroyTexture(backtomenuButtonTexture);
    SDL_DestroyTexture(pipeTopTexture);
    SDL_DestroyTexture(pipeBottomTexture);
    SDL_DestroyTexture(coinTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyTexture(birdchooseTexture);
    SDL_DestroyTexture(birdloadTexture);
    SDL_DestroyTexture(rightTexture);
    SDL_DestroyTexture(leftTexture);
    SDL_DestroyTexture(currentBackground);
    SDL_DestroyTexture(shieldTexture);
    SDL_DestroyTexture(lockTexture);
    SDL_DestroyTexture(unlockTexture);
    SDL_DestroyTexture(ynTexture);
    SDL_DestroyTexture(oopTexture);
    stopMusic();
    Mix_FreeChunk(shieldSound);
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(coinSound);
    Mix_FreeChunk(crashSound);
    Mix_FreeMusic(overMusic);
    Mix_FreeMusic(gameMusic);
    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(startMusic);
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

