#pragma once

#include "Engine/GameState.h"
#include "Engine/Button.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();
public:
	virtual void HandleInput();
	virtual void Update(const float dt);
	virtual void Render();
private:
	Button test;
};

