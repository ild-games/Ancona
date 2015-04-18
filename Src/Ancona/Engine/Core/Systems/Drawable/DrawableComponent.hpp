#ifndef Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_
#define Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include <Ancona/Engine/Core/Systems/CameraSystem.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/Drawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Physics/BasePhysicsSystem.hpp>

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
         * @brief Adds a drawable element to the component.
         *
         * @param key Key for the drawable element on the component.
         * @param drawable Drawable being added.
         */
        void AddDrawable(
                const std::string key,
                Drawable * drawable);

        /**
         * @brief Removes a drawable from the component.
         *
         * @param key Key of the drawable.
         */
        void RemoveDrawable(const std::string key);

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /* getters and setters */
        std::vector<Drawable *> GetKeylessDrawables();
        Drawable * GetDrawable(std::string key) { return _drawables[key].get(); }
        template <class T> T * GetDrawable(std::string key) { return static_cast<T *>(_drawables[key].get()); } 
    private:
        /**
         * @brief Holds all the drawables the component controls.
         */
        std::map<std::string, std::unique_ptr<Drawable> > _drawables;
        /**
         * @brief Camera the drawables for this component are rendered with.
         */
        CameraComponent * _camera;
        CameraSystem * _cameraSystem;
        DrawableSystem * _drawableSystem;
        Entity _camEntity = nullentity;
};

}

#endif
