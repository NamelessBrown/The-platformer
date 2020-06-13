#include "Timer.h"

Timer* Timer::s_instance = nullptr;

Timer* Timer::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Timer();
	}

	return s_instance;
}

void Timer::Quit()
{
	delete s_instance;
}

Timer::Timer()
{
	m_lastTime = 0.f;
	m_deltaTime = 0.f;
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

const float Timer::GetDeltaTime() const
{
	return m_deltaTime;
}



