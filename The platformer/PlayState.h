#pragma once

#include <vector>
#include "Engine/GameState.h"
#include "Engine/Map.h"
#include "Player.h"
#include "Bombs.h"
#include "Goal.h"

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
	void LoadNewLevel();
	void BombCollision(const float dt);
	void SpawnBombs(const unsigned amount, int startingPosition = 250);
private:
	std::string m_level;
	std::string m_levelPath;
	int m_currentLevel = 1;
	std::vector<Map*> m_maps;
	std::vector<Bombs> m_bombs;
	Player m_player;
	Goal m_goal;
};

