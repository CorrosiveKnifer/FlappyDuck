// Local includes:
#include "texture.h"


// Library include:
#include <SDL_image.h>
#include <cassert>

Texture::Texture()
: m_pRenderer(0)
, m_pTexture(0)
, m_height(0)
, m_width(0)
{
	
}

Texture::~Texture()
{
	SDL_DestroyTexture(m_pTexture);
	m_pTexture = 0;

	//m_pRenderer removed in backbuffer;
}

bool 
Texture::Initialise(const char* pcFilename, SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	SDL_Surface* pSurface = IMG_Load(pcFilename);

	if (pSurface == 0)
	{
		return false;
	}
	else
	{
		m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);

		if (m_pTexture == 0)
		{
			return false;
		}

		SDL_FreeSurface(pSurface);
	}

	SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(m_pTexture, 0, 0, &m_width, &m_height);

	return m_pTexture != 0;
}

int 
Texture::GetWidth() const
{
	assert(m_width); 
	return m_width;
}

int 
Texture::GetHeight() const
{
	assert(m_height);
	return m_height;
}

SDL_Texture* 
Texture::GetTexture()
{
	return m_pTexture;
}
