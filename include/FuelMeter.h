#include "SFML/graphics.hpp"

#include "Util.h"
#include "HUDItem.h"

class FuelMeter : public HUDItem {
    public:
    FuelMeter(const sf::RenderTarget&);
    void update() noexcept override;
    void show() noexcept override;
    void hide() noexcept override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    private:
    float fuelLeft;
    private:
    static constexpr float maxWidth=200, maxHeight=30;
    sf::RectangleShape meter;
    const sf::RenderTarget& target;
};