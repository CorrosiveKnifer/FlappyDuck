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

	void IdleProcess(float deltaTime);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void Flutter();

	void Score();
	void SetScore(int score);
	int GetScore();

protected:
private:
	//Member Data:
public:
protected:
	float m_dAng;
	bool m_isFalling;
	int m_score;

	float m_idle_MinAngle;
	float m_idle_MaxAngle;
	float m_idle_AngleIncrement;
	bool m_idle_IsIncreasingAngle;
private:
	const float MAX_ANGLE;
};