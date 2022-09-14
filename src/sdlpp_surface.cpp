#include "..\include\sdlpp_surface.hpp"
#include <SDL_image.h>

SDLpp_surface::SDLpp_surface(const std::string& _filepath)
{
	m_surface = IMG_Load(_filepath.c_str());
}

SDLpp_surface::~SDLpp_surface()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

SDL_Surface* SDLpp_surface::GetHandle()
{
	return m_surface;
}
