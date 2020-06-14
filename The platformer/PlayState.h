#pragma once

#include <vector>
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
	friend class Player;
	int m_currentMap = 0;
	std::vector<Map*> m_maps;
	Player* m_player = nullptr;
};

