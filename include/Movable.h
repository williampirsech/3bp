#pragma once

#include "Util.h"
#include "SFML/graphics.hpp"


class Movable  {
    
    public: 

    explicit Movable(const std::shared_ptr<sf::Shape>);

    std::shared_ptr<sf::Shape> getShape(void) const noexcept;

    protected:

    private:

    std::shared_ptr<sf::Shape> pShape;
    Velocity velocity;

    friend class ScreenMovement;
};