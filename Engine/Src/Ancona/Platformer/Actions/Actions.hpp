#ifndef Ancona_Platformer_Physiscs_Actions_hpp
#define Ancona_Platformer_Physiscs_Actions_hpp

#include <limits>
#include <memory>
#include <vector>

#include <Ancona/Core2D/Systems/Position/PositionSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

#include "ValueAction.hpp"
#include "ScaleAction.hpp"

namespace ild
{

namespace ActionDuration
{

const float PERSISTENT = std::numeric_limits<float>::infinity();
const float INSTANT = 0.0f;

}

typedef std::shared_ptr<ValueAction<sf::Vector2f>> VectorActionProxy;
typedef std::shared_ptr<ScaleAction<sf::Vector2f>> ScaleActionProxy;

/**
 * @brief Actions is used to contain all of the Actions that are effecting
 * an entity.  It also contains the logic for applying and updating the actions.
 * @author Jeff Swenson
 */
class Actions
{
    public:
        /**
         * @brief Default constructor that should only be used for serialization.
         */
        Actions() {}

        /**
         * @brief Construct a container for actions.
         *
         * @param positionSystem Action system that the actions belong to.
         */
        Actions(
            PositionSystem * positionSystem,
            DrawableSystem * drawableSystem);

        /**
         * @brief Update the position based on inactive Actions in
         * the object.
         */
        void Apply(
            PositionComponent & position, 
            DrawableComponent & drawable,
            float delta);

        /**
         * @brief Create an action for setting the position.
         *
         * @return A proxy to the position Action.
         */
        VectorActionProxy CreatePositionAction();

        /**
         * @brief Create an action for setting the velocity.
         *
         * @return A proxy to the velocity Action.
         */
        VectorActionProxy CreateVelocityAction();
        VectorActionProxy CreateScaleAction(std::string drawableKey = "");

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(Archive & arc);

        void position(PositionSystem * positionSystem) { _positionSystem = positionSystem; }
        void drawable(DrawableSystem * drawableSystem) { _drawableSystem = drawableSystem; }

    private:
        std::vector<VectorActionProxy> _positionActions;
        std::vector<VectorActionProxy> _velocityActions;
        std::vector<ScaleActionProxy> _scaleActions;
        Point _actionVelocity;
        PositionSystem * _positionSystem;
        DrawableSystem * _drawableSystem;

        template<typename T>
        void RemoveDoneActions(std::vector<T> & actions)
        {
            actions.erase(
                alg::remove_if(
                    actions,
                    [](T & action) { return action->Done(); }
                    ),
                actions.end()
                );
        }

        Point ApplyPositionActions(const PositionComponent & position, float delta);
        Point ApplyVelocityActions(const PositionComponent & position, float delta);
        void ApplyScaleActions(DrawableComponent & drawable, float delta);
};

}
#endif
