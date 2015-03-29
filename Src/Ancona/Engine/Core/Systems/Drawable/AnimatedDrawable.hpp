#ifndef Ancona_Engine_Core_Systems_AnimatedDrawable_H_
#define Ancona_Engine_Core_Systems_AnimatedDrawable_H_

#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>

namespace ild
{

/**
 * @brief Responsible for drawing an animated sprite to the window.
 *
 * @author Tucker Lein
 */
class AnimatedDrawable : public SpriteDrawable
{
    public:
        AnimatedDrawable() {}

        /**
         * @brief Constructs an AnimatedDrawable
         *
         * @param physicsSystem Physics system used to determine the entitie's location.
         * @param textureKey Key of the texture used for the animation.
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param frameDimensions Dimensions of a frame in the animated texture.
         * @param numFrames Number of frames in the animation.
         * @param duration Seconds per frame.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from the DrawableComponent's position.
         */
        AnimatedDrawable(
                BasePhysicsSystem * physicsSystem,
                const std::string textureKey,
                const int priority,
                sf::Vector2f frameDimensions,
                int numFrames,
                float duration,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the animated sprite to the window. 
         *
         * @param window RenderWindow for the game.
         */
        void Draw(sf::RenderWindow & window, float delta);

        void FetchDependencies(const Entity & entity);
        void Serialize(Archive & archive);
    private:
        /**
         * @brief Dimensions of a frame in the animated texture.
         */
        sf::Vector2f _frameDimensions;
        /**
         * @brief Seconds per frame.
         */
        float _duration;
        /**
         * @brief time until the frame changes.
         */
        float _timeUntilChange;
        /**
         * @brief Number of frames in the animation.
         */
        int _numFrames;
        /**
         * @brief The current frame being shown.
         */
        int _curFrame = 0;
        /**
         * @brief Advances the frame.
         */
        void AdvanceFrame();
        

};

}

#endif
