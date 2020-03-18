#include "DirectionMeter.h"

DirectionMeter::DirectionMeter(const sf::RenderWindow& window, const sf::Texture& texture)
    : window(window) {
        indicator.setTexture(texture);
}

void DirectionMeter::update() noexcept {
    indicator.setPosition(window.getDefaultView().getSize().x,window.getDefaultView().getSize().y-60);
}

void DirectionMeter::show() noexcept {
    //...
}

void DirectionMeter::hide() noexcept {
    //...
}

void DirectionMeter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(indicator);
};