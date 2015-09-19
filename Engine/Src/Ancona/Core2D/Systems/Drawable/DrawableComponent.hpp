#ifndef Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_
#define Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/ContainerDrawable.hpp>
#include <Ancona/Core2D/Systems/Physics/BasePhysicsSystem.hpp>

namespace ild
{

class DrawableSystem;

/**
 * @brief Component used to draw elements on an entity.
 *
 * @author Tucker Lein
 */
class DrawableComponent
{
    public:
        /**
         * @brief Default constructor, should only be used by the serializer.
         */
        DrawableComponent();
    
        /**
         * @brief Construct a DrawableComponent.
         *
         * @param cameraComponent CameraComponent used to render these renderables.
         */
        DrawableComponent(CameraComponent * cameraComponent);

        /**
         * @brief Gets the specified drawable that is on the component.
         *
         * @param key Key for the drawable element.
         */
        Drawable * GetDrawable(const std::string & key);

        /**
         * @brief Draws the DrawableComponent
         *
         * @param window RenderWindow to draw it on
         */
        void Draw(sf::RenderWindow & window, float delta);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        Drawable * topDrawable() { return _topDrawable; }
    private:
        ContainerDrawable * _topDrawable;
        CameraComponent * _camera;
        CameraSystem * _cameraSystem;
        BasePhysicsSystem * _physicsSystem;
        BasePhysicsComponent * _physicsComponent;
        DrawableSystem * _drawableSystem;
        Entity _camEntity = nullentity;
};

}

#endif
