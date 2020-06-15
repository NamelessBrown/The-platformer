#pragma once

#include "Engine/Animation.h"
#include "Engine/GameObject.h"
#include "Engine/RigidBody.h"

class Bombs : public GameObject
{
public:
	Bombs(const GameObjectProperties& properties);
	~Bombs();

	void Boom();
	void Update(const float dt);
	void Render();
private:
	void Movement(const float dt);
private:
	RigidBody m_body;
	Animation m_animation;
	int m_damage;
	sf::Vector2i m_lastSafePosition;
};

