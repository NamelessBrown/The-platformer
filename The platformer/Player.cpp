#include "Player.h"
#include "Engine/CollisionHandler.h"
#include "Engine/InputHandler.h"

Player::Player(const GameObjectProperties& properties)
	:GameObject(properties)
{
	m_animation.SetProperties(properties.m_textureId, 0, 1, 0);
	m_collider.SetColliderBox(sf::IntRect(static_cast<int>(m_position.x), static_cast<int>(m_position.y), properties.m_width, properties.m_height));
	m_body.SetGravity(3.0f);
}

Player::~Player()
{
}

void Player::Update(const float dt)
{
	Movement(dt);
	m_animation.Update(dt);
}

void Player::Render()
{
	m_animation.Draw(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_properties.m_width, m_properties.m_height);
}

void Player::Movement(const float dt)
{
	m_animation.SetProperties(m_properties.m_textureId, 0, 1, 80);
	m_body.ResetForce();

	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::A))
	{
		m_body.ApplyForceX(-2.f);
		m_animation.SetProperties(m_properties.m_textureId, 3, 8, 100, Flip::left);
	}
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::D))
	{
		m_body.ApplyForceX(2.f);
		m_animation.SetProperties(m_properties.m_textureId, 3, 8, 100, Flip::right);
	}
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::Space) && !m_jumping)
	{
		m_body.ApplyForceY(-10.f);
		m_jumping = true;
	}

	m_body.Update(dt);

	//x position
	m_lastSafePosition.x = m_position.x;
	m_position.x += m_body.GetPosition().x;
	m_collider.SetColliderBox(sf::IntRect(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_properties.m_width, m_properties.m_height));

	if (CollisionHandler::GetInstance()->MapCollision(m_collider.GetColliderBox()))
	{
		m_position.x = m_lastSafePosition.x;
	}

	//y position
	m_body.Update(dt);
	m_lastSafePosition.y = m_position.y;
	m_position.y += m_body.GetPosition().y;
	m_collider.SetColliderBox(sf::IntRect(static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_properties.m_width, m_properties.m_height));

	if (CollisionHandler::GetInstance()->MapCollision(m_collider.GetColliderBox()))
	{
		m_position.y = m_lastSafePosition.y;
		m_jumping = false;
	}

	m_origin.x = m_position.x + m_properties.m_width / 2.f;
	m_origin.y = m_position.y + m_properties.m_height / 2.f;
}
