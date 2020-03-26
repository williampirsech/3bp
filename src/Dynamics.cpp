#include "Dynamics.h"

std::vector<Movable *> Dynamics::getMovables() const noexcept {
    return movables;
}

void Dynamics::add(Movable& movable) {
    movables.push_back(&movable);
}

void Dynamics::incrementSystem(const TimeDelta dt) const noexcept {   
    for (auto& elem : movables) {
        for (const auto& other : movables) {
            if (elem < other) {
                if (elem < other && Collision::collidesWith_rad(*elem,*other) && 
                    (Collision::collidesWith_vertexSep(*elem, *other) || Collision::collidesWith_vertexSep(*other, *elem))) {
                    std::cout << "MASS(" << elem->mass << ") " << " collided with "  <<  "MASS(" << other->mass << ") " << "\n";
                    auto p = elem->center - other->center;
                    auto d = norm(p);
                    if (elem->collidableState == CollidableState::Rigid)
                        elem->velocity += other->mass*dt*p/d;
                    if (other->collidableState == CollidableState::Rigid) 
                        other->velocity -= elem->mass*dt*p/d;
                }
            }
            
            if (other->mass != 0) {
                _res = other->getPosition() - elem->getPosition();
                if (_res.x != 0 && _res.y != 0) {
                    float G = other->mass / (_res.x*_res.x+_res.y*_res.y);
                    elem->addVelocity(dt,G*_res.x, G*_res.y);
                }
            }
        }
        elem->moveForward(dt);
    }
}