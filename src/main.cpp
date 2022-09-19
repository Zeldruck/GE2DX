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

    SDLpp_texture testTexture = SDLpp_texture::LoadFromFile(rendererpp, "assets/test.jpg");

    SDL_Rect wh;
    wh.x = 0;
    wh.y = 0;
    wh.w = 1280;
    wh.h = 720;

    Sprite testSprite(testTexture, wh);

    bool isRunning = true;

    while (isRunning)
    {
        SDL_Event event;

        while (SDLpp::PollEvent(&event) > 0) // Still have events to fetch
        {
	        if (event.type == SDL_QUIT)
	        {
                isRunning = false;
                break;
	        }
        }

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        testSprite.Draw(rendererpp, 0, 0);

        rendererpp.Present();
    }

    return 0;
}