#include "Timer.h"

float Timer::m_deltaTime = 0.f;
float Timer::m_lastTime = 0.f;
sf::Clock Timer::m_clock = sf::Clock();

Timer::Timer()
{

}

Timer::~Timer()
{

}

void Timer::Tick()
{
	m_deltaTime = m_clock.restart().asSeconds() * m_targetFPS;

	if (m_deltaTime > m_targetDeltaTime)
	{
		m_deltaTime = m_targetDeltaTime;
	}

}

const float Timer::GetDeltaTime()
{
	return m_deltaTime;
}



