#pragma once

#include <memory>
#include <iostream>

#include "Util.h"
#include "SFML/graphics.hpp"

class Movable : public sf::Drawable {
    
    public: 

    
    Movable(void);

    ~Movable();

    template <class ShapeType>
    void create(const ShapeType& shape) {
        pShape = std::make_shared<ShapeType>(shape);
        auto b = shape.getGlobalBounds();
        pShape->setOrigin(b.width/2,b.height/2);
        velocity.x = 0; velocity.y = 0;
        angle_c = 1; angle_s=0;
    }
    
    const Coordinate& getPosition(void) const noexcept;
    const Angle      getRotation(void) const noexcept;
    const Velocity&   getVelocity(void) const noexcept;
    const Coordinate& getCenter(void) const noexcept;  

    void        setPosition(const double, const double) noexcept;
    void        setRotation(const Angle) noexcept;
    void        setVelocity(const double, const double) noexcept;
    void        setCenter(const double, const double) noexcept;
    void        setColor(const sf::Color&) noexcept;

    void        rotate(const Angle) noexcept;
    void        moveForward(void) noexcept;
    void        addVelocity(const float, const float) noexcept;
    void        accelerate(const float) noexcept;

    protected:

    private: 

    std::shared_ptr<sf::Shape> pShape;
    
    Coordinate size;
    float angle_c, angle_s;
    Velocity velocity;

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};