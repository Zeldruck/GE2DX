#include <iostream>
#include "sdlpp.hpp"
#include "sdlpp_window.hpp"
#include "sdlpp_renderer.hpp"
#include "sdlpp_texture.hpp"

#include "vector2.hpp"

int main(int argc, char** argv)
{
    /*SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    SDLpp_texture testTexture = SDLpp_texture::LoadFromFile(rendererpp, "assets/test.jpg");

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

        SDL_RenderCopy(rendererpp.GetHandle(), testTexture.GetHandle(), nullptr, nullptr);

        rendererpp.Present();
    }*/

    return 0;
}