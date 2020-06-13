#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button() = default;
	Button(const Button&) = delete;
	Button operator=(const Button&) = delete;
	Button(const std::string& spriteID, const std::string& filename);
	Button(const std::string& fontID, const std::string& filename, const unsigned fontSize);
	virtual ~Button();
public:
	bool IsClicked(const std::string& spriteID);
	bool IsClicked(const sf::Vector2i& mousePosition);
	void SetFont(const std::string& fontID, const std::string fontFileName);
	void SetText(const std::string newText);
	void SetPositionFromSprite(const int position);
	void Draw(int x, int y);
private:
	std::string m_spriteID; //*this stores the current id of the current object
	sf::Text m_text;
	std::string m_fontID; //*this stores the current id of the current object

	int m_positionFromSprite;
	bool m_clicked = false;
};

