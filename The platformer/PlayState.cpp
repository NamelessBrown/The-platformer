#include "PlayState.h"
#include "Engine/CollisionHandler.h"
#include "Engine/MapParser.h"

PlayState::PlayState()
{
	MapParser::GetInstance()->Load("level1", "Levels/level1.tmx");
	m_gameMap = MapParser::GetInstance()->GetMap("level1");
}

PlayState::~PlayState()
{
}

void PlayState::HandleInput()
{
}

void PlayState::Update(const float dt)
{
	m_gameMap->Update();
}

void PlayState::Render()
{
	m_gameMap->Render();
}
