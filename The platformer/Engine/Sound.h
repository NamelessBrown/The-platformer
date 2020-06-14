#pragma once

#include <map>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>

/*
	Class used for short Sound files. Ex: gunshots, hitmarkers, jumping, breathing. This isn't used for big music files! Use the music class for that!
*/
class Sound
{
public:
	static Sound* GetInstance();
	~Sound();
	void Quit();
public:
	bool LoadSoundBuffer(const std::string& soundID, const std::string& filename);
	void Play(const std::string& soundID);
	void Stop(const std::string& soundID);
	void RemoveSound(const std::string& soundID);
private:
	Sound();
	static Sound* s_instance;
	std::map<std::string, sf::SoundBuffer> m_soundsbuffers;
	std::map<std::string, sf::Sound> m_sounds;
};

/* Music class used for big boy files! */
class Music
{
public:
	static Music* GetInstance();
	~Music();
	void Quit();
public:
	bool LoadMusic(const std::string& musicID, const std::string& filename);
	void Play(const std::string& musicID);
	void Stop(const std::string& musicID);
	void RemoveSound(const std::string& musicID);
private:
	Music();
	static Music* s_instance;
	std::map<std::string, sf::Music> m_music;
};