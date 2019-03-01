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

	void Score();
	int GetScore();

protected:
private:
	//Member Data:
public:
protected:
	float m_dAng;
	bool m_isFalling;
	int m_score;
private:
	const float MAX_ANGLE;
};