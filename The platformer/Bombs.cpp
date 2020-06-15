#include "Bombs.h"
#include "Engine/CollisionHandler.h"
#include <random>
#include <iostream>

Bombs::Bombs(const GameObjectProperties& properties)
	:GameObject(properties), m_damage(0), m_lastSafePosition(0, 0)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> damageDistribution(0, 75);
	m_damage = damageDistribution(rng);
	m_animation.SetProperties("bomb", 6, 0, 0);
	m_body.SetGravity(2);
	m_collider.SetColliderBox(sf::IntRect(m_properties.m_position.x, m_properties.m_position.y, properties.m_width, properties.m_height));
	m_defaultPosition = m_position;
}

Bombs::~Bombs()
{
}

void Bombs::Update(const float dt)
{
	Movement(dt);
	if (m_position.y == m_lastSafePosition.y)
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_int_distribution<int> locationDistributionX(32, 1000);
		std::uniform_int_distribution<int> locationDistributionY(0, 100);
		m_position = sf::Vector2i(locationDistributionX(rng), locationDistributionY(rng));
	}
}

void Bombs::Render()
{
	m_animation.Draw(m_position.x, m_position.y + m_properties.m_height, m_properties.m_width, m_properties.m_height);
}

bool Bombs::IsAlive() const
{
	return m_alive;
}

const int Bombs::GetDamage() const
{
	return m_damage;
}

void Bombs::Boom()
{
	m_properties.m_width = 143;
	m_properties.m_height = 141;
	m_animation.SetProperties("dead", 1, 5, 100);
	m_alive = false;
}

void Bombs::Movement(const float dt)
{
	m_body.ResetForce();

	m_body.ApplyForceY(2);

	//y position
	m_body.Update(dt);
	m_lastSafePosition.y = m_position.y;
	m_position.y += m_body.GetPosition().y;
	m_collider.SetColliderBox(sf::IntRect(m_position.x, m_position.y, m_properties.m_width, m_properties.m_height));

	if (CollisionHandler::GetInstance()->MapCollision(m_collider.GetColliderBox()))
	{
		m_position.y = m_lastSafePosition.y;
	}

	//x position
	m_body.Update(dt);
	m_lastSafePosition.x = m_position.x;
	m_position.x += m_body.GetPosition().x;
	m_collider.SetColliderBox(sf::IntRect(m_position.x, m_position.y, m_properties.m_width, m_properties.m_height));

	if (CollisionHandler::GetInstance()->MapCollision(m_collider.GetColliderBox()))
	{
		m_position.x = m_lastSafePosition.x;
	}


}
