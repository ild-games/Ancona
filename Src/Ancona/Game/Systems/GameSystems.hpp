#ifndef Ancona_Game_Systems_GameSystems_H_
#define Ancona_Game_Systems_GameSystems_H_

#include <SFML/Graphics.hpp>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>
#include <Ancona/Engine/Core/Systems/SpriteSystem.hpp>
#include <Ancona/Game/Systems/KeyboardPlayerSystem.hpp>

namespace ild
{

/**
 * @brief GameSystems is used as a factory and a container for all 
 * the systems used for gameplay.
 */
class GameSystems
{
    public:
        GameSystems(sf::RenderWindow & window);

        SystemManager * Manager;
        PositionSystem * Position;
        SpriteSystem * Sprite;
        KeyboardPlayerSystem * KeyboardPlayer;
};

}
#endif
