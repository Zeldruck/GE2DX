#include <Engine/sprite.hpp>
#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_texture.hpp>
#include <Engine/Transform.hpp>

Sprite::Sprite(std::shared_ptr<const SDLpp_texture> texture) :
	Sprite(std::move(texture), texture->GetRect())
{
}

Sprite::Sprite(std::shared_ptr<const SDLpp_texture> texture, const SDL_Rect& rect) :
	m_texture(std::move(texture)),
	m_rect(rect),
	m_origin(0.f, 0.f),
	m_width(rect.w),
	m_height(rect.h)
{
}

void Sprite::Resize(int _w, int _h)
{
	m_width = _w;
	m_height = _h;
}

void Sprite::Draw(SDLpp_renderer& _renderer, const Transform& _cameraTransform, const Transform& _transform)
{
	SDL_Rect texRect = m_texture->GetRect();

	Vector2f originPos = m_origin * Vector2f(m_width, m_height);

	Vector2f topLeftCorner = _transform.TransformPoint(Vector2f(0.f, 0.f) - originPos);
	Vector2f topRightCorner = _transform.TransformPoint(Vector2f(static_cast<float>(m_width), 0.f) - originPos);
	Vector2f bottomLeftCorner = _transform.TransformPoint(Vector2f(0.f, static_cast<float>(m_height)) - originPos);
	Vector2f bottomRightCorner = _transform.TransformPoint(Vector2f(static_cast<float>(m_width), static_cast<float>(m_height)) - originPos);

	// Application de la caméra (transformation inverse)
	topLeftCorner = _cameraTransform.TransformInversePoint(topLeftCorner);
	topRightCorner = _cameraTransform.TransformInversePoint(topRightCorner);
	bottomLeftCorner = _cameraTransform.TransformInversePoint(bottomLeftCorner);
	bottomRightCorner = _cameraTransform.TransformInversePoint(bottomRightCorner);

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

const Vector2f& Sprite::GetOrigin() const
{
	return m_origin;
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

void Sprite::SetOrigin(const Vector2f& origin)
{
	m_origin = origin;
}
