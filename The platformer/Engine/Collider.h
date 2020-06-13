#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
	Collider() = default;
	~Collider();
	void SetColliderBox(const sf::IntRect& box);
	const sf::IntRect GetColliderBox() const;
private:
	sf::IntRect m_box;
};

