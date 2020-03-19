#include "FuelMeter.h"

FuelMeter::FuelMeter(const sf::RenderTarget& target)
    : fuelLeft(1.0)
    , meter(sf::Vector2f(maxWidth,maxHeight))
    , target(target)
    {}

void FuelMeter::update() noexcept {
    meter.setPosition(xMargin, target.getDefaultView().getSize().y-maxHeight-yMargin);
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