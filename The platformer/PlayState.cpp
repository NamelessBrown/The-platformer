#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"
#include "Engine/TextureManager.h"
#include "Engine/Camera.h"
#include "Engine/InputHandler.h"
#include "Engine/Music.h"
#include <random>

PlayState::PlayState()
{
	m_maps.emplace_back(new Map());
	Music::GetInstance()->LoadMusic("fath", "Sounds/Faith by Richard Burnish.ogg");
	Music::GetInstance()->Play("fath");
	Music::GetInstance()->GetMusic("fath").setLoop(true);

	TextureManager::GetInstance()->LoadFont("font", "Font/times.ttf");
	MapParser::GetInstance()->Load("level1", "Levels/level1.tmx");
	m_maps[m_currentMap] = MapParser::GetInstance()->GetMap("level1");
	CollisionHandler::GetInstance()->Init(m_maps[m_currentMap]);

	TextureManager::GetInstance()->LoadTexture("player", "Textures/player.png");
	TextureManager::GetInstance()->LoadTexture("bomb", "Textures/sheet1.png");
	TextureManager::GetInstance()->LoadTexture("dead", "Textures/dead.jpg");
	SpawnBombs(50);
	m_player = new Player(GameObjectProperties("player", {32, 0}, 46, 50));
	TextureManager::GetInstance()->GetSprite("bomb").setScale(TextureManager::GetInstance()->GetSprite("bomb").getScale() / 2.f);

	Camera::GetInstance()->SetTarget(m_player->GetOrigin());
}

PlayState::~PlayState()
{
	delete m_player;
	
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

	for (unsigned i = 0; i < m_bombs.size(); i++)
	{
		m_bombs[i]->Update(dt);

		if (CollisionHandler::GetInstance()->CheckCollision(m_player->GetCollider().GetColliderBox(), m_bombs[i]->GetCollider().GetColliderBox()))
		{
			m_bombs[i]->Boom();
			m_player->SetHealth(m_bombs[i]->GetDamage());
		}

	}


}

void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	TextureManager::GetInstance()->DrawText("font", "Press C to go to the next level!", 50, 50, 50);
	m_maps[m_currentMap]->Render();
	m_player->Render();

	for (unsigned i = 0; i < m_bombs.size(); i++)
	{
		if (m_bombs[i]->IsAlive())
		{
			m_bombs[i]->Render();
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
	std::uniform_int_distribution<int> distributionXPosition(startingPosition, 60 * 32);

	for (unsigned i = 0; i < amount; i++)
	{
		m_bombs.emplace_back(new Bombs(GameObjectProperties("bomb", {distributionXPosition(rng), 0}, 32, 32)));
	}
}
