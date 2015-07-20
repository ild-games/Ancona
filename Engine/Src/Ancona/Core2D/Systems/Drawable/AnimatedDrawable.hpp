#ifndef Ancona_Engine_Core_Systems_AnimatedDrawable_H_
#define Ancona_Engine_Core_Systems_AnimatedDrawable_H_

#include <Ancona/Core2D/Systems/Drawable/SpriteDrawable.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing an animated sprite to the window.
 *        
 *        Note: AnimatedDrawables can use both SoloImages and TiledImages
 *        for its frames. It is highly recommended to use TiledImages 
 *        so only one texture is used for the drawable.
 *
 * @author Tucker Lein
 */
class AnimatedDrawable : public Drawable
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        AnimatedDrawable() {}

        /**
         * @brief Constructs an AnimatedDrawable
         *
         * @param physicsSystem Physics system used to determine the entity's location.
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param duration Seconds per frame.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from the DrawableComponent's position.
         */
        AnimatedDrawable(
                BasePhysicsSystem * physicsSystem,
                const int priority,
                float duration,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the animated sprite to the window. 
         *
         * @param window RenderWindow for the game.
         */
        void Draw(sf::RenderWindow & window, float delta);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /* getters and setters */
        sf::Vector2u size();
        int alpha();
        void alpha(int alpha);

    private:
        std::vector<std::unique_ptr<Image>> _frames;
        /**
         * @brief Seconds per frame.
         */
        float _duration;
        /**
         * @brief time until the frame changes.
         */
        float _timeUntilChange;
        /**
         * @brief The current frame being shown.
         */
        int _curFrame = 0;

        /**
         * @brief Ticks the animation, will switch the frame when it is time to do so.
         */
        void Tick(float delta);
        void AdvanceFrame();
};

}

#endif
