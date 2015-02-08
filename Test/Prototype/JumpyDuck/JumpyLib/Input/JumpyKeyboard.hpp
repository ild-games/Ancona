#ifndef Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_
#define Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_

#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Engine/Core/Systems/InputControlComponent.hpp>
#include <Ancona/Engine/InputDevices/InputHandler.hpp>
#include <Ancona/Engine/Core/Systems/Physics/PlatformPhysicsSystem.hpp>

#include <SFML/Window.hpp>

namespace ild
{

class JumpyInputComponent;


class JumpyKeyboard : public InputHandler
{
    public:
        void RegisterInputComponent(JumpyInputComponent * component);

        void HandleInput();
    private:
        JumpyInputComponent * _playerComponent;
};

class JumpyInputComponent : public InputControlComponent
{
    public:
        JumpyInputComponent(const Entity & player, PlatformPhysicsComponent & physicsComponent, JumpyKeyboard & inputHandler);

        void GoLeft();
        void GoRight();
        void GoUp();
        void GoDown();

    private:
        VectorActionProxy action;
};

}

#endif
