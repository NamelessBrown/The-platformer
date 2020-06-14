#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button() = default;
	Button(const Button&);
	Button& operator=(const Button&);
	Button(const std::string& spriteID, const std::string& filename);
	Button(const std::string& fontID, const std::string& filename, const unsigned fontSize);
	virtual ~Button();
public:
	bool IsClicked(const std::string& spriteID);
	bool IsClicked(const sf::Vector2i& mousePosition);
	void ScaleSprite(const float scaleBy);
	void SetFont(const std::string& fontID, const std::string fontFileName);
	void SetText(const std::string newText);
	void SetFontSize(const unsigned size);
	void SetPositionFromSprite(const int position);
	void Draw(int x, int y);
private:
	std::string m_spriteID; //*this stores the current id of the current object
	std::string m_fontID; //*this stores the current id of the current object
	std::string m_text;

	int m_positionFromSprite = 0;
	unsigned m_fontSize = 30;
	bool m_clicked = false;
};

