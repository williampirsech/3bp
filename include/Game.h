#pragma once

#include "Movable.h"
#include "SFML/Graphics.hpp"

class Game {
    public:
    
    Game(void);
    
    void Draw(sf::Drawable&);
    
    void init(void);
    void run(void);

    private:
    sf::RenderWindow window;
};