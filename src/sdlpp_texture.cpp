#include "sdlpp_texture.hpp"
#include "sdlpp_renderer.hpp"
#include "sdlpp_surface.hpp"

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
	SDLpp_surface surface(_filepath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer.GetHandle(), surface.GetHandle());

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