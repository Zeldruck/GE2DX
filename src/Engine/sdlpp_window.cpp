#include "..\include\sdlpp_window.hpp"

SDLpp_window::SDLpp_window(const std::string& _title, int _width, int _height, Uint32 _flags):
SDLpp_window(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, _flags)
{
}

SDLpp_window::SDLpp_window(const std::string& _title, int _xPos, int _yPos, int _width, int _height, Uint32 _flags)
{
	m_window = SDL_CreateWindow(_title.c_str(), _xPos, _yPos, _width, _height, _flags);
}

SDLpp_window::~SDLpp_window()
{
	SDL_DestroyWindow(m_window);
}

SDL_Window* SDLpp_window::GetHandle()
{
	return m_window;
}