#include "GameStateManager.h"
#include <iostream>

std::stack<GameState*> GameStateManager::m_states = std::stack<GameState*>();

GameStateManager::GameStateManager()
{
}

GameStateManager::~GameStateManager()
{
	while (!m_states.empty())
	{
		PopState();
		std::cout << "Pop state!\n";
	}
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
