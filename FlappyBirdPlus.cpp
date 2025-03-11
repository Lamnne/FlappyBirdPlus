#include "FlappyBirdPlus.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include<fstream>
#include <algorithm>

vector<Coin> coins;

FlappyBirdGame::FlappyBirdGame() : birdY(SCREEN_HEIGHT / 2), birdVelocity(0), score(0), birdJumping(false), currentBackgroundIndex(0), pipeVelocity(INITIAL_PIPE_VELOCITY)
{
    // Khởi tạo SDL và các thư viện liên quan
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
    if (TTF_Init() == -1)
    {
        cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
        exit(1); // Dừng chương trình nếu không thể khởi tạo SDL_ttf
    }
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Khởi tạo background cho menu
    menuBackgroundTexture = IMG_LoadTexture(renderer, "menu_background.jpg");  // Thay "menu_background.jpg" bằng đường dẫn đến file ảnh của bạn

    if (menuBackgroundTexture == nullptr)
    {
        cerr << "SDL_image: Error loading menu background! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    bgRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };  // Vẽ ảnh nền toàn màn hình
    SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);

    settingButtonTexture= IMG_LoadTexture(renderer, "setting_button.png");
    if (settingButtonTexture == nullptr)
    {
        cerr << "SDL_image: Error! setting_button! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    settingButtonRect = { 10, 10, 50, 50};
    playButtonTexture = IMG_LoadTexture(renderer, "play_button.png");
    if (playButtonTexture == nullptr)
    {
        cerr << "SDL_image: Error! play_button! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    playButtonRect = { 510, 300, 200, 200};  // Điều chỉnh kích thước và vị trí theo ý muốn

    playAgainButtonTexture = IMG_LoadTexture(renderer, "play_again_button.png");
    if (playAgainButtonTexture == nullptr)
    {
        cerr << "SDL_image: Error! play_again_button! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    playAgainButtonRect = { 490, 200, 90, 90 };  // Điều chỉnh vị trí và kích thước

    exitButtonTexture = IMG_LoadTexture(renderer, "exit_button.png");
    if (exitButtonTexture == nullptr)
    {
        cerr << "SDL_image: Error! exit_button! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    exitButtonRect = { 490, 400, 90, 90 };

    backtomenuButtonTexture = IMG_LoadTexture(renderer, "back_to_menu_button.png");
    if (backtomenuButtonTexture == nullptr)
    {
        cerr << "SDL_image: Error! backtomenu_button! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    backtomenuButtonRect = { 490, 300, 90, 90 };

    birdTexture = IMG_LoadTexture(renderer, "bird.gif");
    if (birdTexture == nullptr)
    {
        cerr << "SDL_image: Error! bird! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    birdRect = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };

    font = TTF_OpenFont("cutefont.ttf", 100);
    if (font == nullptr)
    {
        cerr << "SDL_ttf: Error! font!" << TTF_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    srand(time(0));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background1.jpg"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background2.jpg"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background3.png"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background4.jpg"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background5.jpg"));

    for (auto& texture : backgroundTextures)
    {
        if (texture == nullptr)
        {
            cerr << "SDL_image: Error! background!" << IMG_GetError() << endl;
            SDL_Quit();
            TTF_Quit();
            IMG_Quit();
            Mix_Quit();
            exit(1);
        }
    }

    currentBackground = backgroundTextures[currentBackgroundIndex];

    pipeTopTexture = IMG_LoadTexture(renderer, "pipe_top.png");
    pipeBottomTexture = IMG_LoadTexture(renderer, "pipe_bottom.png");
    if (pipeTopTexture == nullptr || pipeBottomTexture == nullptr)
    {
        cerr << "SDL_image: Error! pipe!" << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    coinTexture = IMG_LoadTexture(renderer, "coin.png");
    if (coinTexture == nullptr)
    {
        cerr << "SDL_image: Error loading coin image! " << IMG_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    generatePipe();

    jumpSound = Mix_LoadWAV("jump_sound.mp3");
    if (jumpSound == nullptr)
    {
        cerr << "SDL_mixer: Error! jump!" << Mix_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    crashSound = Mix_LoadWAV("crash_sound.mp3");
    if (crashSound == nullptr)
    {
        cerr << "SDL_mixer: Error! crashSound!" << Mix_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    clickSound = Mix_LoadWAV("click_sound.mp3");  // Tải âm thanh click
    if (clickSound == nullptr)
    {
        cerr << "SDL_mixer: Error! click_sound! " << Mix_GetError() << endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    menuMusic = Mix_LoadMUS("menu_music.mp3");
    if (menuMusic == nullptr)
    {
        cerr << "SDL_mixer: Error loading menu music! " << Mix_GetError() << endl;
        exit(1);
    }

    gameMusic = Mix_LoadMUS("game_music.mp3");
    if (gameMusic == nullptr)
    {
        cerr << "SDL_mixer: Error loading game music! " << Mix_GetError() << endl;
        exit(1);
    }
    coinSound = Mix_LoadWAV("coin_sound.mp3");
    if (coinSound == nullptr)
    {
        cerr << "SDL_mixer: Error loading coin sound! " << Mix_GetError() << endl;
        exit(1);
    }

    if (coinSound == nullptr)
    {
        cerr << "SDL_mixer: Error loading coin sound! " << Mix_GetError() << endl;
        exit(1);
    }
    playMenuMusic();
    loadTotalCoins();  // Tải tổng số coins từ file khi khởi động game

    loadHighScore();
}

FlappyBirdGame::~FlappyBirdGame()
{
    SDL_DestroyTexture(coinTexture);
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);  // Đảm bảo đóng font đúng cách
    SDL_DestroyTexture(menuBackgroundTexture);
    for (auto& texture : backgroundTextures)
    {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(playButtonTexture);
    SDL_DestroyTexture(exitButtonTexture);
    SDL_DestroyTexture(playAgainButtonTexture);
    SDL_DestroyTexture(backtomenuButtonTexture);
    SDL_DestroyTexture(pipeTopTexture);
    SDL_DestroyTexture(pipeBottomTexture);
    stopMusic();
    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(coinSound);

    Mix_Quit();

    TTF_Quit();  // Đóng SDL_ttf
    IMG_Quit();
    SDL_Quit();
}

void FlappyBirdGame::run()
{
    bool quit = false;
    SDL_Event e;

    playGameMusic();
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if ((e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_UP)) ||
                    (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT))
            {
                birdVelocity = -JUMP_STRENGTH;
                Mix_PlayChannel(-1, jumpSound, 0);
            }

        }

        updateGame();
        render();
        SDL_Delay(16);
    }
}

void FlappyBirdGame::updateGame()
{
    birdVelocity += GRAVITY;
    birdY += birdVelocity;

    if (birdY < 0)
    {
        birdY = 0;
    }
    if (birdY + BIRD_HEIGHT > SCREEN_HEIGHT)
    {
        birdY = SCREEN_HEIGHT - BIRD_HEIGHT;
    }

    birdRect.y = birdY;

    for (auto& pipe : pipes)
    {
        pipe.x -= pipeVelocity;

        if (pipe.x < 100 + BIRD_WIDTH && pipe.x + PIPE_WIDTH > 100 && (birdY < pipe.y || birdY + BIRD_HEIGHT > pipe.y + PIPE_GAP))
        {
            Mix_PlayChannel(-1, crashSound, 0); // Thêm âm thanh va chạm
            totalCoins +=coinCount;  // Cộng số coin đã thu thập vào tổng coin
            saveTotalCoins();  // Lưu totalCoins vào file
            coinCount = 0;  // Reset coinCount khi quay lại menu
            showGameOverMenu();
            return;
        }

    }
    for (auto& coin : coins)
    {
        coin.x -= pipeVelocity;  // Đồng xu di chuyển với cùng tốc độ ống
    }
    checkCoinCollision();
    // Xóa các đồng xu đã ra khỏi màn hình
    coins.erase(remove_if(coins.begin(), coins.end(), [](Coin c)
    {
        return c.x < -20;
    }), coins.end());
    if (!pipes.empty() && pipes.back().x < SCREEN_WIDTH - 300)
    {
        generatePipe();
    }

    vector<Pipe> remainingPipes;
    for (const auto& pipe : pipes)
    {
        if (pipe.x + PIPE_WIDTH > 0)
        {
            remainingPipes.push_back(pipe);
        }
    }
    pipes = remainingPipes;

    for (auto& pipe : pipes)
    {
        if (pipe.x + PIPE_WIDTH == 100)
        {
            score++;
            if (score % 10 == 0)
            {
                pipeVelocity++;
                if (score / 10 < static_cast<int>(backgroundTextures.size()))
                {
                    currentBackgroundIndex = score / 10;
                    currentBackground = backgroundTextures[currentBackgroundIndex];
                }

            }
        }
    }
}

void FlappyBirdGame::resetGame()
{
    birdY = SCREEN_HEIGHT / 2;
    birdVelocity = 0;
    score = 0;
    coinCount = 0;  // Reset số coin khi bắt đầu game mới
    pipes.clear();
    coins.clear();
    generatePipe();
    pipeVelocity = INITIAL_PIPE_VELOCITY;
    currentBackground = backgroundTextures[0];
    currentBackgroundIndex = 0;
}

void FlappyBirdGame::startGame()
{
    resetGame();  // Reset lại trạng thái của game, chẳng hạn như điểm số, vị trí chim
    run();         // Gọi hàm chạy game chính
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
            Mix_PlayChannel(-1, coinSound, 0);
        }
    }
}


