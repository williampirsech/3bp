#include "ScreenMovement.h"

ScreenMovement::ScreenMovement(const sf::Window& window)
    : window(window)
{}

const Coordinate ScreenMovement::getPosition(const Movable& movable) const noexcept {
    Coordinate result(movable.pShape->getPosition());
    result.x = result.x/window.getSize().x;
    result.y = result.y/window.getSize().y;
    
    return result;
}

void ScreenMovement::setPosition(Movable& movable, const float x, const float y) const noexcept {
    movable.pShape->setPosition(x*window.getSize().x, y*window.getSize().y);
}

void ScreenMovement::setRotation(Movable& movable, const Angle angle) const noexcept {
    movable.pShape->setRotation(angle);
}

void ScreenMovement::setVelocity(Movable& movable, const double vx, const double vy) const noexcept {
    movable.velocity.x = vx;
    movable.velocity.y = vy;
}

void ScreenMovement::rotate(Movable& movable, const TimeDelta dt, Angle delta) const noexcept {
    movable.pShape->rotate(delta*dt);
}

void ScreenMovement::moveForward(Movable& movable, const TimeDelta dt) const noexcept {
    movable.pShape->move(
        dt*movable.velocity.x*window.getSize().x,
        dt*movable.velocity.y*window.getSize().y
    );
}

void ScreenMovement::addVelocity(Movable& movable, const TimeDelta dt, const float vx, const float vy) const noexcept {
    movable.velocity.x += dt*vx;
    movable.velocity.y += dt*vy;
}

void ScreenMovement::accelerate(Movable& movable, const TimeDelta dt, const float delta) const noexcept {
    movable.velocity.x += dt*delta*cos(D2R()*movable.pShape->getRotation());
    movable.velocity.y += dt*delta*sin(D2R()*movable.pShape->getRotation());
}