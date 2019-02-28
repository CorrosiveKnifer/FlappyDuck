#pragma once
// Local includes:
#include "entity.h"

//Forward Declarations:
class BackBuffer;
class Sprite;

class Platform : public Entity 
{
	//Member methods:
public:
	Platform();
	~Platform();
	bool Initalise(Sprite* sprite);

	void Draw(BackBuffer& backBuffer);
protected:
private:
	//Member Data:
public:
protected:
private:
};