#include "..\include\sdlpp_renderer.hpp"
#include "sdlpp_window.hpp"

SDLpp_renderer::SDLpp_renderer(SDLpp_window& _windowpp, int _index, Uint32 _flags)
{
	m_renderer = SDL_CreateRenderer(_windowpp.GetHandle(), _index, _flags);
}

SDLpp_renderer::~SDLpp_renderer()
{
	SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer* SDLpp_renderer::GetHandle()
{
	return m_renderer;
}

void SDLpp_renderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

void SDLpp_renderer::SetDrawColor(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a)
{
	SDL_SetRenderDrawColor(m_renderer, _r, _g, _b, _a);
}


void SDLpp_renderer::Present()
{
	SDL_RenderPresent(m_renderer);
}
