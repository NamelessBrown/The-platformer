#include "Map.h"

Map::~Map()
{
}

void Map::Update()
{
	for (auto& e : m_mapLayers)
	{
		e->Update();
	}
}

void Map::Render()
{
	for (auto& e : m_mapLayers)
	{
		e->Render();
	}
}

const std::vector<Layer*>& Map::GetLayers() const
{
	return m_mapLayers;
}
