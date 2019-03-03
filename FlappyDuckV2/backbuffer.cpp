//Local include:
#include "backbuffer.h"
#include "texturemanager.h"
#include "sprite.h"
#include "texture.h"
#include "message.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>
#include <SDL_ttf.h>

BackBuffer::BackBuffer()
: m_pWindow(0)
, m_pRenderer(0)
, m_pTextureManager(0)
, m_width(0)
, m_height(0)
, m_clearRed(0xFF)
, m_clearGreen(0xFF)
, m_clearBlue(0xFF)
{

}

BackBuffer::~BackBuffer()
{
	delete m_pTextureManager;
	m_pTextureManager = 0;

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	IMG_Quit();
	SDL_Quit();
}

bool 
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		return false;
	}
	else
	{
		TTF_Init();
		m_pWindow = SDL_CreateWindow("Flappy Duck", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (m_pWindow == 0)
		{
			return false;
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

			if (m_pRenderer == 0)
			{
				return false;
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					return false;
				}
			}
		}
	}

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	m_fontColour = { 255, 255, 255 , 0};
	return true;
}

void 
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void 
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void 
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}

Sprite*
BackBuffer::CreateTexture(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	pSprite->Initialise(*pTexture);

	//Texture deleted in TextureManager;
	//Sprite deleted in Entity;

	return pSprite;
}

Sprite*
BackBuffer::CreateMessage(std::string msg, int size)
{
	assert(m_pTextureManager);
	TTF_Font* pFont = TTF_OpenFont("assets\\OpenSans.ttf", size);
	Message* pMessage = m_pTextureManager->GetMessage(pFont, msg.c_str(), m_fontColour, size);

	Sprite* pSprite = new Sprite();
	pSprite->Initialise(*pMessage);

	//Message deleted in Sprite;
	//Sprite deleted in Game;
	TTF_CloseFont(pFont);

	return pSprite;
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RendererFlip flip;
	if (sprite.GetFlip())
	{
		flip = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flip = SDL_FLIP_NONE;
	}

	if (sprite.GetMessage() == 0)
	{
		SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, sprite.GetAngle(), NULL, flip);
	}
	else
	{
		SDL_RenderCopyEx(m_pRenderer, sprite.GetMessage()->GetTexture(), 0, &dest, sprite.GetAngle(), NULL, flip);
	}
}