#pragma once

#include <map>
#include <string>
#include <iostream>
#include "Map.h"
#include "TileLayer.h"
#include "tinyxml.h"

class MapParser
{
public:
	static MapParser* GetInstance();
	bool Load(const std::string& id, const std::string& filename);
	void Quit();
	Map* GetMap(std::string id);
public:
	~MapParser();
private:
	MapParser();
	bool Parse(std::string id, std::string filename);
	TileSet ParseTileSet(TiXmlElement* xmlTileSet);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, unsigned tileSize, unsigned rowCount, unsigned columnCount);
private:
	static MapParser* s_instance;
	std::map<std::string, Map*> m_maps;
};

