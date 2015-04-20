#include <Ancona/Core2D/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::SpriteDrawable)

using namespace ild;

SpriteDrawable::SpriteDrawable(
        BasePhysicsSystem * physicsSystem,
        const std::string textureKey,
        const int priority,
        int priorityOffset,
        sf::Vector2f positionOffset) :
    Drawable(
            physicsSystem,
            priority,
            priorityOffset,
            positionOffset), 
    _textureKey(textureKey)
{
}

void SpriteDrawable::Draw(sf::RenderWindow & window, float delta)
{
    auto pos = _physicsComponent->GetInfo().position();
    sf::Vector2f position = sf::Vector2f(
            pos.x + _positionOffset.x,
            pos.y + _positionOffset.y);
    _sprite->setPosition(position.x,position.y);
    _sprite->setRotation(_rotation);
    window.draw(*_sprite);
}

void SpriteDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);
    _sprite = new sf::Sprite(texture);
    _sprite->setOrigin(
            texture.getSize().x / 2,
            texture.getSize().y / 2);
}

void SpriteDrawable::Serialize(Archive &archive) {
    Drawable::Serialize(archive);
    archive(_textureKey, "texture-key");
}

/* getters and setters */
sf::Vector2u SpriteDrawable::size()
{
    return sf::Vector2u(
            _sprite->getLocalBounds().width,
            _sprite->getLocalBounds().height);
}

int SpriteDrawable::alpha()
{
    return _sprite->getColor().a;
}

void SpriteDrawable::alpha(int alpha)
{
    sf::Color col(_sprite->getColor());
    col.a = alpha;
    _sprite->setColor(col);
}