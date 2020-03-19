#pragma once

#include "Util.h"
#include "SFML/graphics.hpp"
#include "IHUDItem.h"
#include "Movable.h"

class Minimap : public HUDItem {
    public:
    Minimap(const sf::RenderWindow& window, const Movable&, sf::View&);
    void update() noexcept override;
    void show() noexcept override;
    void hide() noexcept override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
    const Movable& player;
    const sf::RenderWindow& window;
    static constexpr float viewSize[2] {100.f,100.f};
    sf::View& directionView;
};