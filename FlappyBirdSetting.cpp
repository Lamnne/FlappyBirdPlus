#include "FlappyBirdPlus.h"

// Hàm để vẽ một hình tròn (dùng SDL2_gfx hoặc tự vẽ nếu không có thư viện)
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
    // Chúng ta sẽ vẽ một hình tròn bằng cách sử dụng SDL_RenderDrawPoint hoặc SDL_RenderDrawLine
    // Nếu bạn dùng SDL2_gfx, thì sử dụng hàm "circleColor"
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;  // X khoảng cách từ điểm giữa
            int dy = radius - h;  // Y khoảng cách từ điểm giữa
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void FlappyBirdGame::showSettings()
{
    bool quit = false;
    SDL_Event e;

    int volume = 85;  // Giá trị mặc định của âm lượng (50%)
    bool isDragging = false; // Kiểm tra nếu thanh trượt đang được kéo

    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            // Kiểm tra sự kiện nhấp chuột và kéo thanh trượt để thay đổi âm lượng
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Kiểm tra nếu người dùng nhấp vào thanh trượt âm lượng
                if (mouseX >= 600 && mouseX <= 950 && mouseY >= 200 && mouseY <= 230)
                {
                    isDragging = true;  // Bắt đầu kéo thanh trượt
                }
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT)
            {
                isDragging = false; // Ngừng kéo thanh trượt
            }
            if (e.type == SDL_MOUSEMOTION && isDragging)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Chỉnh âm lượng theo vị trí kéo thanh trượt
                if (mouseX >= 600 && mouseX <= 950)
                {
                    volume = (mouseX - 600) * 100 / 200;  // Tính giá trị âm lượng từ 0 đến 128
                    Mix_VolumeMusic(volume);  // Cập nhật âm lượng nhạc nền
                }
            }

            // Kiểm tra nếu người dùng nhấp vào nút Back to Menu
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 520 && mouseX <= 785 && mouseY >= 450 && mouseY <= 500)
                {
                    Mix_PlayChannel(-1, clickSound, 0);
                    showMenu();  // Quay lại menu chính
                }
            }
        }

        // Vẽ màn hình setting
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuBackgroundTexture, nullptr, &bgRect);  // Vẽ ảnh nền

        font = TTF_OpenFont("cutefont.ttf", 80);
        renderText("Settings", 450, 40, {255, 255, 255});

        font = TTF_OpenFont("cutefont.ttf", 50);
        // Vẽ văn bản âm lượng
        renderText("Volume", 350, 190, {255, 255, 255});

        // Vẽ thanh trượt âm lượng (màu trắng)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Thanh trượt màu trắng
        SDL_Rect volumeBar = { 595, 220, 355, 10 };  // Vị trí và kích thước của thanh trượt
        SDL_RenderFillRect(renderer, &volumeBar);

        // Vẽ nút chỉnh âm lượng hình tròn
        SDL_Color volumeColor = {255, 255, 255, 255};  // Màu nút chỉnh âm lượng
        int radius = 15;  // Đường kính của nút chỉnh âm lượng (hình tròn)
        int circleX = 600 + (volume * 200 / 100);  // Vị trí X của hình tròn (nút)
        int circleY = 225;  // Vị trí Y của hình tròn (nút)

        // Vẽ nút chỉnh âm lượng
        drawCircle(renderer, circleX, circleY, radius, volumeColor);  // Hàm vẽ hình tròn

        // Vẽ nút Back to Menu
        SDL_Rect backButtonRect = {500, 450, 100, 50};
        renderText("Back", 560, 460, {255, 255, 255});

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
