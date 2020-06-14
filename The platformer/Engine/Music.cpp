#include "Music.h"

Music* Music::s_instance = nullptr;

Music* Music::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Music();
	}

	return s_instance;
}

Music::Music()
{

}

Music::~Music()
{
}

void Music::Quit()
{
	delete s_instance;
}

bool Music::LoadMusic(const std::string& musicID, const std::string& filename)
{
	if (!m_music[musicID].openFromFile(filename))
	{
		return false;
	}

	return true;
}

void Music::Play(const std::string& musicID)
{
	m_music[musicID].play();
}

void Music::Stop(const std::string& musicID)
{
	m_music[musicID].stop();
}

void Music::RemoveSound(const std::string& musicID)
{
	if (m_music[musicID].getStatus() == sf::Music::Status::Playing)
	{
		m_music[musicID].stop();
	}

	m_music.erase(musicID);
}