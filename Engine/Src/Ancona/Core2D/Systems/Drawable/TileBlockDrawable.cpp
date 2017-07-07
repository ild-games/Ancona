#include <Ancona/Core2D/Systems/Drawable/TileBlockDrawable.hpp>

REGISTER_POLYMORPHIC_SERIALIZER(ild::TileBlockDrawable);

using namespace ild;

Drawable * TileBlockDrawable::Copy() {
    auto drawable = new TileBlockDrawable();
    Drawable::CopyProperties(drawable);
    drawable->textureKey(_textureKey);
    drawable->size(_size);
    drawable->InitializeImages();
    return drawable;
}

void TileBlockDrawable::OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) {
    for (auto const & imageDrawable : _imageDrawables) {
        imageDrawable->Draw(window, drawableTransform, delta);
    }
}

void TileBlockDrawable::Serialize(Archive & arc) {
    Drawable::Serialize(arc);
    arc(_textureKey, "textureKey");
    arc(_size, "size");
}

void TileBlockDrawable::FetchDependencies(const Entity &entity) {
    Drawable::FetchDependencies(entity);
    InitializeImages();
}

void TileBlockDrawable::InitializeImages() {
    if (_textureKey != "") {
        auto texture = ResourceLibrary::Get<sf::Texture>(_textureKey);
        _tileSize = sf::Vector2f(texture->getSize().x / 4, texture->getSize().y / 4);
        _numTiles = sf::Vector2f(_size.x / _tileSize.x, _size.y / _tileSize.y);
        SetupImages(texture->copyToImage());
    }
}

void TileBlockDrawable::SetupImages(sf::Image image) {
    if (_numTiles.x > 1 && _numTiles.y > 1) {
        _imageDrawables.emplace_back(topLeftDrawable(image));
        _imageDrawables.emplace_back(topRightDrawable(image));
        _imageDrawables.emplace_back(bottomLeftDrawable(image));
        _imageDrawables.emplace_back(bottomRightDrawable(image));
    }

    if (_numTiles.x > 2 && _numTiles.y > 1) {
        _imageDrawables.emplace_back(topDrawable(image));
        _imageDrawables.emplace_back(bottomDrawable(image));
    }
    if (_numTiles.y > 2 && _numTiles.x > 1) {
        _imageDrawables.emplace_back(leftDrawable(image));
        _imageDrawables.emplace_back(rightDrawable(image));
    }

    if (_numTiles.x > 2 && _numTiles.y > 2) {
        _imageDrawables.emplace_back(centerDrawable(image));
    }

    if (_numTiles.y > 1 && _numTiles.x == 1) {
        _imageDrawables.emplace_back(topCapDrawable(image));
        _imageDrawables.emplace_back(bottomCapDrawable(image));
    }

    if (_numTiles.x > 1 && _numTiles.y == 1) {
        _imageDrawables.emplace_back(leftCapDrawable(image));
        _imageDrawables.emplace_back(rightCapDrawable(image));
    }

    if (_numTiles.y > 2 && _numTiles.x == 1) {
        _imageDrawables.emplace_back(verticalCenterDrawable(image));
    }

    if (_numTiles.x > 2 && _numTiles.y == 1) {
        _imageDrawables.emplace_back(horizontalCenterDrawable(image));
    }

    if (_numTiles.y == 1 && _numTiles.x == 1) {
        _imageDrawables.emplace_back(singleDrawable(image));
    }
}

sf::Texture * TileBlockDrawable::createTexture() {
    auto texture = new sf::Texture();
    _generatedTextures.emplace_back(texture);
    return texture;
}

ImageDrawable * TileBlockDrawable::topLeftDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(0, 0, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_topLeft");
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::topRightDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 2, 0, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_topRight");
    drawable->anchor(sf::Vector2f(-(_numTiles.x - 1), 0));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::bottomLeftDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(0, _tileSize.y * 2, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_bottomLeft");
    drawable->anchor(sf::Vector2f(0, -(_numTiles.y - 1)));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::bottomRightDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 2, _tileSize.y * 2, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_bottomRight");
    drawable->anchor(sf::Vector2f(-(_numTiles.x - 1), -(_numTiles.y - 1)));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::topDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x, 0, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_top");
    auto width = _tileSize.x * (_numTiles.x - 2);
    drawable->anchor(sf::Vector2f(-(_tileSize.x / width), 0));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(width, _tileSize.y));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::bottomDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x, _tileSize.y * 2, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_bottom");
    auto width = _tileSize.x * (_numTiles.x - 2);
    drawable->anchor(sf::Vector2f(-(_tileSize.x / width), -(_numTiles.y - 1)));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(width, _tileSize.y));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::leftDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(0, _tileSize.y, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_left");
    auto height = _tileSize.y * (_numTiles.y - 2);
    drawable->anchor(sf::Vector2f(0, -(_tileSize.y / height)));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(_tileSize.x, height));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::rightDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 2, _tileSize.y, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_right");
    auto height = _tileSize.y * (_numTiles.y - 2);
    drawable->anchor(sf::Vector2f(-(_numTiles.x - 1), -(_tileSize.y / height)));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(_tileSize.x, height));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::centerDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x, _tileSize.y, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_center");
    auto width = _tileSize.x * (_numTiles.x - 2);
    auto height = _tileSize.y * (_numTiles.y - 2);
    drawable->anchor(sf::Vector2f(-(_tileSize.x / width), -(_tileSize.y / height)));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(width, height));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::topCapDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 3, 0, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_topCap");
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::bottomCapDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 3, _tileSize.y * 2, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_bottomCap");
    drawable->anchor(sf::Vector2f(0, -(_numTiles.y - 1)));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::leftCapDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(0, _tileSize.y * 3, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_leftCap");
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::rightCapDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 2, _tileSize.y * 3, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_right");
    drawable->anchor(sf::Vector2f(-(_numTiles.x - 1), 0));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::verticalCenterDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 3, _tileSize.y, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_center");
    auto width = _tileSize.x * (_numTiles.x - 2);
    auto height = _tileSize.y * (_numTiles.y - 2);
    drawable->anchor(sf::Vector2f(0, -(_tileSize.y / height)));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(_tileSize.x, height));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::horizontalCenterDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x, _tileSize.y * 3, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_center");
    auto width = _tileSize.x * (_numTiles.x - 2);
    auto height = _tileSize.y * (_numTiles.y - 2);
    drawable->anchor(sf::Vector2f(-(_tileSize.x / width), 0));
    drawable->isTiled(true);
    drawable->tiledArea(sf::Vector2f(width, _tileSize.y));
    drawable->SetupSprite(texture);
    return drawable;
}

ImageDrawable * TileBlockDrawable::singleDrawable(sf::Image image) {
    auto texture = createTexture();
    texture->loadFromImage(image, sf::IntRect(_tileSize.x * 3, _tileSize.y * 3, _tileSize.x, _tileSize.y));
    auto drawable = new ImageDrawable(_renderPriority, _key + "_center");
    drawable->SetupSprite(texture);
    return drawable;
}

/* getters and setters */
int TileBlockDrawable::alpha() {
    if (_imageDrawables.size() == 0) {
        return 0;
    }

    return _imageDrawables[0]->alpha();
}

void TileBlockDrawable::alpha(int newAlpha) {
    for (auto const & imageDrawable : _imageDrawables) {
        imageDrawable->alpha(newAlpha);
    }
}
