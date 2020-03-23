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
    
    for (auto& elem : movables) {
        for (const auto& other : massives) {
            _res = movement.getPosition(*other)-movement.getPosition(*elem);
            if (_res.x != 0 && _res.y != 0) {
                float G = other->mass / (_res.x*_res.x+_res.y*_res.y);
                movement.addVelocity(*elem, dt, G*_res.x, G*_res.y);
                // Collision detection also goes here?
            }
        }
        movement.moveForward(*elem,dt); 
    }
}