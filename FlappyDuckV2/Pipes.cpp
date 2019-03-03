// Local includes:
#include "pipes.h"
#include "entity.h"
#include "sprite.h"

// Library includes:
#include <cassert>

Pipes::Pipes()
	: m_pUpperPipe(0)
	, m_pLowerPipe(0)
	, m_gapSize(0)
	, m_gapH(0)
	, m_pipeX(0)
	, m_scoredUpon(false)
{

}
Pipes::~Pipes()
{
	delete m_pUpperPipe;
	m_pUpperPipe = 0;

	delete m_pLowerPipe;
	m_pLowerPipe = 0;
}

bool 
Pipes::Initialise(Sprite* base, Sprite* upper, Sprite* lower)
{
	upper->SetAngle(180);
	m_pUpperPipe = new Entity();
	m_pLowerPipe = new Entity();
	upper->SetFlip(true);
	Entity::Initialise(base);
	return m_pUpperPipe->Initialise(upper) && m_pLowerPipe->Initialise(lower);
}

bool 
Pipes::IsCollidingWith(Entity& e)
{
	return m_pUpperPipe->IsCollidingWith(e) || m_pLowerPipe->IsCollidingWith(e);
}

void 
Pipes::IdleProcess(float deltaTime)
{
	Pipes::Process(deltaTime);
}

void 
Pipes::Process(float deltaTime)
{
	if (!m_dead) {
		m_pUpperPipe->Process(deltaTime);
		m_pLowerPipe->Process(deltaTime);
		SetPositionX(m_pUpperPipe->GetPositionX());
	}
}

void 
Pipes::Draw(BackBuffer& backBuffer)
{
	m_pUpperPipe->Draw(backBuffer);
	m_pLowerPipe->Draw(backBuffer);
}

void 
Pipes::SetGapSize(int size)
{
	m_gapSize = size;
	UpdatePositions();
}

void 
Pipes::SetGapHeight(int cen_y)
{
	m_gapH = cen_y;
	SetPositionY(cen_y);
	UpdatePositions();
}

void
Pipes::SetPipeX(int x)
{
	m_pipeX = x;
	SetPositionX(x);
	UpdatePositions();
}

void 
Pipes::UpdatePositions()
{
	//Upper
	int x1 = 0;
	int y1 = 0; 

	//Lower
	int x2 = 0;
	int y2 = 0; 
	
	x1 = m_pipeX - m_pUpperPipe->GetWidth() / 2;
	y1 = m_gapH - (m_gapSize / 2) - m_pUpperPipe->GetHeight();
	x2 = m_pipeX - m_pLowerPipe->GetWidth() / 2;
	y2 = m_gapH + (m_gapSize / 2);

	m_pUpperPipe->SetPosition(x1, y1);
 	m_pLowerPipe->SetPosition(x2, y2);
}

void 
Pipes::SetPipeVelocity(int dx)
{
	m_pUpperPipe->SetVerticalVelocity(dx);
	m_pLowerPipe->SetVerticalVelocity(dx);
}

bool Pipes::HasBeenScored()
{
	return m_scoredUpon;
}

void 
Pipes::BeenScored(bool val)
{
	m_scoredUpon = val;
}