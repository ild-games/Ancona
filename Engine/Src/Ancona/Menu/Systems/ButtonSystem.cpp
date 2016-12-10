#include <sstream>

#include "ButtonSystem.hpp"

using namespace ildmenu;

ButtonStateEnum GetNextButtonState(ButtonStateEnum currentState, PointerStateEnum pointerState, bool mouseIsOver);
PointerStateEnum GetNextPointerState(bool isDown, PointerStateEnum previousState);
std::string GetButtonStateTitle(ButtonStateEnum buttonState);


/* Component */
ButtonComponent::ButtonComponent()
{
}

void ButtonComponent::Update(float delta, const ild::Box2 & position, PointerStateEnum pointerState)
{

    // Implement component logic here
    auto mouseIsOver = position.Intersects(_collisionComponent->box());
    auto initalState = _buttonState;
    _buttonState = GetNextButtonState(_buttonState, pointerState, mouseIsOver);


    if (initalState != _buttonState)
    {
        //TODO Gaurd against null with asserts

        if (auto rootDrawable = _drawableComponent->topDrawable())
        {
            if (auto previous = rootDrawable->FindDrawable(GetButtonStateTitle(initalState)))
            {
                previous->inactive(true);
            }

            if (auto next = rootDrawable->FindDrawable(GetButtonStateTitle(_buttonState)))
            {
                next->inactive(false);
            }
        }
    }
}

bool ButtonComponent::WasClicked()
{
    return _buttonState == ButtonState::Clicked;
}

std::string GetButtonStateTitle(ButtonStateEnum buttonState)
{
    switch (buttonState)
    {
        case ButtonState::Clicked:
            return "pressed";
            break;
        case ButtonState::Hover:
            return "hover";
            break;
        case ButtonState::Normal:
            return "normal";
            break;
        case ButtonState::Pressed:
            return "pressed";
            break;
    }
    return "unknown";
}

void ButtonComponent::Serialize(ild::Archive & arc)
{
    // Implement component serialization here
    arc.system(_collisionSystem, "collision");
    arc.system(_drawableSystem, "drawable");

    arc(_key, "key");
}

void ButtonComponent::FetchDependencies(const ild::Entity &entity)
{
    // Implement component post serialization dependency fetch here
    _collisionComponent = _collisionSystem->at(entity);
    _drawableComponent = _drawableSystem->at(entity);
}

/* System */
ButtonSystem::ButtonSystem(
        std::string name,
        ild::SystemManager &manager) :
    UnorderedSystem(name, manager, ild::UpdateStep::Update)
{
}

void ButtonSystem::Update(float delta)
{
    _pointerState = GetNextPointerState(_isDown, _pointerState);
    ild::Box2 box(_location, sf::Vector2f(1.0, 1.0));

    _pressedEntity = ild::nullentity;
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta, box, _pointerState);

        if (comp.second->WasClicked())
        {
            _pressedEntity = comp.first;
        }
    }
}

void ButtonSystem::Pointer(ild::Point location, bool isDown)
{
    _location = location;
    _isDown = isDown;
}

ButtonComponent * ButtonSystem::CreateComponent(const ild::Entity &entity)
{
    ButtonComponent * comp = new ButtonComponent();
    AttachComponent(entity, comp);
    return comp;
}

bool ButtonSystem::WasEntityPressed()
{
    return _pressedEntity != ild::nullentity;
}

ild::Entity ButtonSystem::GetPressedEntity()
{
    return _pressedEntity;
}

std::string ButtonSystem::GetPressedKey()
{
    if (WasEntityPressed()) {
        return this->at(_pressedEntity)->key();
    }
    return "";
}

PointerStateEnum GetNextPointerState(bool isDown, PointerStateEnum previousState)
{
    switch (previousState)
    {
        case PointerState::IsPressedDown:
            if (isDown)
            {
                return PointerState::IsPressedDown;
            }
            else
            {
                return PointerState::WasLetUp;
            }
        case PointerState::WasLetUp:
            if (isDown)
            {
                return PointerState::WasPressedDown;
            }
            else
            {
                return PointerState::Up;
            }
        case PointerState::WasPressedDown:
            if (isDown)
            {
                return PointerState::IsPressedDown;
            }
            else
            {
                return PointerState::WasLetUp;
            }
        case PointerState::Up:
            if (isDown)
            {
                return PointerState::WasPressedDown;
            }
            else
            {
                return PointerState::Up;
            }
    }
    return PointerState::Up; //TODO This should be an assert
}

ButtonStateEnum GetNextButtonState(ButtonStateEnum currentState, PointerStateEnum pointerState, bool mouseIsOver)
{
    switch (pointerState)
    {
        case PointerState::Up:
            if (mouseIsOver)
            {
                return ButtonState::Hover;
            }
            else
            {
                return ButtonState::Normal;
            }
            break;
        case PointerState::WasLetUp:
            if (mouseIsOver && currentState == ButtonState::Pressed)
            {
                return ButtonState::Clicked;
            }
            else if (mouseIsOver)
            {
                return ButtonState::Hover;
            }
            else
            {
                return ButtonState::Normal;
            }
            break;
        case PointerState::WasPressedDown:
            if (mouseIsOver)
            {
                return ButtonState::Pressed;
            }
            else
            {
                return ButtonState::Normal;
            }
            break;
        case PointerState::IsPressedDown:
            return currentState;
            break;
    }
    //TODO add assert
    return currentState;
}
