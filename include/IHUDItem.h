#pragma once

#include "SFML/graphics.hpp"
#include "Util.h"

class HUDItem : public sf::Drawable {
    //virtual ~HudItem() = 0;
    public:
    virtual void update() noexcept = 0;
    virtual void hide() noexcept = 0;
    virtual void show() noexcept = 0;
    protected:
    static constexpr float xMargin=30, yMargin=30;
};