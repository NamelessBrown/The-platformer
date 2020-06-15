#pragma once

#include "Engine/GameObject.h"
#include "Engine/Animation.h"
#include "Engine/RigidBody.h"

class Player : public GameObject
{
public:
	Player(const GameObjectProperties& properties);
	~Player();
public:
	void Update(const float dt);
	void Render();
private:
	void Movement(const float dt);
private:
	bool m_jumping = false;
	Animation m_animation;
	RigidBody m_body;
	sf::Vector2i m_lastSafePosition;
	Flip m_flip;
};

