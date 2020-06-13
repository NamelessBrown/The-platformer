#include "MapParser.h"
#include <sstream>

MapParser* MapParser::s_instance = nullptr;

MapParser* MapParser::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new MapParser();
	}

	return s_instance;
}

MapParser::MapParser()
{
}

MapParser::~MapParser()
{
	std::map<std::string, Map*>::iterator iter;
	for (iter = m_maps.begin(); iter != m_maps.end(); iter++)
	{
		delete iter->second;
	}

	m_maps.clear();
}

bool MapParser::Load(const std::string& id, const std::string& filename)
{
	if (!Parse(id, filename))
		return false;

	return true;
}

void MapParser::Quit()
{
	delete s_instance;
}

bool MapParser::Parse(std::string id, std::string filename)
{
	TiXmlDocument doc;
	doc.LoadFile(filename.c_str());

	if (doc.Error())
	{
		std::cout << doc.ErrorDesc() << '\n';
		return false;
	}

	TiXmlElement* root = doc.RootElement();
	int rows = 0;
	int column = 0;
	int tileSize = 0;

	root->Attribute("width", &column);
	root->Attribute("height", &rows);
	root->Attribute("tilewidth", &tileSize);

	//Parsing the tiles
	TileSetList tileSets;
	for (auto e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->ValueTStr() == "tileset")
		{
			tileSets.push_back(ParseTileSet(e));
		}
	}

	//Parsing the layers
	Map* gameMap = new Map();
	for (auto e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->ValueTStr() == "layer")
		{
			TileLayer* tileLayer = ParseTileLayer(e, tileSets, tileSize, rows, column);
			gameMap->m_mapLayers.push_back(tileLayer);
		}
	}

	m_maps[id] = gameMap;

	return true;
}

TileSet MapParser::ParseTileSet(TiXmlElement* xmlTileSet)
{
	TileSet tileSet;
	tileSet.name = xmlTileSet->Attribute("name");
	xmlTileSet->Attribute("firstgid", &tileSet.firstID);
	xmlTileSet->Attribute("tilecount", &tileSet.tileCount);
	tileSet.lastID = (tileSet.firstID + tileSet.tileCount) - 1;

	xmlTileSet->Attribute("columns", &tileSet.column);
	tileSet.row = tileSet.tileCount / tileSet.column;
	xmlTileSet->Attribute("tilewidth", &tileSet.tileSize);

	TiXmlElement* image = xmlTileSet->FirstChildElement();
	tileSet.source = image->Attribute("source");
	return tileSet;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TileSetList tilesets, unsigned tileSize, unsigned rowCount, unsigned columnCount)
{
	TiXmlElement* data = nullptr;

	for (auto e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->ValueTStr() == "data")
		{
			data = e;
			break;
		}
	}

	std::string matrix = data->GetText();
	std::istringstream iss(matrix);
	std::string id;

	TileMap tileMap(rowCount, std::vector<unsigned>(columnCount, 0));

	for (unsigned row = 0; row < rowCount; row++)
	{
		for (unsigned column = 0; column < columnCount; column++)
		{
			std::getline(iss, id, ',');
			std::stringstream converter(id);
			converter >> tileMap[row][column];

			if (!iss.good())
			{
				break;
			}

		}
	}

	return new TileLayer(tileSize, rowCount, columnCount, tileMap, tilesets);
}

Map* MapParser::GetMap(std::string id)
{
	return m_maps[id];
}

