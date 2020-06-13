#include "Animation.h"

Animation::Animation()
	:m_spriteRow(0), m_spriteFrame(0), m_animationSpeed(0), m_numberOfFrames(0), m_time(0), m_flip(Flip::none)
{

}

Animation::~Animation()
{
}

void Animation::SetProperties(std::string textureID, int row, int numberOfFrames, int animationSpeed, Flip flip)
{
	m_textureID = textureID;
	m_spriteRow = row;
	m_numberOfFrames = numberOfFrames;
	m_animationSpeed = animationSpeed;
	m_flip = flip;
}

void Animation::Advance()
{
	if (++m_spriteFrame >= m_numberOfFrames)
	{
		m_spriteFrame = 0;
	}
}


void Animation::Update(const float& dt)
{
	m_time += dt;

	while (m_time >= m_holdTime)
	{
		m_time -= m_holdTime;
		Advance();
	}
}

void Animation::Draw(const int x, const int y, const int width, const int height)
{
	TextureManager::GetInstance()->DrawFrame(m_textureID, x, y, width, height, m_spriteRow, m_spriteFrame, m_flip);
}