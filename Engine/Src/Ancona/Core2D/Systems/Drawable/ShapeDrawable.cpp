#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ShapeDrawable)

using namespace ild;

ShapeDrawable::ShapeDrawable(
        BasePhysicsSystem * physicsSystem,
        sf::Shape * shape,
        const int priorty,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsSystem,
            priorty,
            priorityOffset,
            positionOffset),
    _shape(shape)
{
}

void ShapeDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent->GetInfo().position();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _shape->setPosition(position.x, position.y);
    window.draw(*_shape);
}

void ShapeDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    _shape->setOrigin(
        _shape->getLocalBounds().width / 2,
        _shape->getLocalBounds().height / 2);
}

void ShapeDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_shape, "shape");
}

/* getters and setters */
sf::Vector2u ShapeDrawable::size()
{
    return sf::Vector2u(
            _shape->getLocalBounds().width,
            _shape->getLocalBounds().height);
}

int ShapeDrawable::alpha()
{
    return _shape->getFillColor().a;
}

void ShapeDrawable::alpha(int alpha)
{
    sf::Color * outlineCol = 
        new sf::Color(_shape->getOutlineColor());
    outlineCol->a = alpha;
    _shape->setOutlineColor(*outlineCol);

    sf::Color * fillCol = 
        new sf::Color(_shape->getFillColor());
    fillCol->a = alpha;
    _shape->setFillColor(*fillCol);

    delete outlineCol;
    delete fillCol;
}

void ShapeDrawable::rotation(float newRotation)
{
    _rotation = newRotation;
    _shape->setRotation(_rotation);
}

void ShapeDrawable::scale(sf::Vector2f newScale)
{
    _scale = newScale;
    _shape->setScale(_scale);
}
