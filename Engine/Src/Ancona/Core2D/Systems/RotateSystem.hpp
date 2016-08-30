#ifndef Ancona_Engine_Core_Systems_RotateSystem_H_
#define Ancona_Engine_Core_Systems_RotateSystem_H_

#include <vector>

#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

class RotateSystem;

/**
 * @brief Component to rotate a DrawableComponent and its drawables.
 *
 * @author Tucker Lein
 */
class RotateComponent
{
    public:
        /**
         * @brief Initialize the rotate component
         *
         * @param rotateSystem Rotate system that the component belongs to.
         */
        RotateComponent(RotateSystem * rotateSystem);

        /**
         * Construct a blank RotateComponent for serialization.
         */
        RotateComponent() { }

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        /**
         * @brief Update step where the rotation happens.
         */
        void Update(float delta);

        /* getters and setters */
        float speed() { return _speed; }
        void speed(float speed) { _speed = speed; }
    private:
        DrawableSystem * _drawableSystem;
        DrawableComponent * _drawableComponent;
        float _speed;
        std::map<std::string, float> _drawablesSpeeds;
};

/**
 * @brief System used to create RotateComponents
 *
 * @author Tucker Lein
 */
class RotateSystem : public UnorderedSystem<RotateComponent>
{
    public:
        RotateSystem(
                std::string name,
                SystemManager & manager,
                DrawableSystem * drawableSystem);

        /**
         * @brief Update all of the components in the rotate system
         *
         * @param delta Time passed in seconds since the last update.
         */
        void Update(float delta);

        /**
         * Create a new rotate component for a given entity
         *
         * @param  entity Entity to create the rotate component for
         *
         * @return New rotate component
         */
        RotateComponent * CreateComponent(const Entity & entity);

        /* getters and setters */
        DrawableSystem * drawableSystem() { return _drawableSystem; }
    private:
        DrawableSystem * _drawableSystem;

};

}

#endif
