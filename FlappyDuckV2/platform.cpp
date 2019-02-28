// Local includes:
#include "platform.h"

Platform::Platform()
{

}

Platform::~Platform()
{

}

bool 
Platform::Initalise(Sprite* sprite)
{
	return Entity::Initialise(sprite);
}

void 
Platform::Draw(BackBuffer& backBuffer)
{
	Entity::Draw(backBuffer);
}