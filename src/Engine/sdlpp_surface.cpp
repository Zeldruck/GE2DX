#include <Engine/sdlpp_surface.hpp>
#include <SDL_image.h>
#include <cassert>
#include <iostream>

SDLpp_surface::SDLpp_surface(int width, int height)
{
	m_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
}

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

void SDLpp_surface::FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(m_surface);
	SDL_FillRect(m_surface, &rect, SDL_MapRGBA(m_surface->format, r, g, b, a));
}

bool SDLpp_surface::IsValid() const
{
	return m_surface != nullptr;
}

SDLpp_surface SDLpp_surface::LoadFromFile(const std::string& _filepath)
{
	SDL_Surface* surface = IMG_Load(_filepath.c_str());

	if (!surface)
		std::cerr << IMG_GetError() << std::endl;

	return SDLpp_surface(surface);
}

Uint8* SDLpp_surface::GetPixels()
{
	return static_cast<Uint8*>(m_surface->pixels);
}

const Uint8* SDLpp_surface::GetPixels() const
{
	return static_cast<const Uint8*>(m_surface->pixels);
}

SDLpp_surface::SDLpp_surface(SDL_Surface* _surface):
	m_surface(_surface)
{
}
