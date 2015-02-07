#ifndef Test_Prototype_FlappyBirdTest_Systems_PointComponent_H_
#define Test_Prototype_FlappyBirdTest_Systems_PointComponent_H_

namespace ild
{

/**
 * @brief Sets the points scored in the game.
 *
 * @author Tucker Lein
 */
class PointComponent
{
    public:
        /**
         * @brief Create a point component.
         */
        PointComponent();

        /**
         * @brief Adds a point to _points.
         */
        void AddPoint();
    private:
        /**
         * @brief Points the player has in the game.
         */
        int _points;
};

}

#endif
