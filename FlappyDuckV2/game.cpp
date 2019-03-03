//Local include:
#include "game.h"
#include "backbuffer.h"
#include "sprite.h"
#include "player.h"
#include "inputhandler.h"
#include "platform.h"
#include "pipes.h"
#include "PipeQueue.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>
#include <vector>
#include <fstream>
#include <sstream> 
#include <ctime>

// Static Members:
Game* Game::sm_pInstance = 0;

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_countdown(false)
, m_state(0)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_pPlayerObject(0)
, m_width(0)
, m_height(0)
, m_pPlatform(0)
, m_pPipeEntities(0)
, m_countdownCurrent(0.0f)
, m_countdownMax(2.0f)
, m_pBoard(0)
, m_highScore(0)
, m_pStartText(0)
, m_pScoreText(0)
, m_pHighscoreText(0)
, m_pRestartText(0)
, m_pipeGapSize(175)
{

}

Game& 
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	//assert(sm_pInstance);

	return (*sm_pInstance);
}

void 
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;

}

Game::~Game()
{
	//Game Handlers
	delete m_pBackBuffer;
	m_pBackBuffer = 0;
	delete m_pInputHandler;
	m_pInputHandler = 0;

	//Entities
	delete m_pPlayerObject;
	m_pPlayerObject = 0;
	delete m_pPlatform;
	m_pPlatform = 0;
	delete m_pPipeEntities;
	m_pPipeEntities = 0;

	//Sprites*
	delete m_pBackgroundSprite;
	m_pBackgroundSprite = 0;
	delete m_pStartText;
	m_pStartText = 0;
	delete m_pScoreText;
	m_pScoreText = 0;
	delete m_pHighscoreText;
	m_pHighscoreText = 0;
	delete m_pRestartText;
	m_pRestartText = 0;
	delete m_pBoard;
	m_pBoard = 0;
}

bool 
Game::Initialise()
{
	m_width = 414;
	m_height = 736;

	srand(time(0));
	
	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(m_width, m_height))
	{
		return false;
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		return (false);
	}

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;
	
	m_pBackgroundSprite = m_pBackBuffer->CreateTexture("assets\\background.png");

	m_pPlatform = new Platform();
	m_pPlatform->Initialise(m_pBackBuffer->CreateTexture("assets\\platform.png"));
	m_pPlatform->SetPositionY(736 - m_pPlatform->GetHeight());

	m_pPlayerObject = new Player();
	m_pPlayerObject->Initalise(m_pBackBuffer->CreateTexture("assets\\player.png"));
	int w = (m_width - m_pPlayerObject->GetWidth()) / 2;
	int h = ((m_height - m_pPlatform->GetHeight()) - m_pPlayerObject->GetHeight()) / 2;
	m_pPlayerObject->SetPosition(w, h);
	m_pPlayerObject->SetHorizontalVelocity(30);
	m_pPlayerObject->SetIdleBaseHeight(h);

	std::ifstream scoreFile;
	scoreFile.open("assets\\highscore.txt");
	if (!scoreFile.is_open())
	{
		return false;
	}
	std::string scoreString;
	getline(scoreFile, scoreString);
	std::stringstream geek(scoreString);
	geek >> m_highScore;
	scoreFile.close();

	m_pStartText = m_pBackBuffer->CreateMessage("[Spacebar] to start", 24);
	m_pStartText->SetCoords((m_width - m_pStartText->GetWidth()) / 2, 500);
	m_pRestartText = m_pBackBuffer->CreateMessage("[R] to restart", 24);
	m_pRestartText->SetCoords((m_width - m_pRestartText->GetWidth()) / 2, 500);

	m_pScoreText = m_pBackBuffer->CreateMessage("0", 50);
	m_pHighscoreText = m_pBackBuffer->CreateMessage(std::to_string(m_highScore), 50);
	m_pHighscoreText->SetCoords((m_width - m_pHighscoreText->GetWidth()) / 2, 75 + m_pHighscoreText->GetHeight());

	m_pPipeEntities = new PipeQueue();
	m_pPipeEntities->Initialise();
	
	Pipes* p1 = new Pipes();
	Sprite* temp1 = m_pBackBuffer->CreateTexture("assets\\pipe.png"); //Base
	Sprite* temp2 = m_pBackBuffer->CreateTexture("assets\\pipe.png"); //Upper
	Sprite* temp3 = m_pBackBuffer->CreateTexture("assets\\pipe.png"); //Lower
	p1->Initialise(temp1, temp2, temp3);
	p1->SetGapSize(m_pipeGapSize);
	p1->SetGapHeight(w); 
	p1->SetPipeX(m_width + p1->GetWidth() / 2);
	p1->SetPipeVelocity(-165);
	p1->SetDead(true);
	m_pPipeEntities->Push_to_back(p1);

	int range = m_height - (m_pipeGapSize * 2);
	int y = rand() % range + m_pipeGapSize; //(m_pipeGapSize) to (m_height - m_pipeGapSize)

	Pipes* p2 = new Pipes();
	temp1 = m_pBackBuffer->CreateTexture("assets\\pipe.png");
	temp2 = m_pBackBuffer->CreateTexture("assets\\pipe.png");
	temp3 = m_pBackBuffer->CreateTexture("assets\\pipe.png");
	p2->Initialise(temp1, temp2, temp3);
	p2->SetGapSize(m_pipeGapSize);
	p2->SetGapHeight(y);
	p2->SetPipeX(m_width + p2->GetWidth() / 2);
	p2->SetPipeVelocity(-165);
	p2->SetDead(true);
	m_pPipeEntities->Push_to_back(p2);

	m_pBoard = m_pBackBuffer->CreateTexture("assets\\scoreboard.png");
	m_pBoard->SetCoords((m_width - m_pBoard->GetWidth()) / 2, 74);
	return true;
}

void 
Game::CheckScoreUpdate()
{
	if (m_highScore < m_pPlayerObject->GetScore())
	{
		m_highScore = m_pPlayerObject->GetScore();
		delete m_pHighscoreText;
		m_pHighscoreText =m_pBackBuffer->CreateMessage(std::to_string(m_highScore), 50);
		m_pHighscoreText->SetCoords((m_width - m_pHighscoreText->GetWidth()) / 2, 75 + m_pHighscoreText->GetHeight());
		std::ofstream highscoreFile("assets\\highscore.txt");
		if (highscoreFile.is_open())
		{
			highscoreFile << std::to_string(m_highScore);
		}
		highscoreFile.close();
	}
}

bool 
Game::GameLoop()
{
	const float frame = 1.0f / 60.0f;
	
	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		//Get difference in refresh time
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= frame)
		{
			switch (m_state)
			{
			case 0: //Idle
				IdleProcess(frame);
				break;
			case 1: //Game
				Process(frame);
				break;
			case 2: //ScoreDisplay
				ScoreProcess(frame);
				break;
			}
			m_lag -= frame;

			++m_numUpdates;
		}
		Draw(*m_pBackBuffer);
	}

	return m_looping;
}

void
Game::IdleProcess(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}
	m_pPlayerObject->IdleProcess(deltaTime);
}

void 
Game::Process(float deltaTime)
{
	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	m_pPlayerObject->Process(deltaTime);
	if (m_countdown)
	{
		m_countdownCurrent += deltaTime;
		if(m_countdownCurrent >= m_countdownMax)
		{
			m_countdown = false;
			m_countdownCurrent = 0;
			StartPipes();
		}
	}
	else
	{
		for (auto& pipes : m_pPipeEntities->GetVector())
		{
			if (pipes->IsCollidingWith(*m_pPlayerObject))
			{
				m_pPlayerObject->SetDead(true);
				CheckScoreUpdate();
				m_state = 2;
			}
			else
			{
				if (!pipes->IsDead())
				{
					pipes->Process(deltaTime);
				}
			}
			if ((0 - pipes->GetWidth()) >= pipes->GetPositionX())
			{
				RestartPipes(pipes);
			}
			if (m_pPlayerObject->IsDead())
			{
				pipes->SetDead(true);
			}
		}
	}
	if (m_pPlatform->IsCollidingWith(*m_pPlayerObject))
	{
		m_pPlayerObject->SetDead(true);
		CheckScoreUpdate();
		m_state = 2;
	}

	PipeChecks();

	m_pScoreText->SetCoords( (m_width - m_pScoreText->GetWidth())/2, 75);
}

void 
Game::ScoreProcess(float deltaTime)
{
	//Do nothing
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	backBuffer.DrawSprite(*m_pBackgroundSprite);
	
	m_pPlatform->Draw(backBuffer);
	
	for (auto& pipe : m_pPipeEntities->GetVector())
	{
		pipe->Draw(backBuffer);
	}

	m_pPlayerObject->Draw(backBuffer);
	switch (m_state)
	{
	case 0: //Idle
		m_pStartText->Draw(backBuffer);
		break;
	case 1: //Game
		m_pScoreText->Draw(backBuffer);
		break;
	case 2: //Score display
		m_pBoard->Draw(backBuffer);
		m_pScoreText->Draw(backBuffer);
		m_pHighscoreText->Draw(backBuffer);
		m_pRestartText->Draw(backBuffer);
		break;
	}
	
	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::SpaceBar()
{
	switch (m_state)
	{
	case 0: //Idle
		m_pPlayerObject->SetHorizontalVelocity(0);
		m_state = 1; //Switch state
		m_countdown = true;
		break;
	case 1: //Game
		m_pPlayerObject->Flutter();
		break;
	case 2: //Score display
		break;
	}

}

void
Game::RKey()
{
	switch (m_state)
	{
	case 0: //Idle
		break;
	case 1: //Game
		break;
	case 2: //Score display
		Restart();
		break;
	}
}

void
Game::PipeChecks()
{
	int p = m_pPlayerObject->GetPositionX() - 50;
	for (auto& pipes : m_pPipeEntities->GetVector())
	{
		if (pipes->GetPositionX() <= p && !pipes->HasBeenScored())
		{
 			pipes->BeenScored(true);
			m_pPlayerObject->Score();
			Sprite* temp = m_pBackBuffer->CreateMessage(std::to_string(m_pPlayerObject->GetScore()), 50);
			temp->SetCoords((m_width - m_pScoreText->GetWidth()) / 2, 125);
			delete m_pScoreText;
			m_pScoreText = temp;
			
		}
		if (pipes->GetPositionX() <= (p - 50) && m_pPipeEntities->HasPipeWaiting())
		{
			m_pPipeEntities->ActivateNextPipe();
		}
	}
}

void
Game::StartPipes()
{
	Pipes* p = m_pPipeEntities->GetVector().front();
	p->SetDead(false);
}

void 
Game::RestartPipes(Pipes* p)
{
	int x = m_width + p->GetWidth() / 2;
	int range = m_height - (m_pipeGapSize * 2);
	int y = rand() % range + m_pipeGapSize; //(m_pipeGapSize) to (m_height - m_pipeGapSize)

	m_pPipeEntities->ResetPipe(p, x, y);
}

void 
Game::Restart()
{
	int w = (m_width - m_pPlayerObject->GetWidth()) / 2;
	int h = ((m_height - m_pPlatform->GetHeight()) - m_pPlayerObject->GetHeight()) / 2;
	m_pPlayerObject->SetPosition(w, h);
	m_pPlayerObject->SetHorizontalVelocity(20);
	m_pPlayerObject->SetAngle(0);
	m_pPlayerObject->SetDead(false);
	m_pPlayerObject->SetScore(0);
	delete m_pScoreText;
	m_pScoreText = m_pBackBuffer->CreateMessage("0", 50);

	for (int i = 0; i < m_pPipeEntities->GetVector().size(); i++)
	{
		Pipes* p = m_pPipeEntities->GetVector().at(i);
		if (i == 0)
		{
			m_pPipeEntities->ResetPipe(p, m_width + p->GetWidth() / 2, w);
		}
		else
		{
			RestartPipes(p);
		}
	}

	m_state = 0;
}