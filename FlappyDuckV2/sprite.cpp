// This include:
#include "sprite.h"

// Local includes:
#include "backbuffer.h"
#include "texture.h"
#include "message.h"

Sprite::Sprite()
: m_pTexture(0)
, m_pMessage(0)
, m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
, m_angle(0.0f)
, m_centerX(0)
, m_centerY(0)
, m_flip(false)
{

}

Sprite::~Sprite()
{
	//m_pTexture deleted in TextureManager;
	//m_pMessage deleted in TextureManager; 
}

bool 
Sprite::Initialise(Texture& texture)
{
	m_pTexture = &texture;
	
	m_width = m_pTexture->GetWidth();
	m_height = m_pTexture->GetHeight();

	return (true);
}

bool
Sprite::Initialise(Message& message)
{
	m_pMessage = &message;

	m_width = m_pMessage->GetWidth();
	m_height = m_pMessage->GetHeight();

	return true;
}

void 
Sprite::Process(float deltaTime)
{

}

void 
Sprite::Draw(BackBuffer& backbuffer)
{
	backbuffer.DrawSprite(*this);
}

void 
Sprite::SetX(int x)
{
	m_x = x;
	m_centerX = x + GetWidth() / 2;
}

void 
Sprite::SetY(int y)
{
	m_y = y;
	m_centerY = y + GetHeight() / 2;
}

void 
Sprite::SetCoords(int x, int y)
{
	SetX(x);
	SetY(y);
}

int
Sprite::GetX() const
{
	return (m_x);
}

int
Sprite::GetY() const
{
	return (m_y);
}

int 
Sprite::GetCentX() const
{
	return m_centerX;
}

int 
Sprite::GetCentY() const
{
	return m_centerY;
}

void
Sprite::SetAngle(float angle)
{
	m_angle = angle;
}

float
Sprite::GetAngle() const
{
	return m_angle;
}

void
Sprite::SetCenter(int x, int y)
{
	m_centerX = x;
	m_centerY = y;
}

void
Sprite::SetHandleCenter()
{
	m_centerX = m_width / 2; 
	m_centerY = m_height / 2;
}

Texture* 
Sprite::GetTexture()
{
	return m_pTexture;
}

Message*
Sprite::GetMessage()
{
	return m_pMessage;
}

int 
Sprite::GetWidth() const
{
	return m_width;
}

int
Sprite::GetHeight() const
{
	return m_height;
}

void 
Sprite::SetFlip(bool flip)
{
	m_flip = flip;
}
bool Sprite::GetFlip()
{
	return m_flip;
}