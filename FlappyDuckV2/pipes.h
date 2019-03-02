#pragma once
// Local includes:
#include "entity.h"

class Pipes: public Entity
{
	//Member methods:
public:
	Pipes();
	~Pipes();
	bool Initialise(Sprite* upper, Sprite* lower);
	bool IsCollidingWith(Entity& e);

	void IdleProcess(float deltaTime);
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

	void SetGapSize(int size);
	void SetGapHeight(int cen_y);
	void SetPipeX(int x);

	void SetPipeVelocity(int dx);
	
	bool HasBeenScored();
	void BeenScored(bool val);

protected:
private:
	void UpdatePositions();

	//Member Data:
public:
protected:
private:
	bool m_scoredUpon;
	Entity* m_pUpperPipe;
	Entity* m_pLowerPipe;

	int m_gapSize;
	int m_gapH;
	int m_pipeX;
};