#ifndef _SDLPP_WINDOW_HPP_
#define _SDLPP_WINDOW_HPP_

#include <string>
#include <SDL.h>

class SDLpp_window
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