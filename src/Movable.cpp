#include "Movable.h"

Movable::Movable(void) {}

Movable::~Movable(void) {}

const Coordinate& Movable::getPosition(void) const noexcept { return pShape->getPosition(); }
const Angle Movable::getRotation(void) const noexcept { return pShape->getRotation(); }
const Velocity& Movable::getVelocity() const noexcept { return velocity; }

void Movable::rotate(Angle delta) noexcept {
    pShape->rotate(delta);
}

void Movable::setPosition(const double x, const double y) noexcept {
    pShape->setPosition(x, y);
}

void Movable::setRotation(Angle angle) noexcept {
    pShape->setRotation(angle);
}

void Movable::setColor(const sf::Color& color) noexcept {
    pShape->setFillColor(color);
}

void Movable::setVelocity(const double vx, const double vy) noexcept {
    velocity.x = vx;
    velocity.y = vy;
}

void Movable::moveForward() noexcept {
    const auto dx = velocity.x;
    const auto dy = velocity.y;
    pShape->move(dx,dy);
}

void Movable::addVelocity(const float vx, const float vy) noexcept {
    velocity.x += vx;
    velocity.y += vy;
}

void Movable::accelerate(const float delta) noexcept {
    velocity.x += delta*cos(D2R()*pShape->getRotation());
    velocity.y += delta*sin(D2R()*pShape->getRotation());
}

void Movable::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*pShape);
}