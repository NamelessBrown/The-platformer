#include "TileLayer.h"
#include "TextureManager.h"
#include "Engine.h"

TileLayer::TileLayer(unsigned tileSize, unsigned rowCount, unsigned columnCount, TileMap tileMap, TileSetList tileSets)
	:m_tileSize(tileSize), m_numberOfRows(rowCount), m_numberOfColumn(columnCount), m_tileMap(tileMap), m_tileSets(tileSets)
{
	for (unsigned i = 0; i < m_tileSets.size(); i++)
	{
		TextureManager::GetInstance()->Load(m_tileSets[i].name, "map/" + m_tileSets[i].source);
	}
}

TileLayer::~TileLayer()
{
}

void TileLayer::Update()
{
}

void TileLayer::Render()
{
	for (unsigned i = 0; i < m_numberOfRows; i++)
	{
		for (unsigned j = 0; j < m_numberOfColumn; j++)
		{
			unsigned tileID = m_tileMap[i][j];

			if (tileID == 0)
			{
				continue;
			}
			else
			{
				int index = 0;
				if (m_tileSets.size() > 1)
				{
					for (unsigned k = 1; k < m_tileSets.size(); k++)
					{
						if (tileID > m_tileSets[k].firstID && tileID < m_tileSets[k].lastID)
						{
							tileID += m_tileSets[k].tileCount - m_tileSets[k].lastID;
							index = k;
							break;
						}
					}
				}

				TileSet ts = m_tileSets[index];
				int tileRow = tileID / ts.column;
				int tileColum = tileID - tileRow * ts.column - 1;

				if (tileID % ts.column == 0)
				{
					tileRow--;
					tileColum = ts.column - 1;
				}

				TextureManager::GetInstance()->DrawTile(ts.name, ts.tileSize, j * ts.tileSize, i * ts.tileSize, tileRow, tileColum);

			}

		}
	}
}

const TileMap& TileLayer::GetTileMap() const
{
	return m_tileMap;
}

const unsigned TileLayer::GetNumberOfRows() const
{
	return m_numberOfRows;
}

const unsigned TileLayer::GetNumberOfColumns() const
{
	return m_numberOfColumn;
}

const unsigned TileLayer::GetTileSize() const
{
	if (!m_tileSets.empty())
	{
		return m_tileSets.front().tileSize;
	}

	return 1;
}
