#ifndef Ancona_Engine_Screen_AbstractScreen_H_
#define Ancona_Engine_Screen_AbstractScreen_H_

#include <memory>
#include <string>

#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>

namespace ild
{

/**
 * @brief  Base definition for a Screen
 *
 * @author Tucker Lein
 */
class AbstractScreen 
{
    public:
        /**
         * @brief Creates a new screen.
         *
         * @param key Key to identify the screen.
         * @param screenManager ScreenManager instance used by the game.
         */
        AbstractScreen(
                std::string key,
                ScreenManager & screenManager);

        /**
         * @brief Destructor for AbstractScreen.
         */
        virtual ~AbstractScreen();

        /**
         * @brief Can be overridden to initialize the screen.  
         * Will be called just before Update is called for the
         * first time.
         */
        virtual void Init() { }

        /**
         * @brief Handles the update logic on the screen
         *
         * @param delta Seconds since last update.
         */
        virtual void Update(float delta) = 0;

        /**
         * @brief Handles the draw logic on the screen
         *
         * @param delta Seconds since last draw.
         */
        virtual void Draw(float delta) = 0;

        /**
         * @brief Code to run while the screen is entering. Defaults to screen transitions.
         *
         * @param delta time since last update.
         */
        virtual void Entering(float delta);

        /**
         * @brief Code to run while the screen is exiting. Defaults to screen transitions.
         *
         * @param delta time since last update.
         */
        virtual void Exiting(float delta);

        /**
         * @brief Used by the ScreenManager to call the Init
         * function at the correct time.
         */
        bool __Initialized;

        /**
         * @brief Used to determine if the screen is still in a state of entering.
         */
        bool __Entering;

        /**
         * @brief Used to determine if the screen is still in a state of exiting.
         */
        bool __Exiting;

        /* getters and setters */
        std::string GetKey() { return KEY; }
        void SetRequestList(std::shared_ptr<RequestList> requestList) { _requestList = requestList; }
        virtual ScreenSystemsContainer * GetSystemsContainer() = 0;
    protected:
        /**
         * @brief Manages all the screens in the game
         */
        ScreenManager & _screenManager;
        /**
         * @brief key to identify the screen.
         */
        const std::string KEY;
        /**
         * @brief Color of the default transition.
         */
        sf::Color _transitionColor;
        /**
         * @brief Rectangle used to create the default transition.
         */
        sf::RectangleShape _transitionRect;
        /**
         * @brief Speed the default transition happens at.
         */
        float TRANSITION_SPEED = 650.0f;
        /**
         * @brief The default camera used when the window is first spawned.
         */
        const sf::View _defaultCam;
        /**
         * @brief Request list used by this screen.
         */
        std::shared_ptr<RequestList> _requestList;
        
};

}

#endif
