#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_instance = nullptr;

CollisionHandler* CollisionHandler::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new CollisionHandler();
    }

    return s_instance;
}

CollisionHandler::CollisionHandler()
{
}

CollisionHandler::~CollisionHandler()
{

}

bool CollisionHandler::Init(Map& map)
{
    m_map = &map;
    m_collisionLayer = (TileLayer*)m_map->GetLayers().front();
    m_tileMap = m_collisionLayer->GetTileMap();

    if (m_map == nullptr)
    {
        return false;
    }

    return true;
}

TileLayer* CollisionHandler::GetCollisionLayer() const
{
    return m_collisionLayer;
}

bool CollisionHandler::CheckCollision(const sf::IntRect& box, const sf::IntRect& box2)
{
    bool overlapX = (box.left < box2.left + box2.width) && (box.left + box.width > box2.left);
    bool overlapY = (box.top < box2.top + box2.height) && (box.top + box.height > box2.top);

    return overlapX && overlapY;
}

bool CollisionHandler::MapCollision(const sf::IntRect& box)
{
    const unsigned tileSize = m_collisionLayer->GetTileSize();
    const unsigned tileRows = m_collisionLayer->GetNumberOfRows();
    const unsigned tileColumns = m_collisionLayer->GetNumberOfColumns();

    unsigned left_tile = (unsigned)box.left / tileSize;
    unsigned right_tile = ((unsigned)box.left + (unsigned)box.width) / tileSize;
    unsigned top_tile = (unsigned)box.top / tileSize;
    unsigned bottom_tile = ((unsigned)box.top + (unsigned)box.height) / tileSize;

    if (left_tile < 0)
    {
        left_tile = 0;
    }
    if (right_tile > tileColumns)
    {
        right_tile = tileColumns;
    }
    if (top_tile < 0)
    {
        top_tile = 0;
    }
    if (bottom_tile > tileRows)
    {
        bottom_tile = tileRows;
    }

    for (auto i = left_tile; i <= right_tile; ++i)
    {
        for (auto j = top_tile; j <= bottom_tile; ++j)
        {
            if (m_tileMap[j][i] > 0)
            {
                return true;
            }
        }
    }

    return false;
}

void CollisionHandler::Quit()
{
    delete s_instance;
}
