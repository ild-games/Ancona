#include <Ancona/Core2D/Core/Game.hpp>
#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include <Ancona/Core2D/InputDevices/Keyboard.hpp>

using namespace ild;

Game::Game(int windowWidth, int windowHeight, const std::string & title) 
    : _window(sf::VideoMode(windowWidth, windowHeight), title)
{
    _screenManager = new ScreenManager(_window);
}

void Game::Run()
{
    sf::Clock clock;
    _window.setFramerateLimit(60);
    _window.setKeyRepeatEnabled(false);
    while(_window.isOpen() && !_screenManager->Empty())
    {
        sf::Event event;
        Keyboard::_ClearKeys(); 
        while(_window.pollEvent(event))
        {

            if(event.type == sf::Event::Closed)
            {
                _window.close();
            }
            if(event.type == sf::Event::KeyPressed)
            {
                Keyboard::_AddKeyPress(event.key.code); 
            }
            if(event.type == sf::Event::KeyReleased)
            {
                Keyboard::_AddKeyRelease(event.key.code);
            }
        }

        sf::Time elapsed = clock.restart();
        float delta = elapsed.asSeconds();
        _screenManager->Update(delta);
            
        _window.clear(sf::Color::Black);
        _screenManager->Draw(delta);
        _window.display();
    }
}
