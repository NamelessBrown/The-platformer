#pragma once

#include <SFML/Graphics.hpp>

constexpr int MASS = 1;
constexpr int GRAVITY = 9;

class RigidBody
{
public:
	RigidBody()
		:m_accelaration(0, 0), m_force(0, 0), m_friction(0, 0), m_velocity(0, 0), m_position(0, 0)
	{
		m_mass = MASS;
		m_gravity = GRAVITY;
	}

	virtual ~RigidBody()
	{
	}

	void SetMass(const int mass) { m_mass = mass; }
	void SetGravity(const int gravity) { m_gravity = gravity; }

	//force functions
	void ApplyForce(const sf::Vector2i& force) { m_force = force; }
	void ApplyForceX(const int forceX) { m_force.x = forceX; }
	void ApplyForceY(const int forceY) { m_force.y = forceY; }
	//reset the force to zero
	void ResetForce() { m_force = sf::Vector2i(0, 0); }

	//friction functions
	void ApplyFriction(const sf::Vector2i& friction) { m_friction = friction; }
	//reset the friction to zero
	void ResetFriction() { m_friction = sf::Vector2i(0, 0); }

	void Update(const float dt)
	{
		m_accelaration.x = (m_force.x + m_friction.x) / m_mass;
		m_accelaration.y = (m_gravity + m_force.y) / m_mass;
		m_velocity = m_accelaration * (int)dt;
		m_position = m_velocity * (int)dt;
	}

	//getters
	const int GetMass() const { return m_mass; }
	const sf::Vector2i GetPosition() const { return m_position; }
	const sf::Vector2i GetVelocity() const { return m_velocity; }
	const sf::Vector2i GetAccelaration() const { return m_accelaration; }

private:
	int m_mass;
	int m_gravity;

	sf::Vector2i m_force;
	sf::Vector2i m_friction;
	sf::Vector2i m_position;
	sf::Vector2i m_velocity;
	sf::Vector2i m_accelaration;
};

