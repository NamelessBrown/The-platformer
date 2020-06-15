#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "TileLayer.h"
#include "Map.h" 

/*
	WARNING: MAKE SURE YOU USE THE INIT FUNCTION BEFORE ANYTHING ELSE!
*/

class CollisionHandler
{
public:
	static CollisionHandler* GetInstance();
	~CollisionHandler();
public:
	/*ALWAYS INITALIZE A MAP OR IT WILL BE A NULLPTR */
	bool Init(Map& map);
	bool CheckCollision(const sf::IntRect& box, const sf::IntRect& box2);
	bool MapCollision(const sf::IntRect& box);
	void Quit();
private:
	CollisionHandler();
private:
	static CollisionHandler* s_instance;
	Map* m_map = nullptr;
	TileMap m_tileMap;
	TileLayer* m_collisionLayer = nullptr;
};

