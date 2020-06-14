#include "MainMenuState.h"
#include "Engine/TextureManager.h"
#include "Engine/Engine.h"
#include "Engine/Sound.h"
#include <iostream>

MainMenuState::MainMenuState()
{
	Sound::GetInstance()->LoadSoundBuffer("brick", "Sounds/brick.wav");
	TextureManager::GetInstance()->LoadTexture("mainMenuBackground", "Textures/background.jpg");
	m_playButton = Button("start", "Textures/start.png");
	m_quitButton = Button("quit", "Textures/quit.png");

	m_playButton.SetFont("font", "Font/Nervous.ttf");
	m_quitButton.SetFont("font", "Font/Nervous.ttf");
	m_playButton.ScaleSprite(6.f);
	m_quitButton.ScaleSprite(2.f);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::HandleInput()
{
}

void MainMenuState::Update(const float dt)
{
	if (m_playButton.IsClicked(sf::Mouse::getPosition(Engine::GetInstance()->GetWindow())))
	{
		Sound::GetInstance()->Play("brick");
	}
}

void MainMenuState::Render()
{
	TextureManager::GetInstance()->DrawFrame("mainMenuBackground", 0, 0, (int)Engine::GetInstance()->GetWindowWidth(), (int)Engine::GetInstance()->GetWindowHeight(), 0, 0);
	m_playButton.Draw(50, 50);
	m_quitButton.Draw(50, 250);
}
