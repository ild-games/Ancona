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
        /**
         * @brief Constructs an AnimatedDrawable
         *
         * @param positionComponent PositionComponent for the entity associated with this drawable element.
         * @param textureKey Key of the texture used for the animation.
         * @param priority RenderPriority that determines when the drawable obj is rendered.
         * @param frameDimensions Dimensions of a frame in the animated texture.
         * @param numFrames Number of frames in the animation.
         * @param speed Speed of the animation.
         * @param xGap Gap between frames in the x dimension, defaults to 0.
         * @param yGap Gap between frames in the y dimension, defaults to 0.
         * @param priorityOffset Optional offset to the render priority.
         * @param positionOffset Vector that defines the offset from the DrawableComponent's position.
         */
        AnimatedDrawable(
                const PositionComponent & positionComponent, 
                const std::string textureKey,
                const RenderPriorityEnum priority,
                sf::Vector2f frameDimensions,
                int numFrames,
                int speed,
                float xGap = 0,
                float yGap = 0,
                int priorityOffset = 0,
                sf::Vector2f positionOffset = sf::Vector2f(0.0f, 0.0f));

        /**
         * @brief Draws the animated sprite to the window. 
         *
         * @param window RenderWindow for the game.
         */
        void Draw(sf::RenderWindow & window);

    private:
        /**
         * @brief Dimensions of a frame in the animated texture.
         */
        sf::Vector2f _frameDimensions;
        /**
         * @brief Gap between frames in the x dimension.
         */
        float _xGap;
        /**
         * @brief Gap between frames in the y dimension.
         */
        float _yGap;
        /**
         * @brief Frames an animation is shown.
         */
        int _speed;
        /**
         * @brief Original amount of frames to show the animation for.
         */
        const int SPEED_CAP;
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
