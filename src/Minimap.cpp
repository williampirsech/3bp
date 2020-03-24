#include "Minimap.h"

Minimap::Minimap(const sf::RenderTarget& window, const Movable& player, sf::View& directionView)
    : window(window) 
    , player(player)
    , directionView(directionView)
{
}

void Minimap::update() noexcept {
    directionView.setCenter(player.getPosition());
}

void Minimap::show() noexcept {
    // Not really implemented
}

void Minimap::hide() noexcept {
    // same
}

void Minimap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(player.getVertexArray());
};