#include "Dynamics.h"

Dynamics::Dynamics(const ScreenMovement& movement)
    : movement(movement)
    {}

std::vector<Movable *> Dynamics::getMovables() const noexcept {
    return movables;
}

void Dynamics::addNonMassive(Movable& movable) {
    movables.push_back(&movable);
}

void Dynamics::addMassive(MassiveMovable& movable) {
    movables.push_back(&movable);
    massives.push_back(&movable);
}

void Dynamics::incrementSystem(const TimeDelta dt) noexcept {
    for (auto& elem : movables) {
        for (const auto& other : massives) {
            auto res = movement.getPosition(*other)-movement.getPosition(*elem);
            if (res.x != 0 && res.y != 0) {
                float G = other->mass / (res.x*res.x+res.y*res.y);
                movement.addVelocity(*elem, dt, G*res.x, G*res.y);
                std::cout << "x = " << G*res.x << ", " << G*res.y << std::endl;
            
            }
        }
        movement.moveForward(*elem,dt);    
    }
    
}