#pragma once

#include "Engine/GameState.h"
#include "Engine/Map.h"
#include "Player.h"

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();
public:
	virtual void HandleInput();
	virtual void Update(const float dt);
	virtual void Render();
private:
	Map* m_gameMap = nullptr;
	Player* m_player = nullptr;
};

