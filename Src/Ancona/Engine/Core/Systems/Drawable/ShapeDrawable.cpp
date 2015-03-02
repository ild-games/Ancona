#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

using namespace ild;

ShapeDrawable::ShapeDrawable(
        const BasePhysicsComponent & physicsComponent,
        sf::Shape & shape,
        const int priorty,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsComponent,
            priorty,
            priorityOffset,
            positionOffset),
    _shape(shape)
{
    _shape.setOrigin(
            _shape.getLocalBounds().width / 2, 
            _shape.getLocalBounds().height / 2);
}

void ShapeDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent.GetInfo().GetPosition();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _shape.setPosition(position.x, position.y);
    _shape.setRotation(_rotation);
    window.draw(_shape);
}

void * ShapeDrawable::Inflate(
        const Json::Value & object,
        const Entity entity,
        LoadingContext * loadingContext)
{
    ShapeDrawable * shape = new ShapeDrawable(
            *loadingContext->GetSystems().GetSystem<PlatformPhysicsSystem>("physics")->at(entity),
            *new sf::RectangleShape(sf::Vector2f(object["shape"]["width"].asFloat(), object["shape"]["height"].asFloat())),
            object["render-priority"].asInt(),
            object["priority-offset"].asInt(),
            sf::Vector2f(object["position-offset"]["x"].asFloat(), object["position-offset"]["y"].asFloat()));
    return shape;
}


/* getters and setters */
sf::Vector2u ShapeDrawable::GetSize()
{
    return sf::Vector2u(
            _shape.getLocalBounds().width, 
            _shape.getLocalBounds().height);
}

int ShapeDrawable::GetAlpha()
{
    return _shape.getFillColor().a;
}

void ShapeDrawable::SetAlpha(int alpha)
{
    sf::Color * outlineCol = 
        new sf::Color(_shape.getOutlineColor());
    outlineCol->a = alpha;
    _shape.setOutlineColor(*outlineCol);

    sf::Color * fillCol = 
        new sf::Color(_shape.getFillColor());
    fillCol->a = alpha;
    _shape.setFillColor(*fillCol);

    delete outlineCol;
    delete fillCol;
}
