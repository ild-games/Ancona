#ifndef Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_
#define Ancona_Engine_Core_Systems_Drawable_DrawableComponet_H_

#include <memory>

#include <SFML/Graphics.hpp>

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/Drawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Core2D/Systems/Drawable/TextDrawable.hpp>
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

        /**
         * @brief Get a drawable being handled by the component.
         *
         * @param key Key of the drawable.
         *
         * @return Drawable instance.
         */
        Drawable * GetDrawable(std::string key) { return _drawables[key].get(); }

        /**
         * @brief Get a drawable out and cast it to the preferred type.
         *
         * @tparam T Type to cast the drawable to.
         * @param key Key of the drawable
         *
         * @return Drawable with the preferred type.
         */
        template <class T> T * GetDrawable(std::string key) { return static_cast<T *>(_drawables[key].get()); }

        /* getters and setters */
        std::vector<Drawable *> keylessDrawables();
        void rotation(float newRotation);
        float rotation() { return _rotation; }
        void scale(sf::Vector2f newScale);
        const sf::Transform & transform() const { return _transform; }
        sf::Vector2u size();
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
        BasePhysicsSystem * _physicsSystem;
        BasePhysicsComponent * _physicsComponent;
        DrawableSystem * _drawableSystem;
        Entity _camEntity = nullentity;
        float _rotation = 0;
        sf::Vector2f _scale = sf::Vector2f(1.0f, 1.0f);
        float _serializedRotation = 0;
        sf::Vector2f _serializedScale = sf::Vector2f(1.0f, 1.0f);
        sf::Transform _transform;
};

}

#endif
