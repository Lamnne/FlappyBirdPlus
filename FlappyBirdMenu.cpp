#include "FlappyBirdPlus.h"

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
                if (mouseX >= playButtonRect.x && mouseX <= 760 &&
                        mouseY >= playButtonRect.y && mouseY <= playButtonRect.y + playButtonRect.h)
                {
                    Mix_PlayChannel(-1, clickSound, 0);
                    quit = true;  // Thoát khỏi menu và bắt đầu trò chơi
                }
                else if (mouseX >= exitButtonRect.x && mouseX <= 800 &&
                         mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
                {
                    Mix_PlayChannel(-1, clickSound, 0);
                    SDL_Quit();      // Đóng cửa sổ và kết thúc SDL
                    TTF_Quit();      // Đảm bảo đóng SDL_ttf
                    IMG_Quit();      // Đảm bảo đóng SDL_image
                    Mix_Quit();      // Đảm bảo đóng SDL_mixer
                    exit(0);         // Thoát hoàn toàn chương trình
                }
                else if (mouseX >= settingButtonRect.x && mouseX <= settingButtonRect.x + settingButtonRect.w &&
                         mouseY >= settingButtonRect.y && mouseY <= settingButtonRect.y + settingButtonRect.h)
                {
                    Mix_PlayChannel(-1, clickSound, 0);
                    showSettings();
                }
            }
        }

        // Vẽ background menu
        SDL_RenderClear(renderer); // Dọn dẹp renderer trước khi vẽ
        SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);  // Vẽ ảnh nền toàn màn hình

        // Vẽ menu
        font = TTF_OpenFont("cutefont.ttf", 100);
        renderText("Flappy Bird", 350, 80, {255, 255, 255});

        font = TTF_OpenFont("cutefont.ttf", 50);
        renderText("Playy", 630, 240, {255, 255, 255});
        renderText("Exit :(( ", 630, 450, {255, 255, 255});
        // Vẽ nút Play
        playButtonRect = { 500, 220, 100, 100};
        SDL_RenderCopy(renderer, playButtonTexture, nullptr, &playButtonRect);
        exitButtonRect = { 500, 430, 100, 100 };
        SDL_RenderCopy(renderer, exitButtonTexture, nullptr, &exitButtonRect);
        SDL_RenderCopy(renderer, settingButtonTexture, nullptr, &settingButtonRect);
        font = TTF_OpenFont("cutefont.ttf", 30);
        // Vẽ màn hình menu
        renderText("Coins: " + to_string(totalCoins), 1030, 10, {255, 255, 255});
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // Khi nhấp vào nút play, bắt đầu trò chơi
    startGame();  // Gọi hàm bắt đầu game (bạn có thể tạo hàm này)
}

void FlappyBirdGame::showGameOverMenu()
{
    bool quit = false;
    SDL_Event e;
    playMenuMusic();
    if (score > highScore)
    {
        highScore = score;  // Cập nhật điểm số cao nhất
        saveHighScore();    // Lưu điểm số cao nhất vào tệp
    }
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

                // Kiểm tra nếu người dùng nhấp vào nút backtomenuButton
                if (mouseX >= backtomenuButtonRect.x && mouseX <= 800 &&
                        mouseY >= backtomenuButtonRect.y && mouseY <= backtomenuButtonRect.y + backtomenuButtonRect.h)
                {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);

                    showMenu();
                }

                // Kiểm tra nếu người dùng nhấp vào nút Play Again
                if (mouseX >= playAgainButtonRect.x && mouseX <= 744 &&
                        mouseY >= playAgainButtonRect.y && mouseY <= playAgainButtonRect.y + playAgainButtonRect.h)
                {
                    // Phát âm thanh click
                    Mix_PlayChannel(-1, clickSound, 0);

                    resetGame();  // Reset lại game
                    quit = true;  // Thoát khỏi menu và bắt đầu trò chơi
                    run();         // Bắt đầu trò chơi
                }

                // Kiểm tra nếu người dùng nhấp vào nút Exit
                if (mouseX >= exitButtonRect.x && mouseX <= 688 &&
                        mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
                {
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
        SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);  // Vẽ ảnh nền toàn màn hình

        font = TTF_OpenFont("cutefont.ttf", 50);
        renderText("Game Over!!", 480, 70, {255, 255, 255});
        renderText("High Score: " + to_string(highScore), 450, 120, {255, 255, 255});
        font = TTF_OpenFont("cutefont.ttf", 30);
        renderText("Play again", 600, 220, {255, 255, 255});
        renderText("Exit", 600, 420, {255, 255, 255});
        renderText("Back to Menu", 600, 320, {255, 255, 255});
        SDL_RenderCopy(renderer, backtomenuButtonTexture, nullptr, &backtomenuButtonRect);
        SDL_RenderCopy(renderer, playAgainButtonTexture, nullptr, &playAgainButtonRect);
        exitButtonRect = { 490, 400, 90, 90 };
        SDL_RenderCopy(renderer, exitButtonTexture, nullptr, &exitButtonRect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
