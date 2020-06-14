#include "Sound.h"

Sound* Sound::s_instance = nullptr;
Music* Music::s_instance = nullptr;

Sound* Sound::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Sound();
	}

	return s_instance;
}

Sound::Sound()
{

}

Sound::~Sound()
{
}

void Sound::Quit()
{
	delete s_instance;
}

bool Sound::LoadSoundBuffer(const std::string& soundID, const std::string& filename)
{
	m_soundsbuffers[soundID] = sf::SoundBuffer();
	m_sounds[soundID] = sf::Sound();

	if (!m_soundsbuffers[soundID].loadFromFile(filename))
	{
		return false;
	}

	return true;
}

void Sound::Play(const std::string& soundID)
{
	m_sounds[soundID].setBuffer(m_soundsbuffers[soundID]);
	m_sounds[soundID].play();
}

void Sound::Stop(const std::string& soundID)
{
	m_sounds[soundID].stop();
}

void Sound::RemoveSound(const std::string& soundID)
{
	m_sounds.erase(soundID);
	m_soundsbuffers.erase(soundID);
}

Music* Music::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Music();
	}

	return s_instance;
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
	m_music.erase(musicID);
}
