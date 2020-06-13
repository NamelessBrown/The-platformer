#pragma once

#include <string>
#include "TextureManager.h"

class Animation
{
public:
	Animation();
	~Animation();
	void Update(const float& dt);
	void Draw(const int x, const int y, const int width, const int height);
	void SetProperties(std::string textureID, int row, int numberOfFrames, int animationSpeed, Flip flip = Flip::none);
private:
	void Advance();
private:
	static constexpr float m_holdTime = 5.5f;
	float m_time;
	int m_spriteRow;
	int m_spriteFrame;
	int m_animationSpeed;
	int m_numberOfFrames;
	std::string m_textureID;
	Flip m_flip;
};

