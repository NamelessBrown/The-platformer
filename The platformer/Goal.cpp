#include "Goal.h"
#include "Engine/TextureManager.h"

Goal::Goal(const GameObjectProperties& properties, int scaleDown)
	:GameObject(properties), m_gotten(false)
{
	m_collider.SetColliderBox(sf::IntRect(properties.m_position.x, m_properties.m_position.y, m_properties.m_width / scaleDown, m_properties.m_height / scaleDown));
}

Goal& Goal::operator=(const Goal& g)
{
	m_gotten = false;
	m_position = g.m_position;
	m_origin = g.m_origin;
	m_properties = g.m_properties;

	return *this;
}

Goal::~Goal()
{
}

void Goal::Update(const float dt)
{
}

void Goal::Render()
{
	TextureManager::GetInstance()->DrawFrame("DDD", m_properties.m_position.x, m_properties.m_position.y, m_properties.m_width, m_properties.m_height, 0, 0);
}
