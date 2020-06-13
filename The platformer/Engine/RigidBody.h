#pragma once

#include <SFML/Graphics.hpp>

constexpr float MASS = 1.0f;
constexpr float GRAVITY = 9.8f;

class RigidBody
{
public:
	RigidBody()
		:m_accelaration(0.f, 0.f), m_force(0.f, 0.f), m_friction(0.f, 0.f), m_velocity(0.f, 0.f), m_position(0.f, 0.f)
	{
		m_mass = MASS;
		m_gravity = GRAVITY;
	}

	virtual ~RigidBody()
	{
	}

	void SetMass(const float mass) { m_mass = mass; }
	void SetGravity(const float gravity) { m_gravity = gravity; }

	//force functions
	void ApplyForce(const sf::Vector2f& force) { m_force = force; }
	void ApplyForceX(const float forceX) { m_force.x = forceX; }
	void ApplyForceY(const float forceY) { m_force.y = forceY; }
	//reset the force to zero
	void ResetForce() { m_force = sf::Vector2f(0.f, 0.f); }

	//friction functions
	void ApplyFriction(const sf::Vector2f& friction) { m_friction = friction; }
	//reset the friction to zero
	void ResetFriction() { m_friction = sf::Vector2f(0.f, 0.f); }

	void Update(const float dt)
	{
		m_accelaration.x = (m_force.x + m_friction.x) / m_mass;
		m_accelaration.y = (m_gravity + m_force.y) / m_mass;
		m_velocity = m_accelaration * dt;
		m_position = m_velocity * dt;
	}

	//getters
	const float GetMass() const { return m_mass; }
	const sf::Vector2f GetPosition() const { return m_position; }
	const sf::Vector2f GetVelocity() const { return m_velocity; }
	const sf::Vector2f GetAccelaration() const { return m_accelaration; }

private:
	float m_mass;
	float m_gravity;

	sf::Vector2f m_force;
	sf::Vector2f m_friction;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_accelaration;
};

