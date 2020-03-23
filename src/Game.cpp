#include "Game.h"

#include <iostream>

Game::Game(void) 
    : window()
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

    if (!font.loadFromFile("resource/font/arialbd.ttf")) {
        //std::cout << "Failed to load font" << std::endl;
    }

    if (!directionTexture.loadFromFile("resource/img/arrow.png")) {
        //std::cout << "Failed to load texture" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("resource/skybox/3.png")) {
        //std::cout << "Failed to load texture" << std::endl;
    }
    background.setTexture(backgroundTexture);
}

void Game::run() {
    //Just a demo
    sf::Clock clock;
    auto pS = std::make_shared<sf::ConvexShape>();
    
    pS->setPointCount(3);
    pS->setPoint(0,sf::Vector2f(0,0));
    pS->setPoint(1,sf::Vector2f(0,6));
    pS->setPoint(2,sf::Vector2f(12,3));
    pS->setFillColor(sf::Color(255,255,255));

    Movable player(pS);

    auto pT = std::make_shared<sf::CircleShape>(5);
    auto pT2 = std::make_shared<sf::CircleShape>(80);
    MassiveMovable planet(pT,0.005);
    MassiveMovable sun(pT2,0.03);
    
    pT->setFillColor(sf::Color::White);
    pT2->setFillColor(sf::Color::White);
    
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
    
    dynamics.add(player);
    dynamics.add(sun);
    dynamics.add(planet);

    sf::View gameView(player.getShape()->getPosition(),viewSize);
    sf::View directionView(player.getShape()->getPosition(), sf::Vector2f(100,100));
    directionView.setViewport(sf::FloatRect(0.8f,0.8f,0.2f,0.2f));

    background.setScale(window.getSize().x/background.getGlobalBounds().width,window.getSize().y/background.getGlobalBounds().height);
    FuelMeter fuelmeter(window);
    fuelmeter.show();
    Minimap minimap(window,player,directionView);
    minimap.show();

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
            gameView.setSize(viewSize);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            
                viewSize.x -= viewRatio*viewIncrement;
                viewSize.y -= viewIncrement;
                gameView.setSize(viewSize);
        }

        window.clear(sf::Color::Black);
        
        gameView.setCenter(player.getShape()->getPosition());
        
        window.setView(window.getDefaultView());
        
        window.draw(background);
        fuelmeter.update();
        window.draw(fuelmeter);
        
        window.setView(directionView);
        minimap.update();
        window.draw(*player.getShape());

        
        dynamics.incrementSystem(dt);
        
        window.setView(gameView);
        
        for (const auto& p : dynamics.getMovables()) {
            window.draw(*(p->getShape()));
        }
        
        window.display();
    }
}