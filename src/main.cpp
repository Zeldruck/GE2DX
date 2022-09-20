#include <iostream>
#include "sdlpp.hpp"
#include "sdlpp_window.hpp"
#include "sdlpp_renderer.hpp"
#include "sdlpp_texture.hpp"
#include "sprite.hpp"

int main(int argc, char** argv)
{
    SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    SDLpp_texture bgTexture = SDLpp_texture::LoadFromFile(rendererpp, "assets/test.jpg");
    SDLpp_texture spritesheetTexture = SDLpp_texture::LoadFromFile(rendererpp, "assets/sprsh.png");

    SDL_Rect whBg;
    whBg.x = 0;
    whBg.y = 0;
    whBg.w = 2560;
    whBg.h = 1440;

    SDL_Rect whSpr;
    whSpr.x = 0;
    whSpr.y = 0;
    whSpr.w = 64;
    whSpr.h = 64;

    Sprite bg(bgTexture, whBg);
    bg.Resize(1280, 720);

    Sprite sprsh(spritesheetTexture, whSpr);
    sprsh.SetRect(whSpr);
    sprsh.Resize(256, 256);

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    float speedTime = 0.1f;
    float duration = speedTime;
    int index = 0;

    bool isRunning = true;

    while (isRunning)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

        SDL_Event event;

        while (SDLpp::PollEvent(&event) > 0) // Still have events to fetch
        {
	        if (event.type == SDL_QUIT)
	        {
                isRunning = false;
                break;
	        }

            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                std::cout << "x: " << event.button.x << ", y: " << event.button.y << std::endl;
            }
        }

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        if (duration > 0.f)
            duration -= deltaTime;
        else
        {
            duration = speedTime;
            index++;

            if (index * 64 >= 832)
            {
                index = 0;
            }

            sprsh.SetRect(SDL_Rect{ index * 64, 0, 64, 64 });
        }

        bg.Draw(rendererpp, 0, 0);

        sprsh.Draw(rendererpp, 100, 100);

        rendererpp.Present();
    }

    return 0;
}