#include "Goal.h"
#include "Engine/TextureManager.h"

Goal::Goal(const GameObjectProperties& properties)
	:GameObject(properties), m_gotten(false)
{

}

Goal::~Goal()
{
}

void Goal::Update(const float dt)
{
}

void Goal::Render()
{
	TextureManager::GetInstance()->Draw("DDD", m_properties.m_position.x, m_properties.m_position.y);
}
