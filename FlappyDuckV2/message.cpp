// Local includes:
#include "message.h"


// Library include:
#include <SDL_image.h>
#include <cassert>
#include <SDL_ttf.h>

Message::Message()
: m_pRenderer(0)
, m_pMessage(0)
, m_height(0)
, m_width(0)
{

}

Message::~Message()
{
	SDL_DestroyTexture(m_pMessage);
	m_pMessage = 0;

	//m_pRenderer removed in backbuffer;
}

bool
Message::Initialise(TTF_Font* pFont, const char* msg, SDL_Color rgb, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;
	
	SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, msg, rgb);
	if (pSurface == 0)
	{
		return false;
	}
	else
	{
		m_pMessage = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);

		if (m_pMessage == 0)
		{
			return false;
		}

		SDL_FreeSurface(pSurface);
	}
	SDL_SetTextureBlendMode(m_pMessage, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pMessage, 0, 0, &m_width, &m_height);

	return m_pMessage != 0;
}

int
Message::GetWidth() const
{
	assert(m_width);
	return m_width;
}

int
Message::GetHeight() const
{
	assert(m_height);
	return m_height;
}

SDL_Texture*
Message::GetTexture()
{
	return m_pMessage;
}