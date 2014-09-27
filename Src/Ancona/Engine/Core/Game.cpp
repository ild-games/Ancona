#include <Ancona/Engine/Core/Game.hpp>
#include <Ancona/Engine/Screen/ScreenManager.hpp>

using namespace ild;

Game::Game(int windowWidth, int windowHeight, const std::string & title) 
    : _window(sf::VideoMode(windowWidth, windowHeight), title)
{
    _screenManager = new ScreenManager(_window);
}

void Game::Run()
{
    sf::Clock clock;
    while(_window.isOpen())
    {
        sf::Event event;
        while(_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                _window.close();
            }
        }

        sf::Time elapsed = clock.restart();
        _screenManager->Update(elapsed.asSeconds());
            
        _window.clear(sf::Color::Blue);
        _screenManager->Draw();
        _window.display();
    }
}
