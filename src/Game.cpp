#include "Game.h"

#include <iostream>

Game::Game(void) 
    : window()
    , movement(window)
    , dynamics(movement)
{}

void Game::Draw(sf::Drawable& d) {
    window.draw(d);
}

void Game::init() 
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(1067,600), "Game",sf::Style::Default,settings);
    window.setFramerateLimit(60);
}

void Game::run() {
    //Just a demo
    sf::Clock clock;
    auto pS = std::make_shared<sf::ConvexShape>();
    Movable player(pS);
    pS->setPointCount(3);
    pS->setPoint(0,sf::Vector2f(0,0));
    pS->setPoint(1,sf::Vector2f(0,6));
    pS->setPoint(2,sf::Vector2f(12,3));
    pS->setFillColor(sf::Color(255,255,255));

    auto pT = std::make_shared<sf::CircleShape>(20);
    auto pT2 = std::make_shared<sf::CircleShape>(80);
    MassiveMovable planet(pT,0.005);
    MassiveMovable sun(pT2,0.01);
    
    pT->setFillColor(sf::Color(255,255,255));
    pT2->setFillColor(sf::Color(255,255,255));
    
    movement.setPosition(player,0.35,0.35);
    movement.setVelocity(player,0.1,0);
    
    movement.setPosition(sun, 0.6,0.6);
    movement.setVelocity(sun,0,0);
    
    movement.setPosition(planet, 0.1,0.1);
    movement.setVelocity(planet,0.1,-0.1);

    std::cout << window.getSize().x << "," << window.getSize().y  << std::endl;
    
    auto viewSize = sf::Vector2f(window.getSize());
    auto viewRatio = viewSize.x/viewSize.y;
    const size_t viewIncrement = 5;
    
    dynamics.addNonMassive(player);
    dynamics.addMassive(sun);
    dynamics.addMassive(planet);

    sf::View view(player.getShape().getPosition(),viewSize);

    window.setView(view);
    
    while (window.isOpen()) {
        sf::Event e;
        while (window.pollEvent(e)) {
            switch(e.type) {
                case sf::Event::Closed: window.close(); break;
                default: break;
            }
        }

        auto dt = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                movement.accelerate(player,dt,0.08);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement.rotate(player,dt,-360);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement.rotate(player,dt,+360);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            viewSize.x += viewRatio*viewIncrement;
            viewSize.y += viewIncrement;
            view.setSize(viewSize);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            if (std::min(viewSize.x,viewSize.y) > viewIncrement) {
                viewSize.x -= viewRatio*viewIncrement;
                viewSize.y -= viewIncrement;
                view.setSize(viewSize);
            }
        }


        window.clear(sf::Color::Black);
        
        dynamics.incrementSystem(dt);
        
        for (const auto& p : dynamics.getMovables()) {
            window.draw(*p);
        }
        view.setCenter(player.getShape().getPosition());
        window.setView(view);

        window.display();
    }
}