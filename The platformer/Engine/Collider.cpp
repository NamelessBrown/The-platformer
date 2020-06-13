#include "Collider.h"

Collider::~Collider()
{
}

void Collider::SetColliderBox(const sf::IntRect& box)
{
	m_box = box;
}

const sf::IntRect Collider::GetColliderBox() const
{
	return m_box;
}
