//Local include:
#include "game.h"
#include "backbuffer.h"
#include "sprite.h"
#include "player.h"
#include "inputhandler.h"
#include "platform.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <cstdio>

// Static Members:
Game* Game::sm_pInstance = 0;

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
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
	
	//delete m_pPlayerObject;
	//m_pPlayerObject = 0;
}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pInputHandler;
	m_pInputHandler = 0;

	m_hitableEntities.clear();
}

bool 
Game::Initialise()
{
	m_width = 414;
	m_height = 736;

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
	m_pPlayerObject = new Player();
	m_pPlayerObject->Initalise(m_pBackBuffer->CreateTexture("assets\\player.png"));
	int w = (m_width - m_pPlayerObject->GetWidth()) / 2;
	int h = (m_height - m_pPlayerObject->GetHeight()) / 2;
	m_pPlayerObject->SetPosition(w, h);

	Platform* p = new Platform();
	p->Initialise(m_pBackBuffer->CreateTexture("assets\\platform.png"));
	p->SetPositionY(736 - p->GetHeight());
	m_hitableEntities.push_back(p);

	m_pStartText = m_pBackBuffer->CreateMessage("0");

	return true;
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
			Process(frame);
			m_lag -= frame;

			++m_numUpdates;
		}
		Draw(*m_pBackBuffer);
	}

	return m_looping;
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

	for (auto& entity : m_hitableEntities)
	{
		if (entity->IsCollidingWith(*m_pPlayerObject))
		{
			m_pPlayerObject->SetDead(true);
		}
		else 
		{
			entity->Process(deltaTime);
		}
	}
	m_pStartText->SetCoords( (m_width - m_pStartText->GetWidth())/2, 150);
}

void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	backBuffer.DrawSprite(*m_pBackgroundSprite);

	for (auto& entity : m_hitableEntities)
	{
		entity->Draw(backBuffer);
	}

	m_pPlayerObject->Draw(backBuffer);

	m_pStartText->Draw(backBuffer);

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void
Game::PlayerFlutter()
{
	m_pPlayerObject->Flutter();
	PlayerScores();
}

void
Game::PlayerScores()
{
	m_pPlayerObject->Score();
}