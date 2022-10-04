#include <Engine/sprite.hpp>
#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_texture.hpp>

Sprite::Sprite(std::shared_ptr<SDLpp_texture> _texture):
	Sprite(_texture, _texture->GetRect())
{
	
}

Sprite::Sprite(std::shared_ptr<SDLpp_texture> _texture, SDL_Rect& _rect):
	m_texture(_texture), m_rect(_rect), m_width(_rect.w), m_height(_rect.h)
{
}

void Sprite::Resize(int _w, int _h)
{
	m_width = _w;
	m_height = _h;
}

void Sprite::Draw(SDLpp_renderer& _renderer, int _x, int _y)
{
	SDL_Rect dest;
	dest.x = _x;
	dest.y = _y;
	dest.w = m_width;
	dest.h = m_height;

	_renderer.RenderCopy(m_texture, m_rect, dest);
}

int Sprite::GetWidth() const
{
	return m_width;
}

int Sprite::GetHeight() const
{
	return m_height;
}

void Sprite::SetRect(SDL_Rect _rect)
{
	m_rect = _rect;
}
