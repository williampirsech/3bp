#include "Dynamics.h"

Dynamics::Dynamics(const ScreenMovement& movement)
    : movement(movement)
    {}

std::vector<Movable *> Dynamics::getMovables() const noexcept {
    return movables;
}

void Dynamics::add(Movable& movable) {
    movables.push_back(&movable);
}

void Dynamics::add(MassiveMovable& movable) {
    movables.push_back(&movable);
    massives.push_back(&movable);
}

void Dynamics::incrementSystem(const TimeDelta dt) const noexcept {
    sf::Vector2f res;
    for (auto& elem : movables) {
        for (const auto& other : massives) {
            res = movement.getPosition(*other)-movement.getPosition(*elem);
            if (res.x != 0 && res.y != 0) {
                float G = other->mass / (res.x*res.x+res.y*res.y);
                movement.addVelocity(*elem, dt, G*res.x, G*res.y);
                // Collision detection also goes here?
            }
        }
        movement.moveForward(*elem,dt); 
    }
}