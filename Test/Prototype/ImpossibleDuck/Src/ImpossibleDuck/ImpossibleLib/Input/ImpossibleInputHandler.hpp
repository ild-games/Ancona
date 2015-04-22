#ifndef Test_Prototype_ImpossibleDuck_Input_ImpossibleInputHandler_H_
#define Test_Prototype_ImpossibleDuck_Input_ImpossibleInputHandler_H_

#include <SFML/Window.hpp>

#include <Ancona/Core2D/InputDevices/InputHandler.hpp>
#include <Ancona/Core2D/Systems/InputControlComponent.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Platformer/Physics/PlatformPhysicsSystem.hpp>
#include "../Systems/ImpossibleGameSystems.hpp"

namespace ild
{

class ImpossibleGameSystems;
class ImpossibleInputComponent;


enum direction {
    UP, RIGHT, DOWN, LEFT, NO_DIR
};

class ImpossibleInputHandler : public InputHandler
{
    public:
        void RegisterInputComponent(ImpossibleInputComponent * component);

        virtual void HandleInput() { };
        
        /* getters and setters */
        void systems(ImpossibleGameSystems * systems) { _systems = systems; }
    protected:
        ImpossibleInputComponent * _playerComponent;
        ImpossibleGameSystems * _systems;
};

class ImpossibleInputComponent : public InputControlComponent
{
    public:
        ImpossibleInputComponent(
                const Entity & player,
                ImpossibleGameSystems & systems,
                ImpossibleInputHandler & inputHandler);

        void GoDirection(int direction);
        void Move(int direction);
        void Jump();

    private:
        VectorActionProxy action;
        VectorActionProxy jumpAction;
        PlatformPhysicsComponent & _physics;
        ImpossibleGameSystems & _systems;
        Entity _playerEntity;
        int lastDir = 0;
        bool _isOnGround;
};

}

#endif
