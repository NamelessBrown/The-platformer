#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"
#include "Engine/TextureManager.h"
#include "Engine/Camera.h"
#include "Engine/InputHandler.h"
#include "Engine/Music.h"

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
	m_player = new Player(GameObjectProperties("player", {32, 0}, 46, 50));
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
}

void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	TextureManager::GetInstance()->DrawText("font", "Press C to go to the next level!", 50, 50, 50);
	m_maps[m_currentMap]->Render();
	m_player->Render();
}