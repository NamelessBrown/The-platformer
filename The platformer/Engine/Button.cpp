#include "Button.h"

Button::Button(const sf::Vector2f& position, const sf::Font& font, const sf::Texture& texture, const int textposition)
	/*
		The textpositionX is how far you want the text position in the {X,Y} direction to be from the GUI button. 
	*/
{
	m_texture = texture;
	m_font = font;
	m_text.setFont(m_font);
	m_text.setString("Defualt");
	m_text.setCharacterSize(20);

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(position);

	m_text.setPosition(m_sprite.getPosition().x + (textposition * 4), m_sprite.getPosition().y + textposition);
}

Button::~Button()
{
}

//Checks to see if the sprite has been clicked on. Returns bool is the mouse is clicked and the sprite is on the button!
bool Button::IsClicked(const sf::Sprite& sprite)
{
	const sf::Mouse mouse;

	if (m_sprite.getGlobalBounds().contains(sprite.getPosition()) && mouse.isButtonPressed(sf::Mouse::Left) && !m_clicked)
	{
		m_clicked = true;
	}
	else
	{
		m_clicked = false;
	}


	return m_clicked;
}

bool Button::IsClicked(const sf::Vector2i& mousePosition)
{
	const sf::Mouse mouse;

	if (m_sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && mouse.isButtonPressed(sf::Mouse::Left) && !m_clicked)
	{
		m_clicked = true;
	}
	else
	{
		m_clicked = false;
	}


	return m_clicked;
}

void Button::MovePosition(const sf::Vector2f& newPosition)
{
	m_sprite.setPosition(newPosition);
}

void Button::SetFont(const std::string fontFileName)
{
	m_font.loadFromFile(fontFileName);
	m_text.setFont(m_font);
}

void Button::SetText(const std::string newText)
{
	m_text.setString(newText);
}

void Button::SetTexture(sf::Texture& texture)
{
	m_sprite.setTexture(texture);
}

void Button::SetScale(float scaleBy)
{
	m_sprite.setScale(m_sprite.getScale() / scaleBy);
}

const sf::Sprite& Button::getSprite() const
{
	return m_sprite;
}

//Draws all things that needs to be draw with the buton class
void Button::Draw(sf::RenderWindow& target)
{
	target.draw(m_sprite);
	target.draw(m_text);
}

