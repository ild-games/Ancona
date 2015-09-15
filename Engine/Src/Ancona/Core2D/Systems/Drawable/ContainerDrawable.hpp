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

        /**
         * @brief Constructs a ContainerDrawable
         *
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from its parent drawable or from the BasePhysicsComponent
         *                       position if it is the top drawable.
         *
         */
        ContainerDrawable(
                const int priority,
                int priorityOffset,
                sf::Vector2f positionOffset);

        /**
         * @copydoc ild::Drawable::Draw
         */
        void Draw(sf::RenderWindow &window, sf::Transform parentTransform, float delta);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /* getters and setters */
        sf::Vector2u size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        std::vector<Drawable *> _drawables;

        void SortDrawables();
};

}

#endif
