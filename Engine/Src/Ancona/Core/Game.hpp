#pragma once

#include <memory>
#include <string>

#include <Ancona/Core/GameConfig.hpp>
#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include <Ancona/HAL.hpp>

namespace ild
{

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

    void ProcessWindowEvent(ildhal::Event event);
};
} // namespace ild
