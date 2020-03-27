#pragma once

#include "Util.h"
#include "Movable.h"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

class MovableCreator {
    public:
    static Movable create(const std::string&);
    static Movable planetMaker(const float, const int, const sf::Color&);
};