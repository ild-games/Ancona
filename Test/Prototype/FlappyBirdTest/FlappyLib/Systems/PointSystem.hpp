#ifndef Test_Prototype_FlappyBirdTest_Systems_PointSystem_H_
#define Test_Prototype_FlappyBirdTest_Systems_PointSystem_H_

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include "PointComponent.hpp"

namespace ild
{

/**
 * @brief System for handling the point component.
 *
 * @author Tucker Lein
 */
class PointSystem : public UnorderedSystem<PointComponent>
{
    public:
        /**
         * @brief Construct the system with the screen's SystemManager.
         *
         * @param manager SystemManager for the screen.
         */
        PointSystem(SystemManager & manager);

        /**
         * @brief Calls the update on the connected components.
         *
         * @param delta Seconds since last update.
         */
        void Update(float delta);

        /**
         * @brief Create and attach a point component associated with the passed in entity.
         *
         * @param entity Entity that the component is associated with.
         *
         * @return The PointComponent made.
         */
        PointComponent * CreateComponent(const Entity & entity);
};

}

#endif
