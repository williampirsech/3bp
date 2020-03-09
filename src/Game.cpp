#include "Game.h"

Game::Game() {}

void Game::init() {
    window.create(sf::VideoMode(800,600), "Game");
    setPlayerPosition(0,0);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event e;
        
        while (window.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        // Do something
        window.display();
    }
}

void Game::setPlayerPosition(int x, int y) {
    playerPosition.x = x;
    playerPosition.y = y;
}

Coord Game::getPlayerPosition(void) {
    return playerPosition;
}