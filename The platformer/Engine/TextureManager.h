#pragma once

#include <string>
#include <map>
#include "SFML/Graphics.hpp"

enum class Flip
{
	left = 0, right, none
};

class TextureManager
{
public:
	/* GetInstance method is used for getting access within the TextureManager functions */
	static TextureManager* GetInstance();
	~TextureManager();
public:
	bool LoadFont(const std::string& id, const std::string& filename);
	bool LoadTexture(const std::string& id, const std::string& filename);
	void Remove(const std::string& id);
	/* Draw function--Draws the whole sprite */
	void Draw(std::string id, int x, int y);
	void DrawText(const std::string& fontID, const std::string& text, int fontSize, int x, int y);
	/* Draw Frame function--Used for animations */
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, Flip flip = Flip::none);
	void DrawTile(std::string id, int tileSize, int x, int y, int row, int frame);
	/* Quits out The TextureManagr instance calling its destructor */
	void Quit();
	const sf::Sprite& GetSprite(const std::string& id) const;
	const sf::Font& GetFont(const std::string& id) const;
private:
	TextureManager();
private:
	static TextureManager* s_instance;
	std::map<std::string, sf::Texture> m_textureMap;
	std::map<std::string, sf::Sprite> m_spriteMap;
	std::map<std::string, sf::Font> m_fontMap;
};

