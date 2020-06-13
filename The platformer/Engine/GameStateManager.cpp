#include "GameStateManager.h"
#include <iostream>

GameStateManager* GameStateManager::s_instance = nullptr;

GameStateManager::GameStateManager()
{
}

GameStateManager* GameStateManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new GameStateManager();
	}

	return s_instance;
}

GameStateManager::~GameStateManager()
{
	while (!m_states.empty())
	{
		PopState();
		std::cout << "Pop state!\n";
	}
}

void GameStateManager::Quit()
{
	delete s_instance;
}

void GameStateManager::PushState(GameState* state)
{
	m_states.push(state);
}

void GameStateManager::PopState()
{
	delete m_states.top();
	m_states.pop();
}

void GameStateManager::ChangeState(GameState* state)
{
	if (!m_states.empty())
	{
		PopState();
	}

	PushState(state);
}

GameState* GameStateManager::CurrentState()
{
	if(m_states.empty())
	{
		return nullptr;
	}

	return m_states.top();
}
