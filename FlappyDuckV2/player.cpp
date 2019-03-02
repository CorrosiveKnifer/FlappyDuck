// Local includes:
#include "player.h"
#include "sprite.h"
#include "backbuffer.h"

Player::Player()
: m_dAng(0)
, MAX_ANGLE(90)
, m_score(0)
, m_idle_IsIncreasingAngle(false)
{

}

Player::~Player()
{

}

bool 
Player::Initalise(Sprite* sprite)
{
	bool cond = Entity::Initialise(sprite);
	m_d2y = 750.0f;
	m_dAng = 160.0f;
	m_idle_MaxAngle = 30.0f;
	m_idle_MinAngle = -30.0f;
	m_idle_AngleIncrement = 35.0f;
	return cond;
}

void 
Player::IdleProcess(float deltaTime)
{
	if (m_idle_IsIncreasingAngle)
	{
		m_pSprite->SetAngle(m_pSprite->GetAngle() + (m_idle_AngleIncrement * deltaTime));
		SetPositionY(GetPositionY() + (m_dy * deltaTime));
	}
	else
	{
		m_pSprite->SetAngle(m_pSprite->GetAngle() - (m_idle_AngleIncrement * deltaTime));
		SetPositionY( GetPositionY() - ( m_dy * deltaTime));
	}
	if (m_pSprite->GetAngle() > m_idle_MaxAngle || m_pSprite->GetAngle() < m_idle_MinAngle)
	{
		m_idle_IsIncreasingAngle = !m_idle_IsIncreasingAngle;
	}

}

void 
Player::Process(float deltaTime)
{
	if (!m_dead) {
		Entity::Process(deltaTime);
		m_isFalling = m_dy > 0;
		if (m_isFalling) {
			if (m_pSprite->GetAngle() > MAX_ANGLE)
			{
				m_pSprite->SetAngle(90);
			}
			else if (m_pSprite->GetAngle() != MAX_ANGLE)
			{
				m_pSprite->SetAngle(m_pSprite->GetAngle() + (m_dAng * deltaTime));
			}
		}
	}
}

void 
Player::Draw(BackBuffer& backBuffer)
{
	Entity::Draw(backBuffer);
}

void
Player::Flutter()
{
	m_pSprite->SetAngle(-45);
	m_dy = -330;
	m_dx = 0;
}

void
Player::Score()
{
	m_score++;
}

void
Player::SetScore(int s)
{
	m_score = s;
}

int
Player::GetScore()
{
	return m_score;
}
