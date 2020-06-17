#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"
#include "Engine/TextureManager.h"
#include "Engine/Camera.h"
#include "Engine/InputHandler.h"
#include "Engine/Music.h"
#include "Engine/GameStateManager.h"
#include "GameOverState.h"
#include <random>

PlayState::PlayState()
	:m_player(GameObjectProperties("player", { 32, 0 }, 46, 50)), m_goal(GameObjectProperties("DDD", { 250, 360 }, 405, 214))
{
	m_level = "level1";
	m_levelPath = "Levels/level1.tmx";

	m_maps.emplace_back(new Map());
	Music::GetInstance()->Play("fath");
	Music::GetInstance()->GetMusic("fath").setLoop(true);

	TextureManager::GetInstance()->LoadFont("font", "Font/times.ttf");
	MapParser::GetInstance()->Load(m_level, m_levelPath);
	m_maps[0] = MapParser::GetInstance()->GetMap(m_level);
	CollisionHandler::GetInstance()->Init(*m_maps[0]);
	SpawnBombs(5);
	TextureManager::GetInstance()->GetSprite("bomb").setScale(TextureManager::GetInstance()->GetSprite("bomb").getScale() / 2.f);
	TextureManager::GetInstance()->GetSprite("DDD").setScale(TextureManager::GetInstance()->GetSprite("DDD").getScale() / 4.f);

	Camera::GetInstance()->SetTarget(m_player.GetOrigin());
}

PlayState::~PlayState()
{

}

void PlayState::HandleInput()
{
	Camera::GetInstance()->SetTarget(m_player.GetOrigin());
}

void PlayState::Update(const float dt)
{
	Camera::GetInstance()->Update(dt);
	m_player.Update(dt);

	BombCollision(dt);

	if (CollisionHandler::GetInstance()->CheckCollision(m_player.GetCollider().GetColliderBox(), m_goal.GetCollider().GetColliderBox()))
	{
		m_maps.emplace_back(new Map());
		LoadNewLevel();
		MapParser::GetInstance()->Load(m_level, m_levelPath);
		m_maps[0] = MapParser::GetInstance()->GetMap(m_level);

		m_player = Player(GameObjectProperties("player", { 64, 0 }, 46, 50));

		const unsigned tileSize = CollisionHandler::GetInstance()->GetCollisionLayer()->GetTileSize();
		const unsigned tileCol = CollisionHandler::GetInstance()->GetCollisionLayer()->GetNumberOfColumns();

		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> distributionXPosition(0 + tileSize, (tileCol - tileSize) * tileSize);
		std::uniform_int_distribution<int> distributionYPosition(150, 250);
		m_goal = Goal(GameObjectProperties("DDD", { distributionXPosition(rng) , distributionYPosition(rng) }, 405, 214));

		SpawnBombs(5);

		CollisionHandler::GetInstance()->Init(*m_maps[0]);
	}

	if (m_player.GetHealth() < 0)
	{
		GameStateManager::GetInstance()->ChangeState(new GameOverState());
		Music::GetInstance()->RemoveSound("fath");
	}

}

void PlayState::Render()
{
	if (m_level == "level1" || m_level == "level2")
	{
		TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	}
	else if (m_level == "level3" || m_level == "leve4")
	{
		TextureManager::GetInstance()->Draw("mainMenuBackground", -100, 0);
	}
	else
	{
		TextureManager::GetInstance()->Draw("mainMenuBackground", -500, 0);
	}

	m_maps[0]->Render();
	m_player.Render();
	m_goal.Render();

	for (auto& e: m_bombs)
	{
		e.Render();
	}
}

void PlayState::LoadNewLevel()
{
	if (m_currentLevel >= 5)
	{
		m_currentLevel = 1;
		m_level = "level1";
		m_levelPath = "Levels/level1.tmx";
		return;
	}

	int newLevel = m_currentLevel + 1;
	std::string nextLevel = std::to_string(newLevel);
	std::string lastLevel = std::to_string(m_currentLevel);

	int index = 0;
	while (index > -1)
	{
		index = m_level.find(lastLevel, index);
		if (index > -1)
		{
			m_level.replace(index, nextLevel.length(), nextLevel);
		}

	}

	index = 0;
	while (index > -1)
	{
		index = m_levelPath.find(lastLevel);
		if (index > -1)
		{
			m_levelPath.replace(index, nextLevel.length(), nextLevel);
			break;
		}

	}

	m_currentLevel++;

}

void PlayState::BombCollision(const float dt)
{
	for (unsigned i = 0; i < m_bombs.size(); i++)
	{
		m_bombs[i].Update(dt);

		if (CollisionHandler::GetInstance()->CheckCollision(m_player.GetCollider().GetColliderBox(), m_bombs[i].GetCollider().GetColliderBox()))
		{
			m_player.SetHealth(m_bombs[i].GetDamage());
			m_bombs.erase(m_bombs.begin() + i);
		}

	}

}

void PlayState::SpawnBombs(const unsigned amount, int startingPosition)
{
	m_bombs.clear();

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distributionXPosition(startingPosition, 45 * 32);

	for (unsigned i = 0; i < amount; i++)
	{
		m_bombs.emplace_back(Bombs(GameObjectProperties("bomb", {distributionXPosition(rng), 0}, 32, 32)));
	}
}
