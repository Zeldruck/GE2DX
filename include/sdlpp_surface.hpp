#ifndef _SDLPP_SURFACE_HPP_
#define _SDLPP_SURFACE_HPP_

#include <SDL.h>
#include <string>

class SDLpp_surface
{
public:
	SDLpp_surface(const std::string&);
	SDLpp_surface(const SDLpp_surface&) = delete;
	~SDLpp_surface();

	SDL_Surface* GetHandle();

private:
	SDL_Surface* m_surface;
};

#endif // !_SDLPP_SURFACE_HPP_