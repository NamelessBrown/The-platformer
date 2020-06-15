#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Collider.h"

struct GameObjectProperties
{
public:
	GameObjectProperties(const std::string& textureId, const sf::Vector2i& position, const int& width, const int& height)
	{
		m_textureId = textureId;
		m_position.x = position.x;
		m_position.y = position.y;
		m_width = width;
		m_height = height;
	}
public:
	std::string m_textureId;
	int m_width;
	int m_height;
	sf::Vector2i m_position;
};

class GameObject
{
public:
	GameObject(const GameObjectProperties& properties)
		:m_properties(properties)
	{
		m_textureId = properties.m_textureId;
		m_width = properties.m_width;
		m_height = properties.m_height;

		m_position = sf::Vector2i(properties.m_position.x, properties.m_position.y);
		float pointX = properties.m_position.x + (float)properties.m_width / 2.f;
		float pointY = properties.m_position.x + (float)properties.m_height / 2.f;
		m_origin = Point(pointX, pointY);
		m_collider = Collider();
	}

	virtual ~GameObject()
	{

	}

	const Point& GetOrigin() const
	{
		return m_origin;
	}

	const Collider& GetCollider() const
	{
		return m_collider;
	}

	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
protected:
	sf::Vector2i m_position;
	Point m_origin;
	Collider m_collider;
	GameObjectProperties m_properties;
private:
	int m_width;
	int m_height;
	std::string m_textureId;
};

