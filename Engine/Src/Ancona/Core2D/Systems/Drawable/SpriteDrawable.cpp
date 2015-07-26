#include <Ancona/Core2D/Systems/Drawable/SpriteDrawable.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::SpriteDrawable)

using namespace ild;

SpriteDrawable::SpriteDrawable(
        BasePhysicsSystem * physicsSystem,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsSystem,
            priority,
            priorityOffset,
            positionOffset)
{
}

void SpriteDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent->GetInfo().position();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _image->position(position);
    _image->Draw(window, delta);
}

void SpriteDrawable::FetchDependencies(const Entity &entity) 
{
    _image->SetupSprite();
    Drawable::FetchDependencies(entity);
}

void SpriteDrawable::Serialize(Archive &archive) 
{
    Drawable::Serialize(archive);
    archive(_image, "image");
}

/* getters and setters */
sf::Vector2u SpriteDrawable::size()
{
    return _image->size();
}

int SpriteDrawable::alpha()
{
    return _image->alpha();
}

void SpriteDrawable::alpha(int alpha)
{
    _image->alpha(alpha);
}

void SpriteDrawable::rotation(float newRotation)
{
    _rotation = newRotation;
    _image->rotation(newRotation);
}

void SpriteDrawable::scale(sf::Vector2f newScale)
{
    _scale = newScale;
    _image->scale(newScale);
}
