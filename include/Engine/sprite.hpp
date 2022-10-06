#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <Engine/Export.hpp>
#include <SDL.h>
#include <memory>

class SDLpp_texture;
class SDLpp_renderer;
class Transform;

class GE2DX_ENGINE_API Sprite
{
public:
	Sprite(std::shared_ptr<SDLpp_texture>);
	Sprite(std::shared_ptr<SDLpp_texture>, SDL_Rect&);
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	~Sprite() = default;

	Sprite& operator=(const Sprite&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Resize(int, int);

	void Draw(SDLpp_renderer&, const Transform&);

	int GetWidth() const;
	int GetHeight() const;

	void SetRect(SDL_Rect);

private:
	std::shared_ptr<SDLpp_texture> m_texture;
	SDL_Rect m_rect;
	int m_width, m_height;
};

#endif // !_SPRITE_HPP_