// Local includes:
#include "player.h"
#include "sprite.h"
#include "backbuffer.h"

Player::Player()
: m_dAng(0)
, MAX_ANGLE(90)
, m_score(0)
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
	return cond;
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
	m_dy = -350;
	m_dx = 0;
}

void
Player::Score()
{
	m_score++;
}
int
Player::GetScore()
{
	return m_score;
}
