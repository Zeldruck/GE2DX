#include "sprite.hpp"
#include "sdlpp_renderer.hpp"
#include "sdlpp_texture.hpp"

Sprite::Sprite(const SDLpp_texture& _texture):
	Sprite(_texture, _texture.GetRect())
{
	
}

Sprite::Sprite(const SDLpp_texture& _texture, SDL_Rect& _rect):
	m_texture(_texture), m_rect(_rect)
{
}

void Sprite::Draw(SDLpp_renderer& _renderer, int _x, int _y)
{
	SDL_Rect dest;
	dest.x = _x;
	dest.y = _y;
	dest.w = m_rect.w;
	dest.h = m_rect.h;

	_renderer.RenderCopy(m_texture, m_rect);
}
