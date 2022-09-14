#ifndef _SDLPP_TEXTURE_HPP_
#define _SDLPP_TEXTURE_HPP_

#include <SDL.h>
#include <string>

class SDLpp_renderer;

class SDLpp_texture
{
public:
	SDLpp_texture(SDLpp_texture&&);
	SDLpp_texture(const SDLpp_texture&) = delete;
	~SDLpp_texture();

	static SDLpp_texture LoadFromFile(SDLpp_renderer&, const std::string&);

	SDL_Texture* GetHandle();

private:
	SDLpp_texture(SDL_Texture*);

	SDL_Texture* m_texture;
};

#endif // !_SDLPP_TEXTURE_HPP_
