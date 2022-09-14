#include "..\include\sdlpp.hpp"

SDLpp::SDLpp(Uint32 _flags)
{
	SDL_Init(_flags);
}

SDLpp::~SDLpp()
{
	SDL_Quit();
}

bool SDLpp::PollEvent(SDL_Event* _event)
{
	return SDL_PollEvent(_event);
}
