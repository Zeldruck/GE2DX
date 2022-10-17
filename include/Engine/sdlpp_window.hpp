#ifndef _SDLPP_WINDOW_HPP_
#define _SDLPP_WINDOW_HPP_

#include <Engine/Export.hpp>
#include <string>
#include <SDL.h>

class GE2DX_ENGINE_API SDLpp_window
{
public:
	SDLpp_window(const std::string&, int, int, Uint32 = 0);
	SDLpp_window(const std::string&, int, int, int, int, Uint32 = 0);
	SDLpp_window(const SDLpp_window&) = delete;
	~SDLpp_window();

	SDL_Window* GetHandle();

private:
	SDL_Window* m_window;

};

#endif // !_SDLPP_WINDOW_HPP_