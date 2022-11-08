#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <Engine/Export.hpp>
#include <Engine/Renderable.hpp>
#include <Engine/vector2.hpp>
#include <SDL.h>
#include <memory>

class SDLpp_texture;
class SDLpp_renderer;
class Transform;

class GE2DX_ENGINE_API Sprite : public Renderable
{
public:
	Sprite();
	Sprite(std::shared_ptr<const SDLpp_texture>);
	Sprite(std::shared_ptr<const SDLpp_texture>, const SDL_Rect&);
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	~Sprite() = default;

	Sprite& operator=(const Sprite&) = default;
	Sprite& operator=(Sprite&&) = delete;

	void Resize(int, int);

	void Draw(SDLpp_renderer& renderer, const Transform& cameraTransform, const Transform& transform) override;

	int GetWidth() const;
	int GetHeight() const;
	const Vector2f& GetOrigin() const;

	void SetTexture(std::shared_ptr<const SDLpp_texture>);
	void SetRect(SDL_Rect);
	void SetOrigin(const Vector2f&);

private:
	std::shared_ptr<const SDLpp_texture> m_texture;
	SDL_Rect m_rect;
	Vector2f m_origin;
	int m_width, m_height;
};

#endif // !_SPRITE_HPP_