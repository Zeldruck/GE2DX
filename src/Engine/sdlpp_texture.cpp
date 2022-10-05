#include <Engine/sdlpp_texture.hpp>
#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_surface.hpp>

SDLpp_texture::SDLpp_texture(SDLpp_texture&& _texturepp) noexcept
{
	std::swap(m_texture, _texturepp.m_texture);
}

SDLpp_texture::~SDLpp_texture()
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

SDLpp_texture& SDLpp_texture::operator=(SDLpp_texture&& _texturepp) noexcept
{
	std::swap(m_texture, _texturepp.m_texture);

	return *this;
}

SDLpp_texture SDLpp_texture::LoadFromFile(SDLpp_renderer& _renderer, const std::string& _filepath)
{
	return LoadFromSurface(_renderer, SDLpp_surface::LoadFromFile(_filepath));
}

SDLpp_texture SDLpp_texture::LoadFromSurface(SDLpp_renderer& _renderer, const SDLpp_surface& _surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer.GetHandle(), _surface.GetHandle());

	return SDLpp_texture(texture);
}

SDL_Texture* SDLpp_texture::GetHandle() const
{
	return m_texture;
}

SDL_Rect SDLpp_texture::GetRect() const
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &rect.w, &rect.h);

	return rect;
}

SDLpp_texture::SDLpp_texture(SDL_Texture* _texture) :
	m_texture(_texture)
{
}
