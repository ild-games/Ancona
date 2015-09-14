#ifndef Ancona_Engine_Core_Systems_ContainerDrawable_H_
#define Ancona_Engine_Core_Systems_ContainerDrawable_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>

namespace ild
{

/**
 * @brief A drawable that contains a list of other drawables.
 *
 * @author Tucker Lein
 */
class ContainerDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        ContainerDrawable() {}

        ContainerDrawable(
                const int priority,
                int priorityOffset,
                sf::Vector2f positionOffset);

        void Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta);

        void Serialize(Archive & arc);

        void FetchDependencies(const Entity & entity);

        sf::Vector2u size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        std::vector<std::unique_ptr<Drawable>> _drawables;
        sf::RenderTexture _renderTexture;
};

}

#endif
