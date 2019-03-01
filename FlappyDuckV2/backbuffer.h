#pragma once

// Library includes:
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

// Forward Declarations:
class TextureManager;
class Sprite;

class BackBuffer 
{
//Member Methods
public:
	BackBuffer();
	~BackBuffer();
	bool Initialise(int width, int height);
	
	void Clear();
	void Present();
	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);
	Sprite* CreateTexture(const char* pcFilename);
	Sprite* CreateMessage(std::string msg);
	void DrawSprite(Sprite& sprite);
	void RenderText(std::string msg, int x, int y);

protected:

private:
	BackBuffer(const BackBuffer& backbuffer);
	BackBuffer& operator=(const BackBuffer& backbuffer);

//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;

	TTF_Font* m_pFont;
	int m_FontSize;
	SDL_Color m_fontColour;
private:

};