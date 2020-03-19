#pragma once

#include "Util.h"
#include "Movable.h"

class MassiveMovable : public Movable {
    public:
    explicit MassiveMovable(const std::shared_ptr<sf::Shape>, const Mass);
    Mass mass;    
};