#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Game.h"

int main() {
    
    Game g;

    g.init();
    g.run();
    
    return EXIT_SUCCESS;
}