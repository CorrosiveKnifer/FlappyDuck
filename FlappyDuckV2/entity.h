#pragma once
// Forward Declarations:
class BackBuffer;
class Sprite;

class Entity
{
	//Member Methods:
public:
	Entity();
	~Entity();
	bool Initialise(Sprite* sprite);

	virtual void IdleProcess(float deltaTime);
	virtual void Process(float deltaTime);
	virtual void Draw(BackBuffer& backBuffer);

	void SetDead(bool dead);
	bool IsDead() const;

	virtual bool IsCollidingWith(Entity& e);

	void SetPosition(float x, float y);
	void SetPositionX(float x);
	void SetPositionY(float y);

	float GetPositionX() const;
	float GetPositionY() const;

	int GetWidth();
	int GetHeight();

	void SetVerticalVelocity(int dx);
	void SetHorizontalVelocity(int dy);

	void SetAngle(float angle);
protected:
private:
	Entity(const Entity& entity);
	Entity& operator=(const Entity& entity);
	//Member Data:
public:
protected:
	Sprite* m_pSprite;

	float m_x;
	float m_y;

	float m_dx; //Velocity
	float m_dy;

	float m_d2x;
	float m_d2y;

	bool m_dead;
private:
};