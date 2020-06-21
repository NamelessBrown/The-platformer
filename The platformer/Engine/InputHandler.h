#pragma once

#include <SFML/Graphics.hpp>
#include <map>

/*
	TODO: Add mouse support
*/

class InputHandler
{
public:
	static InputHandler* GetInstance();
public:
	/* Currently handles all events */
	void EventHandler(sf::RenderWindow& window);
	/* Returns true is a key was pressed */
	bool GetKeyDown(sf::Keyboard::Key key);
	/* Deletes the instance and calls the Destructor */
	void Quit();
	/* Set the key to end the program the defualt key is escape */
	void SetEscapeSequence(sf::Keyboard::Key key);
	~InputHandler();
private:
	InputHandler();
	void KeyDown(sf::Keyboard::Key key);
	void KeyUp(sf::Keyboard::Key key);
private:
	std::map<sf::Keyboard::Key, bool> m_keyStates;
	static InputHandler* s_instance;
	sf::Event m_event = sf::Event();
	sf::Keyboard::Key m_leaveKey = sf::Keyboard::Key::Escape;
};

