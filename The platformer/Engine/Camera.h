#pragma once

#include "Point.h"
#include <SFML/Graphics.hpp>

class Camera
{
public:
	static Camera* GetInstance();
	~Camera();
public:
	const sf::Vector2f& GetPosition() const;
	const sf::IntRect& GetViewBox() const;
	void SetTarget(const Point& target);
	void Update(const float dt);
	void Quit();
private:
	Camera();
private:
	static Camera* s_instance;
	sf::Vector2f m_position;
	Point m_target;
	sf::IntRect m_viewBox;
};

