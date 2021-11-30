#ifndef Ancona_Engine_Core_Game_H_
#define Ancona_Engine_Core_Game_H_

#include <memory>
#include <string>

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/HAL.hpp>

namespace ild {

class Game {
    public:
        Game(
            int windowWidth,
            int windowHeight,
            const std::string & title,
            const unsigned int & style = ildhal::WindowStyle::Default);

        void Run();

        virtual ~Game();

        static unsigned int FrameCount;

        /* getters and setters */
        const bool & windowIsActive() const { return _windowIsActive; }
        ScreenManager & screenManager() { return *_screenManager; }

    protected:
        std::unique_ptr<ScreenManager> _screenManager;

        std::unique_ptr<ildhal::Window> _window;

    private:
        void ProcessWindowEvent(ildhal::Event event);

        bool _windowIsActive = true;
    };
}

#endif
