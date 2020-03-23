#include "Movable.h"

//Movable::~Movable() {}

Movable::Movable(std::shared_ptr<sf::Shape> ptr) {
    pShape = ptr;
    auto b = ptr->getGlobalBounds();
    pShape->setOrigin(b.width/2,b.height/2);
    velocity.x = 0; velocity.y = 0;
}

std::shared_ptr<sf::Shape> Movable::getShape() const noexcept {
    return pShape;
}
