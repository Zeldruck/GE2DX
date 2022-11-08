#ifndef _SDLPP_TEXTURE_HPP_
#define _SDLPP_TEXTURE_HPP_

#include <Engine/Export.hpp>
#include <SDL.h>
#include <string>

class SDLpp_renderer;
class SDLpp_surface;

class GE2DX_ENGINE_API SDLpp_texture
{
public:
	SDLpp_texture(SDLpp_texture&&) noexcept;
	SDLpp_texture(const SDLpp_texture&) = delete;
	~SDLpp_texture();

	SDLpp_texture& operator=(const SDLpp_texture&) = delete;
	SDLpp_texture& operator=(SDLpp_texture&&) noexcept;

	static SDLpp_texture LoadFromFile(SDLpp_renderer&, const std::string&);
	static SDLpp_texture LoadFromSurface(SDLpp_renderer&, const SDLpp_surface&);
	
	const std::string& GetFilepath() const;
	SDL_Texture* GetHandle() const;
	SDL_Rect GetRect() const;


private:
	SDLpp_texture(SDL_Texture* texture, std::string filepath = "");

	std::string m_filepath;
	SDL_Texture* m_texture;
};

#endif // !_SDLPP_TEXTURE_HPP_
