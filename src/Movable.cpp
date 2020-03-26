#include "Movable.h"

//Movable::~Movable() {}

/*
Movable::Movable(std::shared_ptr<sf::Shape> ptr) {
    pShape = ptr;
    auto b = ptr->getGlobalBounds();
    pShape->setOrigin(b.width/2,b.height/2);

    velocity.x = 0; velocity.y = 0;
}*/
Movable::Movable(sf::VertexArray& vert)
        : vert(vert)
        , center(0,0)
        , angle(0.f)
        , velocity(0,0)
        , mass(0)
        , _radius2(0)
        , collidableState{CollidableState::Transparent}
{
    for (int k=0; k<vert.getVertexCount(); ++k) {
        center += vert[k].position;
        
    }
    center *= 1.f/vert.getVertexCount();
    for (int k=0; k<vert.getVertexCount(); ++k) {
        _radius2 = max(_radius2,norm2(vert[k].position-center));
    }
}

void Movable::setRotation(Angle theta) noexcept {
    angle = theta;
    transform = sf::Transform::Identity;
    transform.rotate(angle, center.x, center.y);
    _rotationUpdate();
}

void Movable::setPosition(const float x, const float y) noexcept {
    const sf::Vector2f moveDistance{x-center.x,y-center.y};
    for (int k=0; k<vert.getVertexCount(); ++k) 
        vert[k].position += moveDistance;
    center = {x,y};
}

void Movable::setPosition(const sf::Vector2f& pos) noexcept {
    const sf::Vector2f moveDistance = pos - center;
    for (int k=0; k<vert.getVertexCount(); ++k)
        vert[k].position += moveDistance;
    center = pos;
}

void Movable::setVelocity(const float x, const float y) noexcept { velocity = {x,y}; }

void Movable::rotate(const TimeDelta dt, const Angle theta) noexcept {
    angle += dt*theta;
    transform = sf::Transform::Identity;
    transform.rotate(theta*dt,center.x,center.y);
    _rotationUpdate();
}

void Movable::setMass(const Mass _mass) noexcept { mass = _mass; }

void Movable::moveForward(const TimeDelta dt) noexcept {
    const auto ds = dt*velocity*600.f;
    for (int k=0; k<vert.getVertexCount(); ++k)
        vert[k].position += ds;
    center += ds;
}

void Movable::addVelocity(const TimeDelta dt, const float vx, const float vy) noexcept {
    velocity.x += dt * vx;
    velocity.y += dt * vy;
}

void Movable::accelerate(const TimeDelta dt, const float delta) noexcept {
    const auto a2r = D2R()*angle;
    velocity.x += dt*delta*cos(a2r);
    velocity.y += dt*delta*sin(a2r);
}

const sf::VertexArray& Movable::getVertexArray() const noexcept {
    return vert;
}

void Movable::_rotationUpdate() noexcept {
    for (int k=0; k<vert.getVertexCount(); ++k)
        vert[k].position = transform.transformPoint(vert[k].position);
}

const Angle Movable::getRotation() const noexcept { return angle; }
const Coordinate Movable::getPosition() const noexcept { return center; }