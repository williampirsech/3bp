#pragma once

#include "SFML/Graphics.hpp"

using Coord = sf::Vector2i;

class Game {
    public:
    
    Game(void);
    
    void init(void);
    void run(void);
    Coord getPlayerPosition(void);
    void setPlayerPosition(int,int);
    private:
    sf::RenderWindow window;
    Coord playerPosition;
};