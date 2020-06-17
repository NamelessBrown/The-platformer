#include "MainMenuState.h"
#include "Engine/TextureManager.h"
#include "Engine/Engine.h"
#include "Engine/Music.h"
#include "Engine/GameStateManager.h"
#include "PlayState.h"

MainMenuState::MainMenuState()
{
	Music::GetInstance()->Play("dont");
	Music::GetInstance()->GetMusic("dont").setLoop(true);
	m_playButton = Button("start", "Textures/start.png");
	m_quitButton = Button("quit", "Textures/quit.png");
	m_playButton.ScaleSprite(6.f);
	m_quitButton.ScaleSprite(2.f);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::HandleInput()
{
	if (m_quitButton.IsClicked(sf::Mouse::getPosition(Engine::GetInstance()->GetWindow())))
	{
		Engine::GetInstance()->GetWindow().close();
	}

	if (m_playButton.IsClicked(sf::Mouse::getPosition(Engine::GetInstance()->GetWindow())))
	{
		GameStateManager::GetInstance()->ChangeState(new PlayState());
		Music::GetInstance()->RemoveSound("dont");
	}

}

void MainMenuState::Update(const float dt)
{
}

void MainMenuState::Render()
{
	TextureManager::GetInstance()->DrawFrame("mainMenuBackground", 0, 0, (int)Engine::GetInstance()->GetWindowWidth(), (int)Engine::GetInstance()->GetWindowHeight(), 0, 0);
	m_playButton.Draw(50, 50);
	m_quitButton.Draw(50, 250);
}
