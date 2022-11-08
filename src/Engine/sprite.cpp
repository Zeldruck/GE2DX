#include <Engine/sprite.hpp>
#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_texture.hpp>
#include "Engine/transform.hpp"

Sprite::Sprite():
m_texture(nullptr), m_rect(), m_width(0), m_height(0)
{
}

Sprite::Sprite(std::shared_ptr<const SDLpp_texture> _texture):
	Sprite(std::move(_texture), _texture->GetRect())
{
	
}

Sprite::Sprite(std::shared_ptr<const SDLpp_texture> _texture, const SDL_Rect& _rect):
	m_texture(std::move(_texture)), m_rect(_rect), m_width(_rect.w), m_height(_rect.h)
{
}

void Sprite::Resize(int _w, int _h)
{
	m_width = _w;
	m_height = _h;
}

void Sprite::Draw(SDLpp_renderer& _renderer, const Transform& _cameraTransform, const Transform& _transform)
{
	if (m_texture == nullptr)
		return;

	Vector2f topLeftCorner = _transform.TransformPoint(Vector2f(0.f, 0.f));
	Vector2f topRightCorner = _transform.TransformPoint(Vector2f(m_width, 0.f));
	Vector2f bottomLeftCorner = _transform.TransformPoint(Vector2f(0.f, m_height));
	Vector2f bottomRightCorner = _transform.TransformPoint(Vector2f(m_width, m_height));

	// Application de la cam�ra (transformation inverse)
	topLeftCorner = _cameraTransform.TransformInversePoint(topLeftCorner);
	topRightCorner = _cameraTransform.TransformInversePoint(topRightCorner);
	bottomLeftCorner = _cameraTransform.TransformInversePoint(bottomLeftCorner);
	bottomRightCorner = _cameraTransform.TransformInversePoint(bottomRightCorner);

	SDL_Rect texRect = m_texture->GetRect();

	float invWidth = 1.f / texRect.w;
	float invHeight = 1.f / texRect.h;

	SDL_Vertex vert[4];
	vert[0].color = SDL_Color{ 255, 255, 255, 255 };
	vert[0].position = SDL_FPoint{ topLeftCorner.x, topLeftCorner.y };
	vert[0].tex_coord = SDL_FPoint{ m_rect.x * invWidth, m_rect.y * invHeight };

	vert[1].color = SDL_Color{ 255, 255, 255, 255 };
	vert[1].position = SDL_FPoint{ topRightCorner.x, topRightCorner.y };
	vert[1].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, m_rect.y * invHeight };

	vert[2].color = SDL_Color{ 255, 255, 255, 255 };
	vert[2].position = SDL_FPoint{ bottomLeftCorner.x, bottomLeftCorner.y };
	vert[2].tex_coord = SDL_FPoint{ m_rect.x * invWidth, (m_rect.y + m_rect.h) * invHeight };

	vert[3].color = SDL_Color{ 255, 255, 255, 255 };
	vert[3].position = SDL_FPoint{ bottomRightCorner.x, bottomRightCorner.y };
	vert[3].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, (m_rect.y + m_rect.h) * invHeight };

	int indices[6] = { 0, 1, 2, 2, 1, 3 };

	SDL_RenderGeometry(_renderer.GetHandle(), (m_texture) ? m_texture->GetHandle() : nullptr, vert, 4, indices, 6);
}

int Sprite::GetWidth() const
{
	return m_width;
}

int Sprite::GetHeight() const
{
	return m_height;
}

void Sprite::SetTexture(std::shared_ptr<const SDLpp_texture> _texture)
{
	m_texture = std::move(_texture);
	m_rect = _texture->GetRect();
	m_width = m_rect.w;
	m_height = m_rect.h;
}

void Sprite::SetRect(SDL_Rect _rect)
{
	m_rect = _rect;
}
