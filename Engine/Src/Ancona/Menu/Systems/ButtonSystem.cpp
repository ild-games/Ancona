#include <sstream>

#include <Ancona/Util/Assert.hpp>
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
    if (_disabled) 
    {
        return;
    }

    // Implement component logic here
    auto mouseIsOver = position.Intersects(_collisionComponent->box());
    auto initialState = _buttonState;
    _buttonState = GetNextButtonState(_buttonState, pointerState, mouseIsOver);
    ChangeDrawable(initialState, _buttonState);
}

void ButtonComponent::ChangeDrawable(ButtonStateEnum oldState, ButtonStateEnum newState)
{
    if (oldState != newState)
    {
        if (auto rootDrawable = _drawableComponent->topDrawable())
        {
            if (auto previous = rootDrawable->FindDrawable(GetButtonStateTitle(oldState)))
            {
                previous->inactive(true);
            }

            if (auto next = rootDrawable->FindDrawable(GetButtonStateTitle(newState)))
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

bool ButtonComponent::IsPressed()
{
    return _buttonState == ButtonState::Pressed;
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
    ILD_Assert(false, "Unknown button state in GetButtonStateTitle");
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

/* getters and setters */
void ButtonComponent::disabled(const bool & newDisabled)
{
    _disabled = newDisabled; 
    auto initialState = _buttonState;
    _buttonState = ButtonStateEnum::Normal;
    ChangeDrawable(initialState, _buttonState);
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

    _clickedEntity = ild::nullentity;
    _pressedEntity = ild::nullentity;
    for (EntityComponentPair comp : *this) {
        comp.second->Update(delta, box, _pointerState);

        if (comp.second->WasClicked()) {
            _clickedEntity = comp.first;
        } else if (comp.second->IsPressed()) {
            _pressedEntity = comp.first;
        }
    }
}

void ButtonSystem::DisableAll()
{
    for (EntityComponentPair comp : *this) {
        comp.second->disabled(true);
    }
}

void ButtonSystem::EnableAll()
{
    for (EntityComponentPair comp : *this) {
        comp.second->disabled(false);
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

bool ButtonSystem::WasEntityClicked()
{
    return _clickedEntity != ild::nullentity;
}

ild::Entity ButtonSystem::GetClickedEntity()
{
    return _clickedEntity;
}

std::string ButtonSystem::GetClickedKey()
{
    if (WasEntityClicked()) {
        return this->at(_clickedEntity)->key();
    }
    return "";
}

bool ButtonSystem::IsEntityPressed()
{
    return _pressedEntity != ild::nullentity;
}

ild::Entity ButtonSystem::GetPressedEntity()
{
    return _pressedEntity;
}

std::string ButtonSystem::GetPressedKey()
{
    if (IsEntityPressed()) {
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
    ILD_Assert(false, "Unknown state reached in GetNextPointerState");
    return PointerState::Up;
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
    ILD_Assert(false, "Unknown state reached in GetNextButtonState");
    return currentState;
}
