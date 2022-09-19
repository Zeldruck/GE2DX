#ifndef _SPRITE_HPP_
#define _SPRITE_HPP_

#include <SDL.h>

class SDLpp_texture;
class SDLpp_renderer;

class Sprite
{
public:
	Sprite(const SDLpp_texture&);
	Sprite(const SDLpp_texture&, SDL_Rect&);
	Sprite(const Sprite&) = default;
	Sprite(Sprite&&) = default;
	~Sprite() = default;

	Sprite& operator=(const Sprite&) = delete;
	Sprite& operator=(Sprite&&) = delete;

	void Draw(SDLpp_renderer&, int, int);

private:
	const SDLpp_texture& m_texture;
	SDL_Rect m_rect;
};

#endif // !_SPRITE_HPP_