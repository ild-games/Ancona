#ifndef Anona_Menu_Systems_MenuGameSystems_H_
#define Anona_Menu_Systems_MenuGameSystems_H_

#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/RotateSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Core2D/Systems/InputControlSystem.hpp>
#include <Ancona/Core2D/Systems/Collision/CollisionSystem.hpp>
#include <Ancona/Core2D/Systems/Audio/SoundSystem.hpp>
#include <Ancona/Core2D/Systems/Audio/MusicSystem.hpp>
#include <Ancona/Framework/EntityFramework/SystemManager.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Platformer/Actions/ActionSystem.hpp>

#include "../Systems/ButtonSystem.hpp"

namespace ildmenu
{

/**
 * @brief GameSystems used by the menu screen.
 */
class MenuGameSystems : public ild::ScreenSystemsContainer
{
    public:
        /**
         * @brief Constructs the game systems for menu screen.
         * @param screenManager Screen Manager for the game.
         */
        MenuGameSystems(ild::ScreenManager & screenManager);

        /* getters and setters */
        ild::DrawableSystem & drawable() { return *_drawable; }
        ild::InputControlSystem & input() { return *_input; }
        ild::PositionSystem & position() { return *_position; }
        ild::ActionSystem & action() { return *_action; }
        ild::CameraSystem & camera() { return *_camera; }
        ild::CollisionSystem & collision() { return *_collision; }
        ild::SoundSystem & sound() { return *_sound; }
        ild::MusicSystem & music() { return *_music; }
        ButtonSystem & button() { return *_button; }
        ild::CollisionType nullCollision() { return 0; }
    private:
        ild::DrawableSystem * _drawable;
        ild::InputControlSystem * _input;
        ild::PositionSystem * _position;
        ild::CameraSystem * _camera;
        ild::CollisionSystem * _collision;
        ild::ActionSystem * _action;
        ild::SoundSystem * _sound;
        ild::MusicSystem * _music;
        ButtonSystem * _button;
};

}

#endif
