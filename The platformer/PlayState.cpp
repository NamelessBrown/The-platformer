#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"
#include "Engine/TextureManager.h"
#include "Engine/Camera.h"

PlayState::PlayState()
{
	MapParser::GetInstance()->Load("level1", "Levels/level1.tmx");
	m_gameMap = MapParser::GetInstance()->GetMap("level1");
	CollisionHandler::GetInstance()->Init(m_gameMap);
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
}

void PlayState::Update(const float dt)
{
	Camera::GetInstance()->Update(dt);
	m_player->Update(dt);
	m_gameMap->Update();
}

void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	m_player->Render();
	m_gameMap->Render();
}
