#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <Ancona/Graphics/Color.hpp>
#include <Ancona/Graphics/View.hpp>
#include <Ancona/HAL/SDL/DrawableImpl.hpp>
#include <Ancona/HAL/Text.hpp>
#include <Ancona/HAL/VertexArray.hpp>

namespace ildhal
{

namespace priv
{

class TextImpl : public DrawableImpl
{
  public:
    void Draw(
        TTF_Font & sdlFont,
        SDL_Renderer & sdlRenderer,
        const ild::View & view,
        ildhal::RenderStates & renderStates);

    /* getters and setters */
    const std::string & text() const { return _text; }
    const ild::Color & fillColor() const { return _fillColor; }
    void fillColor(const ild::Color & newFillColor) { _fillColor = newFillColor; }
    void text(const std::string & newText) { _text = newText; }
    unsigned int characterSize() const { return _characterSize; }
    void characterSize(unsigned int newCharacterSize) { _characterSize = newCharacterSize; }
    void dirty(bool newDirty) { _dirty = newDirty; }
    const ild::Vector2f & dimensions() const { return _dimensions; }

  private:
    std::string _text = "";
    ild::Color _fillColor = ild::Color::Black;
    unsigned int _characterSize = 16;
    SDL_Texture * _texture;
    bool _dirty = true;
    const int NUM_VERTICES = 6;
    SDL_Vertex * _vertices;

    // default to non-zero as we won't be able to calculate the dimensions until first render
    ild::Vector2f _dimensions = ild::Vector2f(1.0, 1.0f);

    bool SetupTexture(TTF_Font & sdlFont, SDL_Renderer & sdlRenderer);
    void SetupVertexArray();
    void AddVertexArrayVert(int index, const ild::Vector2f & vertexNormalizedPosition);
};

} // namespace priv

} // namespace ildhal
