#ifndef _SDLPP_HPP_
#define _SDLPP_HPP_

#include <SDL.h>

class SDLpp
{
public:
	SDLpp(Uint32 = 0);
	SDLpp(const SDLpp&) = delete;
	~SDLpp();

	static bool PollEvent(SDL_Event*);
};

#endif // !_SDLPP_HPP_