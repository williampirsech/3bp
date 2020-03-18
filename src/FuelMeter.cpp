#include "FuelMeter.h"

FuelMeter::FuelMeter(const sf::RenderWindow& window)
    : fuelLeft(1.0)
    , meter(sf::Vector2f(maxWidth,maxHeight))
    , window(window)
    {}

void FuelMeter::update() noexcept {
    meter.setPosition(xMargin, window.getDefaultView().getSize().y-maxHeight-yMargin);
    meter.setSize(sf::Vector2f(maxWidth*fuelLeft,maxHeight));
}

void FuelMeter::show() noexcept {
    meter.setFillColor(sf::Color::White);
}

void FuelMeter::hide() noexcept {
    meter.setFillColor(sf::Color::Transparent);
}

void FuelMeter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(meter);
};