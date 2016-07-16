#ifndef Ancona_Engine_Core_Systems_ImageDrawable_H_
#define Ancona_Engine_Core_Systems_ImageDrawable_H_

#include <memory>

#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

/**
 * @brief A drawable which can display either a whole image or a portion of an image.
 *
 * @author Tucker Lein
 */
class ImageDrawable : public Drawable
{
    public:
        /**
         * @brief Blank constructor needed for serializing.
         */
        ImageDrawable() { }

        /**
         * @brief Constructs an ImageDrawable
         */
		ImageDrawable(
			std::string textureKey,
			const int priority,
			const std::string & key,
			bool isWholeImage = true,
			Box2 textureRect = Box2(sf::Vector2f(0, 0), sf::Vector2f(0, 0)),
			int priorityOffset = 0,
			sf::Vector2f positionOffset = sf::Vector2f(0, 0));

        /**
         * @brief Constructs an ImageDrawable
         */
        ImageDrawable(
			sf::Texture * texture,
			const int priority,
			const std::string & key,
			bool isWholeImage = true,
			Box2 textureRect = Box2(sf::Vector2f(0, 0), sf::Vector2f(0, 0)),
			int priorityOffset = 0,
			sf::Vector2f positionOffset = sf::Vector2f(0, 0));

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc) override;

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity) override;

        /* getters and setters */
        sf::Vector2f size() override;
        void alpha(int newAlpha) override;
        int alpha() override;
    private:
        std::string _textureKey = "";
        Box2 _textureRect;
        sf::Texture * _texture = nullptr;
        bool _isWholeImage;
        std::unique_ptr<sf::Sprite> _sprite;

        void OnDraw(sf::RenderWindow &window, sf::Transform transform, float delta) override;
        void SetupSprite();
};

}

#endif
