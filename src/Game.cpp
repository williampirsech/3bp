#include "Game.h"
#include "SFML/Graphics.hpp"

#include <iostream>

Game::Game()
    : window()
{}

void Game::Draw(sf::Drawable& d) {
    window.draw(d);
}

void Game::init() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(800,600), "Game",sf::Style::Default,settings);
}

void Game::run() {

    sf::Clock clock;

    Movable player;
    sf::ConvexShape s;
    s.setPointCount(3);
    s.setPoint(0,sf::Vector2f(0,0));
    s.setPoint(1,sf::Vector2f(0,20));
    s.setPoint(2,sf::Vector2f(50,10));
    player.create(s);
    player.setPosition(100,100);


    player.setColor(sf::Color(255,255,255));

    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed: window.close(); break;
                case sf::Event::KeyPressed: {
                    switch (e.key.code) {
                         case sf::Keyboard::W: 
                            player.accelerate(0.005);
                            break;
                         case sf::Keyboard::S: 
                            player.accelerate(-0.005);
                            break;
                         case sf::Keyboard::A: player.rotate(-3); break;
                         case sf::Keyboard::D: player.rotate(3); break;

                         default: break;
                    }
                }
                default: break;
            }
        }
        
        window.clear(sf::Color::Black);
        
        player.moveForward();
        player.setPosition(fmod(window.getSize().x+player.getPosition().x,window.getSize().x),
                           fmod(window.getSize().y+player.getPosition().y,window.getSize().y));
        window.draw(player);

        window.display();
    }
}