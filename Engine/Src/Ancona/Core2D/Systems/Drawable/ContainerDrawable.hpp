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
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));


        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::Drawable::FindDrawable
         */
        Drawable * FindDrawable(const std::string & key);

        /* getters and setters */
        sf::Vector2f size() override;
        int alpha() override;
        void alpha(int alpha) override;

    private:
        std::vector<Drawable *> _drawables;

        void SortDrawables();
        void OnDraw(sf::RenderWindow &window, sf::Transform drawableTransform, float delta) override;
};

}

#endif
