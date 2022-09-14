#include "sdlpp_texture.hpp"
#include "sdlpp_renderer.hpp"

#include <SDL_image.h>

SDLpp_texture::SDLpp_texture(SDLpp_texture&& _texturepp)
{
	m_texture = _texturepp.m_texture;
	_texturepp.m_texture = nullptr;
}

SDLpp_texture::~SDLpp_texture()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

SDLpp_texture SDLpp_texture::LoadFromFile(SDLpp_renderer& _renderer, const std::string& _filepath)
{
	SDL_Surface* surface = IMG_Load(_filepath.c_str());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer.GetHandle(), surface);

	SDL_FreeSurface(surface);

	return SDLpp_texture(texture);
}

SDL_Texture* SDLpp_texture::GetHandle()
{
	return m_texture;
}

SDLpp_texture::SDLpp_texture(SDL_Texture* _texture) :
	m_texture(_texture)
{
}