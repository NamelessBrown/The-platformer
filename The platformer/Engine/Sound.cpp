#include "Sound.h"

Sound* Sound::s_instance = nullptr;

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
