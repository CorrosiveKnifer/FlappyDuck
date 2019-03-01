#pragma once
// Local includes:
#include "entity.h"

class Pipes: public Entity
{

public:
	Pipes();
	~Pipes();
	bool Initialise(Sprite* upper, Sprite* lower);
	bool IsCollidingWith(Entity& e);

	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetGapSize(int size);
	void SetGapHeight(int cen_y);
	void SetPipeX(int x);

	void HasPassed(Entity& e);
protected:
private:
	void UpdatePositions();

public:
protected:
private:
	Entity* m_pUpperPipe;
	Entity* m_pLowerPipe;

	int m_gapSize;
	int m_gapH;
	int m_pipeX;
};