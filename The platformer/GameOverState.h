#pragma once

#include "Engine/GameState.h"

class GameOverState : public GameState
{
public:
	GameOverState();
	~GameOverState();
public:
	virtual void HandleInput();
	virtual void Update(const float dt);
	virtual void Render();
private:
};

