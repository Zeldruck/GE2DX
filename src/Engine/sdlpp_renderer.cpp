#include <Engine/sdlpp_renderer.hpp>
#include <Engine/sdlpp_window.hpp>
#include <Engine/sdlpp_texture.hpp>

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

void SDLpp_renderer::RenderCopy(std::shared_ptr<SDLpp_texture> _texture)
{
	SDL_RenderCopy(m_renderer, _texture->GetHandle(), nullptr, nullptr);
}

void SDLpp_renderer::RenderCopy(std::shared_ptr<SDLpp_texture> _texture, const SDL_Rect& _dstRect)
{
	SDL_RenderCopy(m_renderer, _texture->GetHandle(), nullptr, &_dstRect);
}

void SDLpp_renderer::RenderCopy(std::shared_ptr<SDLpp_texture> _texture, const SDL_Rect& _srcRect, const SDL_Rect& _dstRect)
{
	SDL_RenderCopy(m_renderer, _texture->GetHandle(), &_srcRect, &_dstRect);
}
