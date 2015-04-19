#ifndef Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_
#define Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>
#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

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

        void GoDirection(int direction);
        void Move(int direction);
        void Jump();

    private:
        VectorActionProxy action;
        VectorActionProxy jumpAction;
        PlatformPhysicsComponent & _physics;
        int lastDir = 0;
        bool _isOnGround;
};

}

#endif
