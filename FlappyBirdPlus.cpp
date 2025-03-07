#include "FlappyBirdPlus.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>

FlappyBirdGame::FlappyBirdGame() : birdY(SCREEN_HEIGHT / 2), birdVelocity(0), score(0), birdJumping(false), currentBackgroundIndex(0), pipeVelocity(INITIAL_PIPE_VELOCITY) {
    // Khởi tạo SDL và các thư viện liên quan
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
    if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    exit(1); // Dừng chương trình nếu không thể khởi tạo SDL_ttf
    }
    IMG_Init(IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);


    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    playButtonTexture = IMG_LoadTexture(renderer, "play_button.png");
    if (playButtonTexture == nullptr)
    {
        std::cerr << "SDL_image: Error! play_button! " << IMG_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    playButtonRect = { 330, 300, 150, 150 };  // Điều chỉnh kích thước và vị trí theo ý muốn

    playAgainButtonTexture = IMG_LoadTexture(renderer, "play_again_button.png");
    if (playAgainButtonTexture == nullptr)
    {
        std::cerr << "SDL_image: Error! play_again_button! " << IMG_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    playAgainButtonRect = { 350, 200, 100, 100 };  // Điều chỉnh vị trí và kích thước

    exitButtonTexture = IMG_LoadTexture(renderer, "exit_button.png");
    if (exitButtonTexture == nullptr)
    {
        std::cerr << "SDL_image: Error! exit_button! " << IMG_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    exitButtonRect = { 350, 400, 100, 100 };

    birdTexture = IMG_LoadTexture(renderer, "bird.gif");
    if (birdTexture == nullptr)
    {
        std::cerr << "SDL_image: Error! bird! " << IMG_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }
    birdRect = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };

    font = TTF_OpenFont("cutefont.ttf", 30);
    if (font == nullptr)
    {
        std::cerr << "SDL_ttf: Error! font!" << TTF_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    srand(time(0));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background1.png"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background2.png"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background3.png"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background4.jpg"));
    backgroundTextures.push_back(IMG_LoadTexture(renderer, "background5.jpg"));

    for (auto& texture : backgroundTextures)
    {
        if (texture == nullptr)
        {
            std::cerr << "SDL_image: Error! background!" << IMG_GetError() << std::endl;
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
        std::cerr << "SDL_image: Error! pipe!" << IMG_GetError() << std::endl;
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
        std::cerr << "SDL_mixer: Error! jump!" << Mix_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    crashSound = Mix_LoadWAV("crash_sound.mp3");
    if (crashSound == nullptr)
    {
        std::cerr << "SDL_mixer: Error! crashSound!" << Mix_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

    clickSound = Mix_LoadWAV("click_sound.mp3");  // Tải âm thanh click
    if (clickSound == nullptr)
    {
        std::cerr << "SDL_mixer: Error! click_sound! " << Mix_GetError() << std::endl;
        SDL_Quit();
        TTF_Quit();
        IMG_Quit();
        Mix_Quit();
        exit(1);
    }

}

FlappyBirdGame::~FlappyBirdGame() {
    SDL_DestroyTexture(birdTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);  // Đảm bảo đóng font đúng cách

    for (auto& texture : backgroundTextures) {
        SDL_DestroyTexture(texture);
    }
    SDL_DestroyTexture(playButtonTexture);
    SDL_DestroyTexture(exitButtonTexture);
    SDL_DestroyTexture(playAgainButtonTexture);
    SDL_DestroyTexture(pipeTopTexture);
    SDL_DestroyTexture(pipeBottomTexture);

    Mix_FreeChunk(jumpSound);
    Mix_FreeChunk(clickSound);
    Mix_Quit();

    TTF_Quit();  // Đóng SDL_ttf
    IMG_Quit();
    SDL_Quit();
}

void FlappyBirdGame::renderText(const std::string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr)
    {
        std::cerr << "SDL_ttf: Error creating surface for text: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

void FlappyBirdGame::showMenu()
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // Kiểm tra sự kiện nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Kiểm tra nếu người dùng nhấp vào nút play
                if (mouseX >= playButtonRect.x && mouseX <= playButtonRect.x + playButtonRect.w &&
                        mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
                {
                    Mix_PlayChannel(-1, clickSound, 0);
                    quit = true;  // Thoát khỏi menu và bắt đầu trò chơi
                }
            }
        }

        // Vẽ menu
        SDL_RenderClear(renderer);
        renderText("Flappy Bird", 330, 200, {255, 255, 255});

        // Vẽ nút Play
        SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }

    // Khi nhấp vào nút play, bắt đầu trò chơi
    startGame();  // Gọi hàm bắt đầu game (bạn có thể tạo hàm này)
}

void FlappyBirdGame::run()
{
    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
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
            showGameOverMenu();
            return;
        }
    }

    if (!pipes.empty() && pipes.back().x < SCREEN_WIDTH - 300)
    {
        generatePipe();
    }

    std::vector<Pipe> remainingPipes;
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

void FlappyBirdGame::render()
{
    SDL_Rect backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, currentBackground, nullptr, &backgroundRect);

    SDL_Rect renderQuad = { 100, birdY, BIRD_WIDTH, BIRD_HEIGHT };
    SDL_RenderCopy(renderer, birdTexture, nullptr, &renderQuad);

    for (auto& pipe : pipes)
    {
        SDL_Rect topPipeRect = { pipe.x, 0, PIPE_WIDTH, pipe.y };
        SDL_RenderCopy(renderer, pipeTopTexture, nullptr, &topPipeRect);

        SDL_Rect bottomPipeRect = { pipe.x, pipe.y + PIPE_GAP, PIPE_WIDTH, SCREEN_HEIGHT - pipe.y - PIPE_GAP };
        SDL_RenderCopy(renderer, pipeBottomTexture, nullptr, &bottomPipeRect);
    }

    displayScore();

    SDL_RenderPresent(renderer);
}

void FlappyBirdGame::generatePipe()
{
    int pipeHeight = rand() % (SCREEN_HEIGHT - PIPE_GAP);
    pipes.push_back({ SCREEN_WIDTH, pipeHeight, false });
}

void FlappyBirdGame::displayScore()
{
    SDL_Color textColor = { 255, 255, 255 };
    std::string scoreText = "Score: " + std::to_string(score);
    SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_FreeSurface(scoreSurface);

    SDL_Rect scoreRect = { SCREEN_WIDTH - 150, 20, 130, 40 };
    SDL_RenderCopy(renderer, scoreTexture, nullptr, &scoreRect);

    SDL_DestroyTexture(scoreTexture);
}

void FlappyBirdGame::resetGame()
{
    birdY = SCREEN_HEIGHT / 2;
    birdVelocity = 0;
    score = 0;
    pipes.clear();
    generatePipe();
    pipeVelocity = INITIAL_PIPE_VELOCITY;
    currentBackground = backgroundTextures[0];
    currentBackgroundIndex = 0;
}

void FlappyBirdGame::startGame()
{
    // Tiến hành reset game và bắt đầu vòng lặp chơi
    resetGame();  // Reset lại trạng thái của game, chẳng hạn như điểm số, vị trí chim
    run();         // Gọi hàm chạy game chính
}

void FlappyBirdGame::showGameOverMenu() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Kiểm tra sự kiện nhấp chuột
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Kiểm tra nếu người dùng nhấp vào nút Play Again
                if (mouseX >= playAgainButtonRect.x && mouseX <= playAgainButtonRect.x + playAgainButtonRect.w &&
                    mouseY >= playAgainButtonRect.y && mouseY <= playAgainButtonRect.y + playAgainButtonRect.h) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);

                    resetGame();  // Reset lại game
                    quit = true;  // Thoát khỏi menu và bắt đầu trò chơi
                    run();         // Bắt đầu trò chơi
                }

                // Kiểm tra nếu người dùng nhấp vào nút Exit
                if (mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
                    mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h) {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);

                    // Thoát khỏi game
                    SDL_Quit();      // Đóng cửa sổ và kết thúc SDL
                    TTF_Quit();      // Đảm bảo đóng SDL_ttf
                    IMG_Quit();      // Đảm bảo đóng SDL_image
                    Mix_Quit();      // Đảm bảo đóng SDL_mixer
                    exit(0);         // Thoát hoàn toàn chương trình
                }
            }
        }

        // Vẽ game over menu
        SDL_RenderClear(renderer);
        renderText("Game Over", 340, 100, {255, 255, 255});

        // Vẽ nút Play Again và Exit
        SDL_RenderCopy(renderer, playAgainButtonTexture, nullptr, &playAgainButtonRect);
        SDL_RenderCopy(renderer, exitButtonTexture, nullptr, &exitButtonRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}


