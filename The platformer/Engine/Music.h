#pragma once

#include <string>
#include <map>
#include <SFML/Audio.hpp>
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
	sf::Music& GetMusic(const std::string& musicID);
private:
	Music();
	static Music* s_instance;
	std::map<std::string, sf::Music> m_music;
};
