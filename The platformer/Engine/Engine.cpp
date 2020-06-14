#include "Engine.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "MapParser.h"
#include "Camera.h"
#include "Timer.h"
#include "Sound.h"
#include "GameStateManager.h"
#include "../MainMenuState.h"

Engine* Engine::s_instance = nullptr;

Engine* Engine::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Engine();
	}

	return s_instance;
}

sf::RenderWindow& Engine::GetWindow()
{
	return m_window;
}

bool Engine::Init(unsigned width, unsigned height, const std::string& title, bool fullscreen, unsigned framerate)
{
	if (fullscreen)
	{
		m_window.create(sf::VideoMode::getFullscreenModes().front(), title, sf::Style::None);
	}
	else
	{
		m_window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	}

	m_window.setFramerateLimit(framerate);
	m_windowWidth = m_window.getSize().x;
	m_windowHeight = m_window.getSize().y;

	GameStateManager::GetInstance()->PushState(new MainMenuState());

	if (!m_window.isOpen())
	{
		return false;
	}

	return true;
}


Engine::Engine()
{
	m_deltaTime = 60.f;
	m_windowWidth = 0;
	m_windowHeight = 0;
}

void Engine::Run()
{
	while (m_window.isOpen())
	{
		HandleEvents();
		Update();
		Render();
		Timer::GetInstance()->Tick();
	}
}

void Engine::HandleEvents()
{
	InputHandler::GetInstance()->EventHandler(m_window);
	GameStateManager::GetInstance()->CurrentState()->HandleInput();
}

void Engine::Update()
{
	const float dt = Timer::GetInstance()->GetDeltaTime();
	GameStateManager::GetInstance()->CurrentState()->Update(dt);
}

void Engine::Render()
{
	m_window.clear();
	GameStateManager::GetInstance()->CurrentState()->Render();
	m_window.display();
}

void Engine::Quit()
{
	Music::GetInstance()->Quit();
	Sound::GetInstance()->Quit();
	GameStateManager::GetInstance()->Quit();
	Timer::GetInstance()->Quit();
	MapParser::GetInstance()->Quit();
	Camera::GetInstance()->Quit();
	InputHandler::GetInstance()->Quit();
	TextureManager::GetInstance()->Quit();
	delete s_instance;
}

const unsigned& Engine::GetWindowWidth() const
{
	return m_windowWidth;
}

const unsigned& Engine::GetWindowHeight() const
{
	return m_windowHeight;
}

Engine::~Engine()
{

}