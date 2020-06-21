#pragma once

#include <SFML/System/Clock.hpp>

class Timer
{
public:
	Timer();
	Timer(const Timer&) = delete;
	Timer operator=(const Timer&) = delete;
	~Timer();
public:
	static void Tick();
	static const float GetDeltaTime();
private:
	static constexpr float m_targetFPS = 60.F;
	static constexpr float m_targetDeltaTime = 1.5F;
	static float m_deltaTime;
	static float m_lastTime;
	static sf::Clock m_clock;
};

