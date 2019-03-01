#pragma once
// Library Includes:
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>

// Forward Declarations:
class Texture;
class Message;

class TextureManager
{
	//Member Methods:
public:
	TextureManager();
	~TextureManager();

	bool Initialise(SDL_Renderer* pRenderer);

	Texture* GetTexture(const char* pcFilename);
	Message* GetMessage(TTF_Font* pFont, const char* msg, SDL_Color rgb, int size);
protected:

private:
	TextureManager(const TextureManager& textureManager);
	TextureManager& operator=(const TextureManager& textureManager);

	//Member Data:
public:

protected:
	SDL_Renderer* m_pRenderer;

	std::map<std::string, Texture*> m_pLoadedTextures;
	std::map<std::string, Message*> m_pMessageTextures;
private:

};