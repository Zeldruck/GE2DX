#ifndef _SDLPP_SURFACE_HPP_
#define _SDLPP_SURFACE_HPP_

#include <Engine/Export.hpp>
#include <SDL.h>
#include <string>

class GE2DX_ENGINE_API SDLpp_surface
{
public:
	SDLpp_surface(int width, int height);
	SDLpp_surface(const SDLpp_surface&) = delete;
	SDLpp_surface(SDLpp_surface&&) noexcept;
	~SDLpp_surface();

	SDLpp_surface& operator=(const SDLpp_surface&) = delete;
	SDLpp_surface& operator=(SDLpp_surface&&) noexcept;

	SDL_Surface* GetHandle() const;

	void FillRect(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	bool IsValid() const;

	static SDLpp_surface LoadFromFile(const std::string&);

public:
	Uint8* GetPixels();
	const Uint8* GetPixels() const;

private:
	SDLpp_surface(SDL_Surface*);

	SDL_Surface* m_surface;
};

#endif // !_SDLPP_SURFACE_HPP_