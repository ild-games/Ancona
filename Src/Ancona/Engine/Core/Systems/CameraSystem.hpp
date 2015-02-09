#ifndef Ancona_Engine_Core_Systems_CameraSystem_H_
#define Ancona_Engine_Core_Systems_CameraSystem_H_

#include <Ancona/Engine/Core/Systems/PositionComponent.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>

#include <SFML/Graphics.hpp>

namespace ild
{

/**
 * @brief Used to manage a camera's attributes.
 *
 * @author Tucker Lein
 */
class CameraComponent
{
    public:
        /**
         * @brief Constructs a new CameraComponent.
         *
         * @param cameraPosition Position component for the camera.
         * @param followPosition Position component for what the camera is following.
         */
        CameraComponent(
                PositionComponent & cameraPosition,
                PositionComponent & followPosition);

        /**
         * @brief Updates the position of the camera.
         */
        void Update(float delta);

    private:
        /**
         * @brief SFML view for actually applying the camera's position on the window.
         */
        sf::View * _view;
        /**
         * @brief Position component for the camera.
         */
        PositionComponent & _cameraPosition;

        /**
         * @brief Position component for what the camera is following.
         */
        PositionComponent & _followPosition;

};

/**
 * @brief System for managing CameraComponents
 *
 * @author Tucker Lein
 */
class CameraSystem : public UnorderedSystem<CameraComponent>
{
    public:
        /**
         * @brief Constructs the CameraSystem.
         *
         * @param manager SystemManager instance for the current screen.
         */
        CameraSystem(SystemManager & manager);

        /**
         * @brief Updates the components managed by the system.
         */
        void Update(float delta);

        /**
         * @brief Constructs a CameraComponent and attaches it to the system.
         *
         * @param entity Entity to associate the component with.
         * @param cameraPosition Position component for the camera.
         * @param followPosition Position component for what the camera is following.
         *
         * @return Pointer to the CameraComponent being created.
         */
        CameraComponent * CreateComponent(
                const Entity & entity,
                PositionComponent & cameraPosition,
                PositionComponent & followPosition);

};

}

#endif
