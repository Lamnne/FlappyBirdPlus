#include "FlappyBirdPlus.h"
#include <fstream>

bool FlappyBirdGame::sure()
{
    bool confirmQuit = false;
    SDL_Event e;
    bool result = false;
    while (!confirmQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) confirmQuit = true;
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 350 && mouseX <= 450 && mouseY >= 450 && mouseY <= 500)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    result = true;
                    confirmQuit = true;
                }
                if (mouseX >= 800 && mouseX <= 900 && mouseY >= 450 && mouseY <= 500)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    result = false;
                    confirmQuit = true;
                }
            }
        }
        SDL_Rect ynRect = {200, 100, 800, 500};
        SDL_Texture* ynTexture = IMG_LoadTexture(renderer, "image/yn.png");
        if (ynTexture)
        {
            SDL_RenderCopy(renderer, ynTexture, nullptr, &ynRect);
            SDL_DestroyTexture(ynTexture);
        }
        else
        {
            renderText("yn.png missing!", 650, 300, {255, 0, 0});
        }

        font = TTF_OpenFont("Font/cutefont.ttf", 60);
        renderText("ARE YOU SURE" , 390, 220, {255, 255, 255});
        renderText("TO BUY THIS SKIN???", 300, 300, {255, 255, 255});
        font = TTF_OpenFont("Font/cutefont.ttf", 50);
        renderText("YES", 350, 450, {255, 255, 255});
        renderText("NO", 800, 450, {255, 255, 255});

        SDL_RenderPresent(renderer);
    }
    return result;
}

void FlappyBirdGame::oops()
{
    bool confirmQuit = false;
    SDL_Event e;
    while (!confirmQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)confirmQuit = true;
        }
        SDL_Rect oopRect = {200, 50, 800, 600};
        SDL_Texture* oopTexture = IMG_LoadTexture(renderer, "image/oop.png");
        if (oopTexture)
        {
            SDL_RenderCopy(renderer, oopTexture, nullptr, &oopRect);
            SDL_DestroyTexture(oopTexture);
        }
        else
        {
            renderText("oop.png missing!", 650, 300, {255, 0, 0});
        }

        font = TTF_OpenFont("Font/cutefont.ttf", 100);
        renderText("OOPS!!!" , 410, 80, {255, 255, 255});
        font = TTF_OpenFont("Font/cutefont.ttf", 40);
        renderText("YOU DON'T HAVE ENOUGH COIN:((", 250, 200, {255, 255, 255});
        SDL_RenderPresent(renderer);
    }
}

void FlappyBirdGame::loadUnlockedSkins() {
    ifstream file("unlocked_skins.txt");
    if (file.is_open()) {
        for (int i = 1; i <= 10; i++) {
            int value;
            file >> value;
            unlockedSkins[i] = (value == 1);
        }
        file.close();
    } else {
        unlockedSkins[1] = true;
        for (int i = 2; i <= 10; i++) {
            unlockedSkins[i] = false;
        }
    }
}

void FlappyBirdGame::saveUnlockedSkins() {
    std::ofstream file("unlocked_skins.txt");
    if (file.is_open()) {
        for (int i = 1; i <= 10; i++) {
            file << (unlockedSkins[i] ? 1 : 0) << " ";
        }
        file.close();
    }
}

void FlappyBirdGame::loadskin()
{
    if (skin == 0)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird1.png");
    }
    else if (skin == 1)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird2.png");
    }
    else if (skin == 2)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird3.png");
    }
    else if (skin == 3)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird4.png");
    }
    else if (skin == 4)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird5.png");
    }
    else if (skin == 5)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird6.png");
    }
    else if (skin == 6)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird7.png");
    }
    else if (skin == 7)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird8.png");
    }
    else if (skin == 8)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird9.png");
    }
    else if (skin == 9)
    {
        birdTexture = IMG_LoadTexture(renderer, "image/bird10.png");
    }
}

void FlappyBirdGame::loadmenuskin()
{
    SDL_Rect birdloadRect = {200, 200, 294, 252};
    SDL_Texture* tempTexture = nullptr;
    if (skin == 0)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird1.png");
    }
    else if (skin == 1)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird2.png");
    }
    else if (skin == 2)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird3.png");
    }
    else if (skin == 3)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird4.png");
    }
    else if (skin == 4)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird5.png");
    }
    else if (skin == 5)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird6.png");
    }
    else if (skin == 6)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird7.png");
    }
    else if (skin == 7)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird8.png");
    }
    else if (skin == 8)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird9.png");
    }
    else if (skin == 9)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird10.png");
    }
    if (tempTexture)
    {
        SDL_RenderCopy(renderer, tempTexture, nullptr, &birdloadRect);
        SDL_DestroyTexture(tempTexture);
    }
}

void FlappyBirdGame::loadchoose()
{
    SDL_Rect birdchooseRect = {780, 270, 140, 120};
    SDL_Texture* tempTexture = nullptr;
    if (choose == 0)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird1.png");
    }
    else if (choose == 1)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird2.png");
    }
    else if (choose == 2)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird3.png");
    }
    else if (choose == 3)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird4.png");
    }
    else if (choose == 4)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird5.png");
    }
    else if (choose == 5)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird6.png");
    }
    else if (choose == 6)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird7.png");
    }
    else if (choose == 7)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird8.png");
    }
    else if (choose == 8)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird9.png");
    }
    else if (choose == 9)
    {
        tempTexture = IMG_LoadTexture(renderer, "image/bird10.png");
    }
    if (tempTexture)
    {
        SDL_RenderCopy(renderer, tempTexture, nullptr, &birdchooseRect);
        SDL_DestroyTexture(tempTexture);
    }
}

void FlappyBirdGame::showWardrobe()
{
    SDL_Event e;
    loadTotalCoins();
    loadUnlockedSkins();
    while (!shouldQuit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                shouldQuit = true;
                break;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= 0 && mouseX <= 130 && mouseY >= 0 && mouseY <= 70)
                {
                    SDL_Delay(200);
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    showMenu();
                    return;
                }
                if (mouseX >= 1000 && mouseX <= 1050 && mouseY >= 300 && mouseY <= 350)
                {
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    if (choose == 9) choose = 0;
                    else choose++;
                }
                if (mouseX >= 650 && mouseX <= 700 && mouseY >= 300 && mouseY <= 350)
                {
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    if (choose == 0) choose = 9;
                    else choose--;
                }
                if (mouseX >= 830 && mouseX <= 930 && mouseY >= 420 && mouseY <= 480)
                    {
                    if (soundEnabled) Mix_PlayChannel(-1, clickSound, 0);
                    if (unlockedSkins[choose]) {
                        skin = choose;
                        loadskin();
                    }
                else if (totalCoins >= skinPrices[choose])
                    {
                        if(sure())
                        {
                            totalCoins -= skinPrices[choose];
                            unlockedSkins[choose] = true;
                            saveTotalCoins();
                            saveUnlockedSkins();
                        }
                    } else {
                        SDL_Delay(200);
                        oops();
                    }
                }
            }
        }
        if(!shouldQuit)
        {
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, wardrobebackgroundTexture, nullptr, &wbgRect);

            font = TTF_OpenFont("Font/cutefont.ttf", 80);
            renderText("Wardrobe", 430, 40, {255, 255, 255});
            font = TTF_OpenFont("Font/cutefont.ttf", 50);
            if (unlockedSkins[choose])
            {
                renderText("Ok", 830, 420, {255, 255, 255});
                SDL_Rect unlockRect = {810, 150, 75, 78};
                SDL_Texture* unlockTexture = IMG_LoadTexture(renderer, "image/unlock.png");
                SDL_RenderCopy(renderer, unlockTexture, nullptr, &unlockRect);
                SDL_DestroyTexture(unlockTexture);
            }
            else
            {
                std::string priceText = std::to_string(skinPrices[choose]) + "$";
                renderText(priceText.c_str(), 800, 420, {255, 255, 0});
                SDL_Rect lockRect = {820, 170, 53, 48};
                SDL_Texture* lockTexture = IMG_LoadTexture(renderer, "image/lock.png");
                SDL_RenderCopy(renderer, lockTexture, nullptr, &lockRect);
                SDL_DestroyTexture(lockTexture);
            }
            renderText("Back", 10, 10, {255, 255, 255});
            font = TTF_OpenFont("Font/cutefont.ttf", 30);
            renderText("Coins: " + to_string(totalCoins), 900, 10, {255, 255, 255});

            SDL_Rect rightRect = {1000, 300, 50, 50};
            SDL_Texture* rightTexture = IMG_LoadTexture(renderer, "image/right.png");
            SDL_RenderCopy(renderer, rightTexture, nullptr, &rightRect);
            SDL_DestroyTexture(rightTexture);

            SDL_Rect leftRect = {650, 300, 50, 50};
            SDL_Texture* leftTexture = IMG_LoadTexture(renderer, "image/left.png");
            SDL_RenderCopy(renderer, leftTexture, nullptr, &leftRect);
            SDL_DestroyTexture(leftTexture);

            loadchoose();
            loadmenuskin();

            SDL_RenderPresent(renderer);
        }
    }
}
