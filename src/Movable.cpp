#include "Movable.h"

//Movable::~Movable() {}

Movable::Movable(std::shared_ptr<sf::Shape> ptr) {
    pShape = ptr;
    auto b = ptr->getGlobalBounds();
    pShape->setOrigin(b.width/2,b.height/2);
    velocity.x = 0; velocity.y = 0;
}

const sf::Shape& Movable::getShape() const noexcept {
    return *pShape;
}

void Movable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*pShape);
}