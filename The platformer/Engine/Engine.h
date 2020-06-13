#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Engine
{
public:
	static Engine* GetInstance();
	sf::RenderWindow& GetWindow();
public:
	~Engine();
	/* Returns true if the window is made */
	bool Init(unsigned width, unsigned height, const std::string& title, bool fullscreen, unsigned framerate = 60);
	/* Deletes the instance and calls the Destructor */
	void Quit();
	const unsigned& GetWindowWidth() const;
	const unsigned& GetWindowHeight() const;
	void Run();
private:
	Engine();
	void HandleEvents();
	void Update();
	void Render();
private:
	static Engine* s_instance;
	sf::RenderWindow m_window;

	unsigned m_windowWidth;
	unsigned m_windowHeight;
	float m_deltaTime;
};

