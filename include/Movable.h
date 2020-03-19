#pragma once

#include "Util.h"
#include "SFML/graphics.hpp"


class Movable : public sf::Drawable {
    
    public: 

    explicit Movable(const std::shared_ptr<sf::Shape>);

    const sf::Shape& getShape(void) const noexcept;

    protected:

    private:

    std::shared_ptr<sf::Shape> pShape;
    Velocity velocity;

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;

    friend class ScreenMovement;
};