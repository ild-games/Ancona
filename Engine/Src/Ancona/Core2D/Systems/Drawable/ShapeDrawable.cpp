#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ShapeDrawable);

using namespace ild;

ShapeDrawable::ShapeDrawable(
        sf::Shape * shape,
        const int priorty,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priorty,
            priorityOffset,
            positionOffset),
    _shape(shape)
{
}

void ShapeDrawable::Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta)
{
    Drawable::Draw(window, parentTransform, delta);
    sf::RenderStates states(parentTransform.combine(_transform));
    window.draw(*_shape, states);
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

