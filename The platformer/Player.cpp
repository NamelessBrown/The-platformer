#include "Player.h"
#include "Engine/CollisionHandler.h"
#include "Engine/InputHandler.h"

Player::Player(const GameObjectProperties& properties)
	:GameObject(properties), m_flip(Flip::none)
{
	m_animation.SetProperties(properties.m_textureId, 0, 1, 0);
	m_collider.SetColliderBox(sf::IntRect(static_cast<int>(m_position.x), static_cast<int>(m_position.y), properties.m_width, properties.m_height));
	m_body.SetGravity(3);
}

Player::~Player()
{
}

const int Player::GetHealth() const
{
	return m_health;
}

void Player::SetHealth(const int health)
{
	m_health -= health;
}

void Player::Update(const float dt)
{
	Movement(dt);
	m_animation.Update(dt);
}

void Player::Render()
{
	TextureManager::GetInstance()->DrawText("font", "Health: " + std::to_string(m_health), 30, m_position.x, m_position.y);
	m_animation.Draw(m_position.x, m_position.y, m_properties.m_width, m_properties.m_height);
}

void Player::Movement(const float dt)
{
	m_animation.SetProperties(m_properties.m_textureId, 0, 1, 0);
	m_body.ResetForce();

	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::A))
	{
		m_flip = Flip::left;
		m_body.ApplyForceX(-2);
		m_animation.SetProperties(m_properties.m_textureId, 3, 3, 100, m_flip);
	}
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::D))
	{
		m_flip = Flip::right;
		m_body.ApplyForceX(2);
		m_animation.SetProperties(m_properties.m_textureId, 3, 3, 100, m_flip);
	}
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::Space))
	{
		m_body.ApplyForceY(-10);
	}
	if (InputHandler::GetInstance()->GetKeyDown(sf::Keyboard::Key::RShift))
	{
		m_animation.SetProperties(m_properties.m_textureId, 1, 6, 100, m_flip);
	}

	m_body.Update(dt);

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
	m_lastSafePosition.x = m_position.x;
	m_position.x += m_body.GetPosition().x;
	m_collider.SetColliderBox(sf::IntRect(m_position.x, m_position.y, m_properties.m_width, m_properties.m_height));

	if (CollisionHandler::GetInstance()->MapCollision(m_collider.GetColliderBox()))
	{
		m_position.x = m_lastSafePosition.x;
	}

	m_origin.x = m_position.x + m_properties.m_width / 2.f;
	m_origin.y = m_position.y + m_properties.m_height / 2.f;
}
