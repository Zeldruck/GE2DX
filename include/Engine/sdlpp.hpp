#ifndef _SDLPP_HPP_
#define _SDLPP_HPP_

#include <Engine/Export.hpp>
#include <SDL.h>

class GE2DX_ENGINE_API SDLpp
{
public:
	SDLpp(Uint32 = 0);
	SDLpp(const SDLpp&) = delete;
	~SDLpp();

	static bool PollEvent(SDL_Event*);
};

#endif // !_SDLPP_HPP_