// Local includes:
#include "platform.h"

Platform::Platform()
{

}

Platform::~Platform()
{

}

void 
Platform::IdleProcess(float deltaTime)
{
	Entity::Process(deltaTime);
}
void 
Platform::Process(float deltaTime)
{
	Entity::Process(deltaTime);
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