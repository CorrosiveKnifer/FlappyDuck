#pragma once

// Forward Declarations:
class BackBuffer;
class Texture;
class Message;

class Sprite
{
	//Member Methods:
public:
	Sprite();
	~Sprite();

	bool Initialise(Texture& texture);
	bool Initialise(Message& message);

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);

	void SetX(int x);
	void SetY(int y);

	void SetCoords(int x, int y);

	int GetX() const;
	int GetY() const;
	int GetCentX() const;
	int GetCentY() const;

	void SetAngle(float angle);
	float GetAngle() const;

	void SetCenter(int x, int y);
	void SetHandleCenter();

	int GetWidth() const;
	int GetHeight() const;

	Texture* GetTexture();
	Message* GetMessage();

	void SetFlip(bool flip);
	bool GetFlip();
protected:

private:
	Sprite(const Sprite& sprite);
	Sprite& operator=(const Sprite& sprite);

	//Member Data:
public:

protected:
	Texture* m_pTexture;
	Message* m_pMessage;
	int m_x;
	int m_y;

	float m_angle;
	int m_centerX;
	int m_centerY;

	int m_width;
	int m_height;

	bool m_flip;
private:

};
