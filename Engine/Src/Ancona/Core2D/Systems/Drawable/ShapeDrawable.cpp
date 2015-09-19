#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Util2D/VectorMath.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::ShapeDrawable);

using namespace ild;

ShapeDrawable::ShapeDrawable(
        sf::Shape * shape,
        const int priorty,
        const std::string & key,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            priorty,
            key,
            priorityOffset,
            positionOffset),
    _shape(shape)
{
}

void ShapeDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta)
{
    sf::RenderStates states(drawableTransform);
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
sf::Vector2f ShapeDrawable::size()
{
    sf::Vector2f size(_shape->getLocalBounds().width, _shape->getLocalBounds().height);
    return VectorMath::ComponentMultiplication(size, _scale);
}

int ShapeDrawable::alpha()
{
    return _shape->getFillColor().a;
}

void ShapeDrawable::alpha(int alpha)
{
    sf::Color outlineCol(_shape->getOutlineColor());
    outlineCol.a = alpha;
    _shape->setOutlineColor(outlineCol);

    sf::Color fillCol(_shape->getFillColor());
    fillCol.a = alpha;
    _shape->setFillColor(fillCol);
}

