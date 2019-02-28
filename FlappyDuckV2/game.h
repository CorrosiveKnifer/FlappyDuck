#pragma once
// Local includes:
#include <vector>

//Forward Declarations:
class BackBuffer;
class Sprite;
class Player;
class InputHandler;
class Entity;

class Game
{
	//Member methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();

	bool Initialise();
	bool GameLoop();
	void Quit();
	void PlayerFlutter();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);

	Game();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	Sprite* m_pBackgroundSprite;
	Player* m_pPlayerObject;
	std::vector<Entity*> m_hitableEntities;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

private:

};