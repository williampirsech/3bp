#include "MovableCreator.h"


Movable MovableCreator::create(const std::string& filename) {
    
    sf::VertexArray va(sf::TriangleFan);

    rapidxml::file<> xmlFile((std::string("resource/data/movable/")+filename).c_str()); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    auto *node = doc.first_node("Movable");

    for (auto child = node->first_node("VertexArray")->first_node("item"); child != nullptr; child = child->next_sibling()) {
        std::string x = child->first_node("x")->value();
        std::string y = child->first_node("y")->value();
        sf::Vertex v(sf::Vector2f(stof(x),stof(y)));
        v.color = sf::Color::White;
        
        va.append(v);
    }

    Movable m(va);

    return m;
}

Movable MovableCreator::planetMaker(const float radius, const int nVert, const sf::Color& color) {
    sf::VertexArray va(sf::TriangleFan);
    auto incr = PI2()/nVert;
    for (int k=0; k<nVert; ++k) {
        auto vert = sf::Vertex(sf::Vector2f(radius*cos(k*incr),radius*sin(k*incr)));
        vert.color = color;
        va.append(vert);
    }
    //va.append(va[0]);
    return Movable(va);
}