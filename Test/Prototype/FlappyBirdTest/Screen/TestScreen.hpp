#ifndef Ancona_Game_Screen_TestScreen_H_
#define Ancona_Game_Screen_TestScreen_H_

#include <Ancona/Engine/Screen/AbstractScreen.hpp>
#include <Ancona/Engine/EntityFramework/Entity.hpp>
#include <Ancona/Engine/Core/Systems/Collision/CollisionSystem.hpp>

namespace ild
{

class SystemManager;
class PositionSystem;
class InputControlSystem;
class SpriteSystem;
class GravitySystem;
class FlappyRotateSystem;
class PipeSpawnerSystem;
class CollisionSystem;
class PipeSpawnerComponent;
class FlappyKeyboard;

class TestScreen : public AbstractScreen
{
    public:
        TestScreen(ScreenManager & manager);

        void Update(float delta);

        void Init ();

        void Draw();

        void StopAllMovement();

        void RestartGame();
    private:
        SystemManager * _systemManager;
        PositionSystem  * _positionSystem;
        InputControlSystem * _inputSystem;
        SpriteSystem * _spriteSystem;
        GravitySystem * _gravitySystem;
        FlappyRotateSystem * _rotateSystem;
        PipeSpawnerSystem * _pipeSpawnerSystem;
        CollisionSystem * _collisionSystem;
        PipeSpawnerComponent * _pipeSpawnerComp;
        Entity _player;
        Entity _pipeSpawner;
        Entity _ground;
        Entity _bg;
        Entity _fg;
        Entity _groundWarp;
        CollisionType _pipeCollisionType;
        CollisionType _groundCollisionType;
        CollisionType _pointCollisionType;
        FlappyKeyboard * _keyboard;
        int _points = 0;
        sf::Text _pointText;
        sf::Font _font;

        void InitializeEntities();
        void CreateGround();
        void CreatePipeSpawner();
        void CreateFgBg();
        void CreatePlayer();
        
};

}

#endif

