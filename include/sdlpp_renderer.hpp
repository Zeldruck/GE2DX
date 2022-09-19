#ifndef _SDLPP_RENDERER_HPP_
#define _SDLPP_RENDERER_HPP_

#include <SDL.h>

class SDLpp_window;
class SDLpp_texture;

class SDLpp_renderer
{
public:
	SDLpp_renderer(SDLpp_window&, int = 0, Uint32 = 0);
	SDLpp_renderer(const SDLpp_renderer&) = delete;
	~SDLpp_renderer();

	SDL_Renderer* GetHandle();

	void Clear();
	void SetDrawColor(Uint8, Uint8, Uint8, Uint8 = 255);
	void Present();
	void RenderCopy(const SDLpp_texture&);
	void RenderCopy(const SDLpp_texture&, const SDL_Rect&);
	void RenderCopy(const SDLpp_texture&, const SDL_Rect&, const SDL_Rect&);


private:
	SDL_Renderer* m_renderer;

};

#endif // !_SDLPP_RENDERER_HPP_