#include "MainMenuState.h"
#include "Engine/TextureManager.h"

MainMenuState::MainMenuState()
{
	TextureManager::GetInstance()->LoadTexture("donuts", "Textures/DDD.png");
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::HandleInput()
{
}

void MainMenuState::Update(sf::RenderWindow& window, const float dt)
{
}

void MainMenuState::Render()
{
	TextureManager::GetInstance()->Draw("donuts", 100, 100);
}
