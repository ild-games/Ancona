#ifndef Ancona_Menu_Systems_ButtonSystem_H_
#define Ancona_Menu_Systems_ButtonSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>

namespace ildmenu
{

namespace ButtonState
{
    enum State
    {
        Pressed,
        Hover,
        Normal,
        Clicked
    };
}
typedef ButtonState::State ButtonStateEnum;

namespace PointerState
{
    enum State
    {
        Up,
        WasPressedDown,
        IsPressedDown,
        WasLetUp
    };
}
typedef PointerState::State PointerStateEnum;

/**
 * @brief The ButtonComponent is attached to entities that act as buttons. Button entities
 *        must have drawables attached with the keys "hover", "normal", "pressed". Those drawables
 *        will be activated and de-activated based on the state of the button.
 */
class ButtonComponent
{
    public:
        /**
         * Construct a blank ButtonComponent for serialization.
         */
        ButtonComponent();

        /**
         * @copydoc ild::CameraComponent::FetchDependencies
         */
        void FetchDependencies(const ild::Entity & entity);

        /**
         * @copydoc ild::CameraComponent::Serialize
         */
        void Serialize(ild::Archive & arc);

        /**
         * @brief Update step where the component logic happens.
         */
        void Update(float delta, const ild::Box2 & position, PointerStateEnum pointerState);

        /*
         * Returns true if the entity was clicked this update step.
         */
        bool WasClicked();
        bool IsPressed();

        /* getters and setters */
        const std::string & key() { return _key; }
        void key(const std::string & key) { _key = key; }
        bool disabled() { return _disabled; }
        void disabled(const bool & newDisabled);

    private:
        bool _disabled = false;
        std::string _key;
        ButtonStateEnum _buttonState = ButtonState::Normal;

        ild::CollisionComponent * _collisionComponent;
        ild::CollisionSystem * _collisionSystem;
        ild::DrawableSystem * _drawableSystem;
        ild::DrawableComponent * _drawableComponent;

        void ChangeDrawable(ButtonStateEnum oldState, ButtonStateEnum newState);
};

/**
 * @brief The ButtonSystem is used to implement entities that act as buttons. Consumers of the ButtonSystem should
 *        use the WasEntityPressed() method to determine when buttons are pressed. Entities will only be considered
 *        pressed for one update cycle.

          The MenuScreen handles interaction with the ButtonSystem. See its update method for an example of how to
          handle button clicks.
 */
class ButtonSystem : public ild::UnorderedSystem<ButtonComponent>
{
    public:
        /**
         * @copydoc ild::UnorderedSystem
         */
        ButtonSystem(
                std::string name,
                ild::SystemManager & manager);

        /**
         * @copydock ild::UnorderedSystem
         */
        void Update(float delta) override;

        /**
         * Check if an entity was pressed.
         * @return True if an entity was pressed, false otherwise.
         */
        bool WasEntityClicked();
        bool IsEntityPressed();

        /**
         * Determine which entity was pressed. Returns ild::nullentity when WasEntityPressed
         * returns false.
         * @return The entity that was pressed.
         */
        ild::Entity GetClickedEntity();
        ild::Entity GetPressedEntity();

        /**
         * Get the MenuKey of the pressed button.
         * @return If WasEntityPressed() returns true, this is the button key. Returns "" if no button was pressed.
         */
        std::string GetClickedKey();
        std::string GetPressedKey();

        /**
         * Called by the MenuScreen's input handler. If you are integrating this system into your own custom screen you
         * should call this every input cycle to update the systems knowledge of the pointer.
         * @param location Current location of the pointer.
         * @param isDown   True if the pointer is down/clicked. False otherwise.
         */
        void Pointer(ild::Point location, bool isDown);

        void DisableAll();
        void EnableAll();

        /**
         * Factory method for the ButtonComponent.
         * @param  entity Entity to create the button for.
         * @return        A pointer to the new component.
         */
        ButtonComponent * CreateComponent(
                const ild::Entity & entity);

        /* getters and setters */
        const ild::Point & location() { return _location; }

    private:
        ild::Entity _clickedEntity = ild::nullentity;
        ild::Entity _pressedEntity = ild::nullentity;
        ild::Point _location;
        PointerStateEnum _pointerState = PointerState::Up;
        bool _isDown = false;
};

}

#endif
