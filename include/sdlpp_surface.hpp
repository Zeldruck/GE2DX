#ifndef _SDLPP_SURFACE_HPP_
#define _SDLPP_SURFACE_HPP_

#include <SDL.h>
#include <string>

class SDLpp_surface
{
public:
	
	SDLpp_surface(const SDLpp_surface&) = delete;
	SDLpp_surface(SDLpp_surface&&) noexcept;
	~SDLpp_surface();

	SDLpp_surface& operator=(const SDLpp_surface&) = delete;
	SDLpp_surface& operator=(SDLpp_surface&&) noexcept;

	SDL_Surface* GetHandle() const;

	static SDLpp_surface LoadFromFile(const std::string&);

private:
	SDLpp_surface(SDL_Surface*);

	SDL_Surface* m_surface;
};

#endif // !_SDLPP_SURFACE_HPP_