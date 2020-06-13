#pragma once

#include <vector>
#include "Layer.h"

class Map
{
public:
	virtual ~Map();

	void Update();
	void Render();

	const std::vector<Layer*>& GetLayers() const;
private:
	friend class MapParser;
	std::vector<Layer*> m_mapLayers;
};

