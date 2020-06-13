#include "TextureManager.h"
#include "Engine.h"
#include "Camera.h"
#include <iostream>

TextureManager* TextureManager::s_instance = nullptr;

TextureManager::TextureManager()
{
}

TextureManager* TextureManager::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new TextureManager();
    }

    return s_instance;
}

void TextureManager::Quit()
{
    delete s_instance;
}

TextureManager::~TextureManager()
{
    for (auto it = m_spriteMap.begin(); it != m_spriteMap.end(); it++)
    {
        std::cout << "Deleted sprite ID: " << it->first << '\n';
        delete it->second;
    }

    for (auto it = m_textureMap.begin(); it != m_textureMap.end(); it++)
    {
        std::cout << "Deleted textured ID: " << it->first << '\n';
        delete it->second;
    }


    m_spriteMap.clear();
}

bool TextureManager::Load(const std::string& id, const std::string& filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);
    m_textureMap[id] = new sf::Texture(texture);
    m_textureMap[id]->loadFromFile(filename);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    m_spriteMap[id] = new sf::Sprite(sprite);
    m_spriteMap[id]->setTexture(*m_textureMap[id]);

    //m_textureMap[id].loadFromFile(filename);
    //m_spriteMap[id].setTexture(m_textureMap[id]);
    return true;
}

void TextureManager::Remove(const std::string& id)
{
    m_spriteMap.erase(id);
}

void TextureManager::Draw(std::string id, int x, int y)
{
    const sf::Vector2f camera = Camera::GetInstance()->GetPosition() * 0.5f;
    m_spriteMap[id]->setPosition({ (float)x - camera.x, (float)y - camera.y });

    Engine::GetInstance()->GetWindow().draw(*m_spriteMap[id]);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, Flip flip)
{
    const sf::Vector2f camera = Camera::GetInstance()->GetPosition();
    const sf::IntRect defaultRect = m_spriteMap[id]->getTextureRect();
    m_spriteMap[id]->setPosition({ (float)x - camera.x, (float)y - camera.y });

    sf::IntRect srcRect(width * frame, height * row, width, height);
    m_spriteMap[id]->setTextureRect(srcRect);

    if (flip == Flip::left)
    {
        if (frame == 0)
        {
            srcRect.left = width;
        }

        m_spriteMap[id]->setTextureRect(sf::IntRect(srcRect.left, srcRect.top, -srcRect.width, srcRect.height));
    }

    Engine::GetInstance()->GetWindow().draw(*m_spriteMap[id]);
    m_spriteMap[id]->setTextureRect(defaultRect);
}

void TextureManager::DrawTile(std::string id, int tileSize, int x, int y, int row, int frame)
{
    const sf::Vector2f camera = Camera::GetInstance()->GetPosition();
    sf::IntRect defaultRect = m_spriteMap[id]->getTextureRect();
    m_spriteMap[id]->setPosition({ (float)x - camera.x, (float)y - camera.y });

    sf::IntRect srcRect(tileSize * frame, tileSize * row, tileSize, tileSize);
    m_spriteMap[id]->setTextureRect(srcRect);
    Engine::GetInstance()->GetWindow().draw(*m_spriteMap[id]);
    m_spriteMap[id]->setTextureRect(defaultRect);
}