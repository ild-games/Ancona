#ifndef Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_
#define Test_Prototype_JumpyDuck_Input_JumpyKeyboard_H_

#include <SFML/Window.hpp>

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>

namespace ild
{

class JumpyGameSystems;
class JumpyInputComponent;

class JumpyKeyboard : public InputHandler
{
    public:
        void RegisterInputComponent(JumpyInputComponent * component);

        void HandleInput();

        /* getters and setters */
        void SetSystems(JumpyGameSystems * systems) { _systems = systems; }
    private:
        JumpyInputComponent * _playerComponent;
        JumpyGameSystems * _systems;
};

class JumpyInputComponent : public InputControlComponent
{
    public:
        JumpyInputComponent(
                const Entity & player,
                PlatformPhysicsComponent & physicsComponent,
                JumpyKeyboard & inputHandler);

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
