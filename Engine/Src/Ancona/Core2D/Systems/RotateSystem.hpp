#ifndef Ancona_Engine_Core_Systems_RotateSystem_H_
#define Ancona_Engine_Core_Systems_RotateSystem_H_

#include <vector>

#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

/**
 * @brief Component to rotate a DrawableComponent and its drawables.
 *
 * @author Tucker Lein
 */
class RotateComponent
{
    public:
        /**
         * Construct a blank RotateComponent for serialization.
         */
        RotateComponent();

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
                SystemManager & manager);

        void Update(float delta);

        RotateComponent * CreateComponent(
                const Entity & entity);

};

#endif
