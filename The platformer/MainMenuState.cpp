#include "MainMenuState.h"
#include "Engine/TextureManager.h"
#include "Engine/Engine.h"
#include <iostream>

MainMenuState::MainMenuState()
{
	TextureManager::GetInstance()->LoadTexture("donuts", "Textures/DDD.png");
	test = Button("bomb", "Textures/bomb.png");
	test.SetPositionFromSprite(50);
	test.SetFont("font", "Font/Nervous.ttf");
	test.SetText("This is a test");
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::HandleInput()
{
}

void MainMenuState::Update(const float dt)
{
	if (test.IsClicked(sf::Mouse::getPosition(Engine::GetInstance()->GetWindow())))
	{
		std::cout << "boobs clicked " << '\n';
	}
}

void MainMenuState::Render()
{
	TextureManager::GetInstance()->Draw("donuts", 100, 100);
	test.Draw(350, 350);
}
