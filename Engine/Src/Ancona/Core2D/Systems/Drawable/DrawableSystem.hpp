#ifndef Ancona_Engine_Core_Systems_DrawableSystem_H_
#define Ancona_Engine_Core_Systems_DrawableSystem_H_

#include <vector>

#include <SFML/Window.hpp>

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/SerializingContext.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>

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
         * @param systemName Name of the system.
         * @param window RenderWindow for game.
         * @param systemManager SystemManager for the screen.
         */
        DrawableSystem(
                std::string systemName,
                sf::RenderWindow & window,
                SystemManager & systemManager);

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
         * @param drawable Drawable to associate with the DrawableComponent.
         *
         * @return Pointer to the newly created DrawableComponent.
         */
        DrawableComponent * CreateComponent(
                const Entity & entity,
                Drawable * topDrawable,
                PositionSystem * position);

        /**
         * @brief Creates a DrawableComponent on the system.
         * @param entity Entity to attach the component to.
         * @param drawable Drawable to associate with the DrawableComponent.
         * @param camera CameraComponent for the DrawableComponent.
         *
         * @return Pointer to the newly created DrawableComponent.
         */
        DrawableComponent * CreateComponent(
                const Entity & entity,
                Drawable * topDrawable,
                PositionSystem * position,
                CameraComponent * camera);

        /* gettes and setters */
        void defaultCamera(CameraComponent *defaultCamera);
        CameraComponent * defaultCamera() { return _defaultCamera; }
    protected:
        /**
         * @see copydoc::SystemManager::OnComponentRemove
         */
        void OnComponentRemove(Entity entity, DrawableComponent * component);

    private:
        /**
         * @brief The window the sprite system will draw to.
         */
        sf::RenderWindow & _window;
        /**
         * @brief Holds pointers to the camera components sorted by priority
         */
        std::vector<CameraComponent *> _cameras;
        /**
         * @brief Default camera to use for drawable components.
         */
        CameraComponent * _defaultCamera = nullptr;
};


}

#endif
