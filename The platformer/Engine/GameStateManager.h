#pragma once

#include <stack>
#include "GameState.h"

class GameStateManager
{
public:
	static GameStateManager* GetInstance();
	~GameStateManager();
	void Quit();
	void PushState(GameState* state);
	void PopState();
	void ChangeState(GameState* state);

	GameState* CurrentState();
private:
	GameStateManager();
	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator=(const GameStateManager&) = delete;
private:
	static GameStateManager* s_instance;
	std::stack<GameState*> m_states;
};

