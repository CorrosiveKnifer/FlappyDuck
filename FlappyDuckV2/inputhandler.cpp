// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"

// Library includes:
#include <cassert>

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

bool 
InputHandler::Initialise()
{
	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			game.PlayerFlutter();
		}
	}
}
