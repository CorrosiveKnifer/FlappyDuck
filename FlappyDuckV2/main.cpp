//Local include:
#include "game.h"

// Library includes:
#include <crtdbg.h>
#include <SDL.h>

int main(int argc, char** argv) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game& gameInstance = Game::GetInstance();
	if (!gameInstance.Initialise())
	{
		//Failed
		return (1);
	}

	while (gameInstance.GameLoop())
	{
		// No body.
	}

	Game::DestroyInstance();

	return 0;
}