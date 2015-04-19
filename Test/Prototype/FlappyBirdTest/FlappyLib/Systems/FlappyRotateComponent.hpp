#ifndef Test_Prototype_FlappyBirdTest_Systems_FlappyRotateComponent_H_
#define Test_Prototype_FlappyBirdTest_Systems_FlappyRotateComponent_H_

#include <Ancona/Framework/Core/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/Core/Systems/PositionSystem.hpp>


namespace ild
{

/**
 * @brief  Sets the current rotation of a flappy bird.
 *
 * @author Tucker Lein
 */
class FlappyRotateComponent
{
    public:
        /**
         * @brief Create a component with the given SpriteComponent and PositionComponent
         *
         * @param drawable DrawableComponent of the flappy bird
         * @param position PositionComponent of the flappy bird
         */
        FlappyRotateComponent(
                DrawableComponent & drawable,
                PositionComponent & position);

        /**
         * @brief Updates the rotation of the sprite based on the current rotation and position 
         *        of the flappy bird.
         */
        void Update(float delta);

        /* getters and setters */
        int GetRotateDir() { return _rotateDir; }
        void SetRotateDir(int rotateDir) { _rotateDir = rotateDir; }
    private:
        /**
         * @brief The sprite component for the flappy bird.
         */
        DrawableComponent & _drawableComponent;

        /**
         * @brief The position component for the flappy bird.
         */
        PositionComponent & _positionComponent;

        /**
         * @brief Determines the direction the flappy bird is rotating.
         *        -1 means it is rotating counter clockwise (backwards)
         *        1 means it is rotating clockwise (forwards)
         */
        int _rotateDir;

        /**
         * @brief Speed at which the flappy bird rotates, note the backwords rotation will be three times as fast.
         */
        const float ROTATE_SPEED = 125.0f;
};

}

#endif

