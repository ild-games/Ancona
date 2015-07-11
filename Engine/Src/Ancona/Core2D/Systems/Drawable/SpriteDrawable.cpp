#include <Ancona/Core2D/Systems/Drawable/SpriteDrawable.hpp>

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

    for(int i = 0; i < _textureRects.size(); i++)
    {
        float newX = position.x + _textureRects[i].second.left;
        float newY = position.y + _textureRects[i].second.top;
        _sprites[i]->setPosition(newX, newY);
        _sprites[i]->setRotation(_rotation);
        window.draw(*_sprites[i]);
    }
}

void SpriteDrawable::FetchDependencies(const Entity &entity) 
{
    Drawable::FetchDependencies(entity);
    sf::Texture & texture = *ResourceLibrary::Get<sf::Texture>(_textureKey);

    if(_textureRects.size() == 0)
    {
        int textureWidth = texture.getSize().x, textureHeight = texture.getSize().y;
        _textureRects.push_back(std::pair<sf::IntRect, sf::IntRect>(
                sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(textureWidth, textureHeight)),
                sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(textureWidth, textureHeight))));
    }

    for(int i = 0; i < _textureRects.size(); i++)
    {
        _sprites.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(texture)));
        auto curRect = _textureRects[i];
        _sprites[i]->setTextureRect(curRect.first);
        _sprites[i]->setOrigin(
                (curRect.second.width / 2),
                (curRect.second.height / 2));
    }
}

void SpriteDrawable::Serialize(Archive &archive) 
{
    Drawable::Serialize(archive);
    archive(_textureKey, "texture-key");
    archive(_textureRects, "texture-rects");
}

bool SpriteDrawable::IsWholeTexture()
{
    return _textureRects.size() == 0;
}

/* getters and setters */
sf::Vector2u SpriteDrawable::size()
{
    float maxWidth = 0, maxHeight = 0, curWidth, curHeight;
    for(auto & sprite : _sprites)
    {
        curWidth = sprite->getPosition().x + sprite->getLocalBounds().width > maxWidth;
        curHeight = sprite->getPosition().y + sprite->getLocalBounds().height > maxHeight;
        if(curWidth > maxWidth)
        {
            maxWidth = curWidth;
        }
        if(curHeight > maxHeight)
        {
            maxHeight = curHeight;
        }
    }
    return sf::Vector2u(maxWidth, maxHeight);
}

void SpriteDrawable::alpha(int alpha)
{
    _alpha = alpha;    
    for(auto & sprite : _sprites)
    {
        sf::Color col(sprite->getColor());
        col.a = alpha;
        sprite->setColor(col);
    }
}
