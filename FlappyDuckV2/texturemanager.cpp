// Local includes:
#include "texturemanager.h"
#include "texture.h"
#include "message.h"

// Library includes:
#include <SDL.h>

TextureManager::TextureManager()
: m_pRenderer(0)
{

}

TextureManager::~TextureManager()
{
	
	std::map<std::string, Texture*>::iterator iter = m_pLoadedTextures.begin();
	while (iter != m_pLoadedTextures.end())
	{
		delete (iter->second);
		iter++;
	}
	m_pLoadedTextures.clear();

	std::map<std::string, Message*>::iterator iter2 = m_pMessageTextures.begin();
	while (iter2 != m_pMessageTextures.end())
	{
		delete (iter2->second);
		iter2++;
	}
	m_pMessageTextures.clear();

	//m_pRenderer deleted in backbuffer;
}

bool 
TextureManager::Initialise(SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	return (true);
}

Texture*
TextureManager::GetTexture(const char* pcFilename)
{
	Texture* pTexture = 0;

	if (m_pLoadedTextures.find(pcFilename) == m_pLoadedTextures.end())
	{
		// Not already loaded...
		pTexture = new Texture();
		pTexture->Initialise(pcFilename, m_pRenderer);
		m_pLoadedTextures[pcFilename] = pTexture;
	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[pcFilename];
	}

	return pTexture;
}
Message*
TextureManager::GetMessage(TTF_Font* pFont, const char* msg, SDL_Color rgb, int size)
{
	Message* pMessage = 0;

	if (m_pMessageTextures.find(msg) == m_pMessageTextures.end())
	{
		// Not already loaded...
		pMessage = new Message();
		pMessage->Initialise(pFont, msg, rgb, m_pRenderer);
		m_pMessageTextures[msg] = pMessage;
	}
	else
	{
		// Is already loaded...
		pMessage = m_pMessageTextures[msg];
	}

	return pMessage;
}
