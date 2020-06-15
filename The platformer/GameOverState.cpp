#include "GameOverState.h"
#include "Engine/TextureManager.h"
#include "Engine/InputHandler.h"
#include "Engine/GameStateManager.h"
#include "Engine/Camera.h"
#include "MainMenuState.h"

GameOverState::GameOverState()
{
	Camera::GetInstance()->SetTarget(Point());
}

GameOverState::~GameOverState()
{
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
