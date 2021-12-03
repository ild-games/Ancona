#ifndef Ancona_HAL_SFML_TextImpl_H_
#define Ancona_HAL_SFML_TextImpl_H_

#include <string>

#include <SFML/Graphics.hpp>

#include <Ancona/HAL/Text.hpp>
#include <Ancona/HAL/SFML/DrawableImpl.hpp>

namespace ildhal
{

namespace priv
{

class TextImpl : public DrawableImpl
{
    public:
        TextImpl();
        TextImpl(
            const std::string& string,
            const sf::Font& font,
            unsigned int characterSize = 30);

        /* getters and setters */
        void underlyingSfmlString(const std::string& string);
        const std::string& underlyingSfmlString() const;

        sf::Text & sfmlText() const;

    private:
        std::string _underlyingSfmlString;
};

}

}

#endif
