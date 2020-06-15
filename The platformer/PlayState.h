#pragma once

#include <vector>
#include "Engine/GameState.h"
#include "Engine/Map.h"
#include "Player.h"
#include "Bombs.h"

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
	void SpawnBombs(const unsigned amount);
private:
	int m_currentMap = 0;
	std::vector<Map*> m_maps;
	std::vector<Bombs*> m_bombs;
	Player* m_player = nullptr;
};

