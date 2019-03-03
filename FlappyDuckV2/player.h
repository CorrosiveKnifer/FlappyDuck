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
	bool IsCollidingWith(Entity& e);

	void IdleProcess(float deltaTime);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	void Flutter();

	void SetIdleBaseHeight(int base);

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

	int m_hitW;
	int m_hitH;

	float m_idle_Min;
	float m_idle_Max;
	int m_idle_Base;
	bool m_idle_IsIncreasingAngle;
private:
	const float MAX_ANGLE;
};