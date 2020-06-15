#pragma once

#include "Engine/GameObject.h"

class Goal : public GameObject
{
public:
	Goal(const GameObjectProperties& properties);
	~Goal();
public:
	void Update(const float dt);
	void Render();
private:
	bool m_gotten;
	sf::Vector2i m_position;
};

