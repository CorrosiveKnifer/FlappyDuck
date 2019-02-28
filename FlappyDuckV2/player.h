#pragma once
// Local includes:
#include "entity.h"

//Forward Declarations:
class BackBuffer;

class Player: public Entity
{
	//Member methods:
public:
	Player();
	~Player();
	bool Initalise(Sprite* sprite);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void Flutter();

protected:
private:
	//Member Data:
public:
protected:
	float m_dAng;
	bool m_isFalling;

private:
	const float MAX_ANGLE;
};