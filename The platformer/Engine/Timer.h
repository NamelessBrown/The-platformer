#pragma once

#include <SFML/System/Clock.hpp>

class Timer
{
public:
	static Timer* GetInstance();
	void Quit();
	~Timer();
public:
	void Tick();
	const float GetDeltaTime() const;
private:
	Timer();
private:
	static constexpr float m_targetFPS = 60.F;
	static constexpr float m_targetDeltaTime = 2.5F;
	static Timer* s_instance;
	float m_deltaTime;
	float m_lastTime;
	sf::Clock m_clock;
};

