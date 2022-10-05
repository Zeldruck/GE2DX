#include <iostream>
#include <Engine/InputSystem.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/SDLpp.hpp>
#include <Engine/SDLpp_window.hpp>
#include <Engine/SDLpp_renderer.hpp>
#include <Engine/SDLpp_texture.hpp>
#include <Engine/Sprite.hpp>
#include <Engine/Transform.hpp>

int main(int argc, char** argv)
{
    SDLpp sdlpp;

    SDLpp_window windowpp("GE2DX", 1280, 720);
    SDLpp_renderer rendererpp(windowpp);

    ResourceManager resourceManager(rendererpp);

    InputSystem::Instance().BindKeyPressed(SDLK_h, "SayHello");
    InputSystem::Instance().BindMouseButtonPressed(MouseButton::Right, "SayHello");

    InputSystem::Instance().OnAction("SayHello", []()
    {
        std::cout << "Hello world" << std::endl;
    });

    Sprite bg(ResourceManager::Instance().GetTexture("assets/test.jpg"));
    bg.Resize(1280, 720);

    Sprite sprsh(ResourceManager::Instance().GetTexture("assets/sprsh.png"));
    sprsh.SetRect(SDL_Rect{ 0, 0, 64, 64});
    sprsh.Resize(256, 256);


    SDL_Vertex wallVertices[6];
    wallVertices[0].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[0].position = SDL_FPoint{ 350.f, 500.f };
    wallVertices[0].tex_coord = SDL_FPoint{ 0.f, 0.f };
    wallVertices[1].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[1].position = SDL_FPoint{ 650.f, 500.f };
    wallVertices[1].tex_coord = SDL_FPoint{ 0.f, 0.f };
    wallVertices[2].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[2].position = SDL_FPoint{ 350.f, 300.f };
    wallVertices[2].tex_coord = SDL_FPoint{ 0.f, 0.f };

    wallVertices[3].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[3].position = SDL_FPoint{ 650.f, 500.f };
    wallVertices[3].tex_coord = SDL_FPoint{ 0.f, 0.f };
    wallVertices[4].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[4].position = SDL_FPoint{ 650.f, 300.f };
    wallVertices[4].tex_coord = SDL_FPoint{ 0.f, 0.f };
    wallVertices[5].color = SDL_Color{ 255, 255, 255, 255 };
    wallVertices[5].position = SDL_FPoint{ 350.f, 300.f };
    wallVertices[5].tex_coord = SDL_FPoint{ 0.f, 0.f };

    SDL_Vertex tVertices[3];
    tVertices[0].color = SDL_Color{ 255, 0, 0, 255 };
    tVertices[0].position = SDL_FPoint{ 300.f, 300.f };
    tVertices[0].tex_coord = SDL_FPoint{ 0.f, 0.f };

    tVertices[1].color = SDL_Color{ 255, 0, 0, 255 };
    tVertices[1].position = SDL_FPoint{ 700.f, 300.f };
    tVertices[1].tex_coord = SDL_FPoint{ 0.f, 0.f };

    tVertices[2].color = SDL_Color{ 255, 0, 0, 255 };
    tVertices[2].position = SDL_FPoint{ 500.f, 150.f };
    tVertices[2].tex_coord = SDL_FPoint{ 0.f, 0.f };

    SDL_Vertex doorVertices[6];
    doorVertices[0].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[0].position = SDL_FPoint{ 475.f, 500.f };
    doorVertices[0].tex_coord = SDL_FPoint{ 0.f, 0.f };
    doorVertices[1].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[1].position = SDL_FPoint{ 475.f, 400.f };
    doorVertices[1].tex_coord = SDL_FPoint{ 0.f, 0.f };
    doorVertices[2].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[2].position = SDL_FPoint{ 525.f, 500.f };
    doorVertices[2].tex_coord = SDL_FPoint{ 0.f, 0.f };
    doorVertices[3].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[3].position = SDL_FPoint{ 525.f, 500.f };
    doorVertices[3].tex_coord = SDL_FPoint{ 0.f, 0.f };
    doorVertices[4].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[4].position = SDL_FPoint{ 525.f, 400.f };
    doorVertices[4].tex_coord = SDL_FPoint{ 0.f, 0.f };
    doorVertices[5].color = SDL_Color{ 0, 0, 0, 255 };
    doorVertices[5].position = SDL_FPoint{ 475.f, 400.f };
    doorVertices[5].tex_coord = SDL_FPoint{ 0.f, 0.f };



    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    float speedTime = 0.1f;
    float duration = speedTime;
    int index = 0;

    bool isRunning = true;

    while (isRunning)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = static_cast<float>(now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

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

        SDL_Event event;

        while (SDLpp::PollEvent(&event) > 0) // Still have events to fetch
        {
	        if (event.type == SDL_QUIT)
	        {
                isRunning = false;
                break;
	        }

            InputSystem::Instance().HandleEvent(event);
        }

        rendererpp.SetDrawColor(0, 0, 0);
        rendererpp.Clear();

        bg.Draw(rendererpp, 0, 0);
        sprsh.Draw(rendererpp, 100, 100);

        SDL_RenderGeometry(rendererpp.GetHandle(), nullptr, wallVertices, 6, nullptr, 0);
        SDL_RenderGeometry(rendererpp.GetHandle(), nullptr, doorVertices, 6, nullptr, 0);
        SDL_RenderGeometry(rendererpp.GetHandle(), nullptr, tVertices, 3, nullptr, 0);

        rendererpp.Present();
    }

    return 0;
}