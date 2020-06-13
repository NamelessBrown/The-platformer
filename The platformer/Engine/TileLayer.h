#pragma once

#include <string>
#include <vector>
#include "Layer.h"

struct TileSet
{
	unsigned firstID;
	unsigned lastID;
	unsigned row;
	unsigned column;
	unsigned tileCount;
	unsigned tileSize;
	std::string name;
	std::string source;
};

using TileSetList = std::vector<TileSet>;
using TileMap = std::vector<std::vector<unsigned> >;

class TileLayer : public Layer
{
public:
	TileLayer(unsigned tileSize, unsigned rowCount, unsigned columnCount, TileMap tileMap, TileSetList tileSets);
	virtual ~TileLayer();

	virtual void Update();
	virtual void Render();
	const TileMap& GetTileMap() const;
	const unsigned GetNumberOfRows() const;
	const unsigned GetNumberOfColumns() const;
	/* Returns the first tile size!!! If the tile are different sizes this may not work */
	const unsigned GetTileSize() const;
private:
	unsigned m_tileSize;
	unsigned m_numberOfRows;
	unsigned m_numberOfColumn;

	TileMap m_tileMap;
	TileSetList m_tileSets;
};

