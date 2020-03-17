#include "MassiveMovable.h"

MassiveMovable::MassiveMovable(const std::shared_ptr<sf::Shape> ptr, const Mass mass) 
    : Movable(ptr)
    , mass(mass)
{}