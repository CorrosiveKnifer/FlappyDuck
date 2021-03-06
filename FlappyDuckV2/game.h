#pragma once
// Library includes:
//#include <vector>

//Forward Declarations:
class BackBuffer;
class Sprite;
class Player;
class InputHandler;
class Entity;
class Platform;
class Pipes;
class PipeQueue;

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
	void SpaceBar();
	void RKey();
	void StartPipes();
	void RestartPipes(Pipes* p);
	void Restart();
	void CheckScoreUpdate();

protected:
	void IdleProcess(float deltaTime);
	void Process(float deltaTime);
	void ScoreProcess(float deltaTime);
	void Draw(BackBuffer& backBuffer);

private:
	Game(const Game& game);
	Game& operator=(const Game& game);

	Game();

	void PipeChecks();
	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;

	int m_width;
	int m_height;
	int m_state;
	int m_highScore;
	int m_pipeGapSize;
	bool m_looping;
	bool m_countdown;
	float m_countdownCurrent;
	float m_countdownMax;

	//Sprites
	Sprite* m_pBackgroundSprite;

	//Entities
	Player* m_pPlayerObject;
	Platform* m_pPlatform;
	PipeQueue* m_pPipeEntities;

	//Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;

	//Messages
	Sprite* m_pStartText;
	Sprite* m_pScoreText;
	Sprite* m_pHighscoreText;
	Sprite* m_pRestartText;
	Sprite* m_pBoard;
private:

};