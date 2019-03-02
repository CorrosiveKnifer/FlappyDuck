// Local includes:
#include "entity.h"
#include "backbuffer.h"
#include "sprite.h"

// Library includes:
#include <cassert>

Entity::Entity()
: m_pSprite(0)
, m_x(0.0f)
, m_y(0.0f)
, m_dx(0.0f)
, m_dy(0.0f)
, m_d2x(0.0f)
, m_d2y(0.0f)
, m_dead(false)
{

}
Entity::~Entity()
{
	
}
bool
Entity::Initialise(Sprite* sprite)
{
	assert(sprite);
	m_pSprite = sprite;

	return true;
}

void 
Entity::IdleProcess(float deltaTime)
{
	//Do nothing
}
void 
Entity::Process(float deltaTime)
{
	//TODO MOVEMENT
	m_pSprite->Process(deltaTime);
	m_dx += m_d2x * deltaTime;
	m_dy += m_d2y * deltaTime;
	m_x += m_dx * deltaTime;
	m_y += m_dy * deltaTime;
	SetPosition(m_x, m_y);
}
void 
Entity::Draw(BackBuffer& backBuffer)
{
	backBuffer.DrawSprite(*m_pSprite);
}

void 
Entity::SetDead(bool dead)
{
	m_dead = dead;
}

bool 
Entity::IsDead() const
{
	return m_dead;
}

bool 
Entity::IsCollidingWith(Entity& e)
{
	bool x = (e.GetPositionX() + e.GetWidth() >= m_x) && (m_x + m_pSprite->GetWidth() >= e.GetPositionX());
	bool y = (e.GetPositionY() + e.GetHeight() >= m_y) && (m_y + m_pSprite->GetHeight() >= e.GetPositionY());
	return x && y;
}

void 
Entity::SetPosition(float x, float y) 
{
	SetPositionX(x);
	SetPositionY(y);
}

void 
Entity::SetPositionX(float x)
{
	m_x = x;
	m_pSprite->SetX(x);
}

void 
Entity::SetPositionY(float y)
{
	m_y = y;
	m_pSprite->SetY(y);
}

float 
Entity::GetPositionX() const
{
	return m_x;
}

float 
Entity::GetPositionY() const
{
	return m_y;
}

int 
Entity::GetWidth()
{
	return m_pSprite->GetWidth();
}

int 
Entity::GetHeight()
{
	return m_pSprite->GetHeight();
}

void 
Entity::SetVerticalVelocity(int dx)
{
	m_dx = dx;
}

void
Entity::SetHorizontalVelocity(int dy)
{
	m_dy = dy;
}

void
Entity::SetAngle(float angle)
{
	m_pSprite->SetAngle(angle);
}