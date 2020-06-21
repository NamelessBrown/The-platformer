#pragma once

#include <stack>
#include "GameState.h"

class GameStateManager
{
public:
	GameStateManager();
	GameStateManager(const GameStateManager&) = delete;
	GameStateManager& operator=(const GameStateManager&) = delete;
	~GameStateManager();
public:
	static void PushState(GameState* state);
	static void PopState();
	static void ChangeState(GameState* state);

	static GameState* CurrentState();
private:
	static std::stack<GameState*> m_states;
};

