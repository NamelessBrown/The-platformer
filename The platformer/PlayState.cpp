#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"
#include "Engine/TextureManager.h"
#include "Engine/Camera.h"
#include "Engine/InputHandler.h"

PlayState::PlayState()
{
	m_maps.emplace_back(new Map());
	MapParser::GetInstance()->Load("level1", "Levels/level1.tmx");
	m_maps[m_currentMap] = MapParser::GetInstance()->GetMap("level1");
	CollisionHandler::GetInstance()->Init(m_maps[m_currentMap]);
	TextureManager::GetInstance()->LoadTexture("player", "Textures/player.png");
	m_player = new Player(GameObjectProperties("player", {32.f, 0.f}, 46, 50));
	Camera::GetInstance()->SetTarget(m_player->GetOrigin());
}

PlayState::~PlayState()
{
	delete m_player;

}

void PlayState::HandleInput()
{
	Camera::GetInstance()->SetTarget(m_player->GetOrigin());
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::C))
	{
		m_maps.emplace_back(new Map());
		MapParser::GetInstance()->Load("level2", "Levels/level2.tmx");
		m_currentMap++;
		m_maps[m_currentMap] = MapParser::GetInstance()->GetMap("level2");
		CollisionHandler::GetInstance()->Init(m_maps[m_currentMap]);
	}
}

void PlayState::Update(const float dt)
{
	Camera::GetInstance()->Update(dt);
	m_player->Update(dt);
}

void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	m_maps[m_currentMap]->Render();
	m_player->Render();
}