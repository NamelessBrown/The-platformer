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
{
	m_level = "level1";
	m_levelPath = "Levels/level1.tmx";

	m_maps.emplace_back(new Map());
	Music::GetInstance()->LoadMusic("fath", "Sounds/Faith by Richard Burnish.ogg");
	Music::GetInstance()->Play("fath");
	Music::GetInstance()->GetMusic("fath").setLoop(true);

	TextureManager::GetInstance()->LoadFont("font", "Font/times.ttf");
	MapParser::GetInstance()->Load(m_level, m_levelPath);
	m_maps[m_currentMap] = MapParser::GetInstance()->GetMap("level1");
	CollisionHandler::GetInstance()->Init(m_maps[m_currentMap]);

	TextureManager::GetInstance()->LoadTexture("player", "Textures/player.png");
	TextureManager::GetInstance()->LoadTexture("bomb", "Textures/sheet1.png");
	TextureManager::GetInstance()->LoadTexture("dead", "Textures/dead.jpg");
	TextureManager::GetInstance()->LoadTexture("DDD", "Textures/DDD.png");
	SpawnBombs(10);
	m_player = new Player(GameObjectProperties("player", {32, 0}, 46, 50));
	TextureManager::GetInstance()->GetSprite("bomb").setScale(TextureManager::GetInstance()->GetSprite("bomb").getScale() / 2.f);
	TextureManager::GetInstance()->GetSprite("DDD").setScale(TextureManager::GetInstance()->GetSprite("DDD").getScale() / 4.f);

	m_goal = new Goal(GameObjectProperties("DDD", { 250, 360 }, 405, 214));

	Camera::GetInstance()->SetTarget(m_player->GetOrigin());
}

PlayState::~PlayState()
{
	delete m_player;
	delete m_goal;
	
	for (auto& e : m_bombs)
	{
		delete e;
	}

}

void PlayState::HandleInput()
{
	Camera::GetInstance()->SetTarget(m_player->GetOrigin());
}

void PlayState::Update(const float dt)
{
	Camera::GetInstance()->Update(dt);
	m_player->Update(dt);

	BombCollision(dt);

	if (CollisionHandler::GetInstance()->CheckCollision(m_player->GetCollider().GetColliderBox(), m_goal->GetCollider().GetColliderBox()))
	{
		//load new level;
		std::cout << "new level! \n";
	}

	if (m_player->GetHealth() < 0)
	{
		GameStateManager::GetInstance()->ChangeState(new GameOverState());
		Music::GetInstance()->RemoveSound("fath");
	}

}

void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);

	m_maps[m_currentMap]->Render();
	m_player->Render();
	m_goal->Render();

	for (auto& e: m_bombs)
	{
		e->Render();
	}
}

void PlayState::LoadNewLevel()
{
}

void PlayState::BombCollision(const float dt)
{
	for (unsigned i = 0; i < m_bombs.size(); i++)
	{
		m_bombs[i]->Update(dt);

		if (CollisionHandler::GetInstance()->CheckCollision(m_player->GetCollider().GetColliderBox(), m_bombs[i]->GetCollider().GetColliderBox()))
		{
			m_player->SetHealth(m_bombs[i]->GetDamage());
			delete m_bombs[i];
			m_bombs.erase(m_bombs.begin() + i);
		}

	}

}

void PlayState::SpawnBombs(const unsigned amount, int startingPosition)
{
	for (auto& e : m_bombs)
	{
		delete e;
	}

	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distributionXPosition(startingPosition, 45 * 32);

	for (unsigned i = 0; i < amount; i++)
	{
		m_bombs.emplace_back(new Bombs(GameObjectProperties("bomb", {distributionXPosition(rng), 0}, 32, 32)));
	}
}
