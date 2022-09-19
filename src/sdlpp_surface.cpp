#include "sdlpp_surface.hpp"
#include <SDL_image.h>
#include <iostream>

SDLpp_surface::SDLpp_surface(SDLpp_surface&& _surface) noexcept
{
	std::swap(m_surface, _surface.m_surface);
}

SDLpp_surface::~SDLpp_surface()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

SDLpp_surface& SDLpp_surface::operator=(SDLpp_surface&& _surface) noexcept
{
	std::swap(m_surface, _surface.m_surface);

	return *this;
}

SDL_Surface* SDLpp_surface::GetHandle() const
{
	return m_surface;
}

SDLpp_surface SDLpp_surface::LoadFromFile(const std::string& _filepath)
{
	SDL_Surface* surface = IMG_Load(_filepath.c_str());

	if (!surface)
		std::cerr << IMG_GetError() << std::endl;

	return SDLpp_surface(surface);
}

SDLpp_surface::SDLpp_surface(SDL_Surface* _surface):
	m_surface(_surface)
{
}
