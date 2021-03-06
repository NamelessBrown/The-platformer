#pragma once

#include "Engine/GameObject.h"
#include "Engine/Animation.h"
#include "Engine/RigidBody.h"

class Player : public GameObject
{
public:
	Player(const GameObjectProperties& properties);
	Player(const Player& player);
	Player& operator=(const Player& player);
	~Player();
public:
	const int GetHealth() const;
	void SetHealth(const int health);
	void Update(const float dt);
	void Render();
private:
	void Movement(const float dt);
private:
	int m_health = 100;
	Animation m_animation;
	RigidBody m_body;
	sf::Vector2i m_lastSafePosition;
	Flip m_flip;
};

