#pragma once

class Layer
{
public:
	virtual ~Layer()
	{

	}

	virtual void Update() = 0;
	virtual void Render() = 0;
};