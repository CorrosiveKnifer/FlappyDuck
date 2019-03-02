#pragma once
// Library includes:
#include <SDL.h>
#include <SDL_ttf.h>

class Message
{
	//Member Methods:
public:
	Message();
	~Message();

	bool Initialise(TTF_Font* pFont, const char* msg, SDL_Color rgb, SDL_Renderer* pRenderer);
	
	int GetWidth() const;
	int GetHeight() const;

	SDL_Texture* GetTexture();

protected:

private:
	Message(const Message& texture);
	Message& operator=(const Message& texture);

	//Member Data:
public:

protected:
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pMessage;

	int m_width;
	int m_height;

};