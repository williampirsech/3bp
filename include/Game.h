#pragma once

#include "Util.h"
#include "Movable.h"
#include "MassiveMovable.h"
#include "ScreenMovement.h"
#include "Dynamics.h"
#include "SFML/Graphics.hpp"
#include "FuelMeter.h"
#include "DirectionMeter.h"

class Game {
    public:
    
    Game(void);
    
    void Draw(sf::Drawable&);
    
    void init(void);
    void run(void);

    private:
    sf::Font font;
    sf::RenderWindow window;
    sf::Texture directionTexture;
    ScreenMovement movement;
    Dynamics dynamics;
};