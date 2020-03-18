#pragma once

#include "Util.h"
#include "SFML/graphics.hpp"
#include "HUDItem.h"

class DirectionMeter : public HUDItem {
    public:
    DirectionMeter(const sf::RenderWindow& window, const sf::Texture&);
    void update() noexcept override;
    void show() noexcept override;
    void hide() noexcept override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
    sf::Sprite indicator;
    const sf::RenderWindow& window;
};