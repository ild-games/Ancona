#ifndef Ancona_Engine_Core_Game_H_
#define Ancona_Engine_Core_Game_H_

#include <memory>
#include <string>

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/HAL.hpp>

namespace ild
{

struct GameConfig
{
    int windowWidth = 1280;
    int windowHeight = 720;
    std::string title = "Ancona Game";
    bool isVSyncEnabled = true;
    bool isFpsLimited = true;
    float fpsLimit = 60.0f;
    float fixedUpdateFps = 60.0f;
    float minFps = 45.0f;
    bool isKeyRepeatEnabled = false;
    unsigned int style = ildhal::WindowStyle::Default;
};

class Game
{
  public:
    Game(const GameConfig &config);

    void Run();
    void RunOld();
    void InputUpdate(float deltaTime);
    void FixedUpdate(float fixedDeltaTime);
    void Render(float delta);

    virtual ~Game();

    static unsigned long FrameCount;
    static float InterpolationAlpha;

    /* getters and setters */
    const bool &windowIsActive() const
    {
        return _windowIsActive;
    }
    ScreenManager &screenManager()
    {
        return *_screenManager;
    }

  protected:
    std::unique_ptr<ScreenManager> _screenManager;
    std::unique_ptr<ildhal::Window> _window;

  private:
    const GameConfig &_config;
    bool _windowIsActive = true;
    std::shared_ptr<ildhal::Music> _music;

    void ProcessWindowEvent(ildhal::Event event);
};
} // namespace ild

#endif
