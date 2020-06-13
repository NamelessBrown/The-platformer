#pragma once

#include <SFML/Graphics.hpp>

class GameState
{
public:
    virtual ~GameState();
    virtual void Render() = 0;
    virtual void Update(sf::RenderWindow& window, const float dt) = 0;
    virtual void HandleInput() = 0;
};

