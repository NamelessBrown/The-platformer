#pragma once

#include "Engine/GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState();
	~MainMenuState();
public:
	virtual void HandleInput();
	virtual void Update(sf::RenderWindow& window, const float dt);
	virtual void Render();
private:

};

