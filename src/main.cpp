#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <sstream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Main");
    
    // Font
    sf::Font font;
    if (!font.loadFromFile("resource/font/arialbd.ttf")) {
        throw std::exception();
    }

    // Text    
    sf::Text text;
    text.setFont(font);
    text.setString("Hello World__");
    text.setCharacterSize(44);
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Regular);
    
    while (window.isOpen()) {
        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
    return 0;
}