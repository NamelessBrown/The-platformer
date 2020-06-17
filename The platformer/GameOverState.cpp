#include "GameOverState.h"
#include "Engine/TextureManager.h"
#include "Engine/InputHandler.h"
#include "Engine/GameStateManager.h"
#include "Engine/Camera.h"
#include "Engine/Music.h"
#include "MainMenuState.h"

GameOverState::GameOverState()
{
	Camera::GetInstance()->SetTarget(Point());
	Music::GetInstance()->GetMusic("best").setLoop(true);
	Music::GetInstance()->GetMusic("best").play();
}

GameOverState::~GameOverState()
{
	TextureManager::GetInstance()->GetSprite("bomb").setScale(TextureManager::GetInstance()->GetSprite("bomb").getScale() * 2.f);
	TextureManager::GetInstance()->GetSprite("DDD").setScale(TextureManager::GetInstance()->GetSprite("DDD").getScale() * 4.f);
	TextureManager::GetInstance()->GetSprite("start").setScale(TextureManager::GetInstance()->GetSprite("start").getScale() * 6.f);
	TextureManager::GetInstance()->GetSprite("quit").setScale(TextureManager::GetInstance()->GetSprite("quit").getScale() * 2.f);
	Music::GetInstance()->RemoveSound("best");
}

void GameOverState::HandleInput()
{
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::Space))
	{
		GameStateManager::GetInstance()->ChangeState(new MainMenuState());
	}
}

void GameOverState::Update(const float dt)
{
	Camera::GetInstance()->Update(dt);
}

void GameOverState::Render()
{
	TextureManager::GetInstance()->Draw("mainMenuBackground", 0, 0);
	TextureManager::GetInstance()->DrawText("font", "Dead press [space] to play again.", 30, 250, 250);
}
