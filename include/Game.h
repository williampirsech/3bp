#pragma once

#include "Util.h"
#include "Movable.h"
#include "MassiveMovable.h"
#include "ScreenMovement.h"
#include "Dynamics.h"
#include "SFML/Graphics.hpp"

class Game {
    public:
    
    Game(void);
    
    void Draw(sf::Drawable&);
    
    void init(void);
    void run(void);

    private:
    sf::RenderWindow window;
    ScreenMovement movement;
    Dynamics dynamics;
};