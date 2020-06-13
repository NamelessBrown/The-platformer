#include "Button.h"
#include "TextureManager.h"

Button::Button(const std::string& spriteID, const std::string& filename)
{
	TextureManager::GetInstance()->LoadTexture(spriteID, filename);
	m_text.setString("Defualt");
	m_text.setCharacterSize(20);
	m_spriteID = spriteID;
	m_positionFromSprite = 0;
}

Button::Button(const std::string& fontID, const std::string& filename, const unsigned fontSize)
{
	TextureManager::GetInstance()->LoadFont(fontID, filename);
	m_text.setString("Defualt");
	m_text.setCharacterSize(fontSize);
	m_fontID = fontID;
	m_positionFromSprite = 0;
}

Button::~Button()
{
}

//Checks to see if the sprite has been clicked on. Returns bool is the mouse is clicked and the sprite is on the button!
bool Button::IsClicked(const std::string& spriteID)
{
	const sf::Mouse mouse;

	const sf::Sprite thisSprite = TextureManager::GetInstance()->GetSprite(m_spriteID);
	const sf::Sprite sprite = TextureManager::GetInstance()->GetSprite(spriteID);

	if (thisSprite.getGlobalBounds().contains(sprite.getPosition()) && mouse.isButtonPressed(sf::Mouse::Left) && !m_clicked)
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
	const sf::Sprite thisSprite = TextureManager::GetInstance()->GetSprite(m_spriteID);

	if (thisSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition)) && mouse.isButtonPressed(sf::Mouse::Left) && !m_clicked)
	{
		m_clicked = true;
	}
	else
	{
		m_clicked = false;
	}


	return m_clicked;
}

void Button::SetFont(const std::string& fontID, const std::string fontFileName)
{
	TextureManager::GetInstance()->LoadFont(fontID, fontFileName);
	sf::Font font = TextureManager::GetInstance()->GetFont(fontID);
	m_text.setFont(font);
	m_fontID = fontID;
}

void Button::SetText(const std::string newText)
{
	m_text.setString(newText);
}

void Button::SetPositionFromSprite(const int position)
{
	m_positionFromSprite = position;
}

//Draws all things that needs to be draw with the buton class
void Button::Draw(int x, int y)
{
	TextureManager::GetInstance()->Draw(m_spriteID, x, y);
	TextureManager::GetInstance()->DrawText(m_text, x + m_positionFromSprite, y);
}

