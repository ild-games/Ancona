#ifndef Ancona_Engine_Core_Systems_DrawableSystem_H_
#define Ancona_Engine_Core_Systems_DrawableSystem_H_

#include <vector>

#include <SFML/Window.hpp>

#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>
#include <Ancona/Engine/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

namespace ild
{


/**
 * @brief Manages all DrawableComponents for a screen.
 *
 * @author Tucker Lein
 */
class DrawableSystem : public UnorderedSystem<DrawableComponent>
{
    public:
        /**
         * @brief Construct the DrawableSystem.
         *
         * @param window RenderWindow for game.
         * @param systemManager SystemManager for the screen.
         * @param physicsSystem PhysicsSystem for the screen.
         */
        DrawableSystem(
                sf::RenderWindow & window,
                SystemManager & systemManager,
                BasePhysicsSystem & positionSystem);



        /**
         * @brief Draw all drawable elements to the screen.
         *
         * @param delta Ignored by the drawable system.
         */
        void Update(float delta);

        /**
         * @brief Adds a CameraComponent to the system's cameras.
         *
         * @param camera CameraComponent to add.
         */
        void AddCamera(CameraComponent * camera);

        /**
         * @brief Removes a CameraComponent from the system's cameras.
         *
         * @param camera CameraComponent to remove.
         */
        void RemoveCamera(CameraComponent * camera);

        /**
         * @brief Creates a DrawableComponent on the system.
         * @param entity Entity to attach the component to.
         * @param camera CameraComponent for the DrawableComponent.
         *
         * @return Pointer to the newly created DrawableComponent.
         */
        DrawableComponent * CreateComponent(
                const Entity & entity,
                CameraComponent & camera);

    protected:
        /**
         * @see ild::SystemManager::OnComponentRemove(Entity, ComponentType*)
         */
        void OnComponentRemove(Entity entity, DrawableComponent * component);

    private:
        /**
         * @brief The window the sprite system will draw to.
         */
        sf::RenderWindow & _window;
        /**
         * @brief The system used to determine where an entity should be drawn.
         */
        BasePhysicsSystem & _physicsSystem;
        /**
         * @brief Holds pointers to the camera components sorted by priority
         */
        std::vector<CameraComponent *> _cameras;
};


}

#endif
