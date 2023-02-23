#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/HAL/SDL/FontImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/TextImpl.hpp>
#include <Ancona/HAL/SDL/VertexArrayImpl.hpp>
#include <Ancona/System/Log.hpp>

namespace ildhal
{

/* Pimpl Implementation */

void priv::TextImpl::Draw(
    TTF_Font & sdlFont,
    SDL_Renderer & sdlRenderer,
    const ild::View & view,
    ildhal::RenderStates & renderStates)
{
    if (_text == "" || (_dirty && !SetupTexture(sdlFont, sdlRenderer)))
    {
        return;
    }

    const ild::Transform & transform = renderStates.renderStatesImpl().transform();

    SDL_Vertex transformedVertices[NUM_VERTICES];
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        ild::Vector2f transformed = 
          view.inverseTransform() * transform.transform() * ild::Vector2f(_vertices[i].position.x, _vertices[i].position.y);

        transformedVertices[i].position.x = transformed.x;
        transformedVertices[i].position.y = transformed.y;
        transformedVertices[i].color = _vertices[i].color;
        transformedVertices[i].tex_coord = _vertices[i].tex_coord;
    }

    if (SDL_RenderGeometry(&sdlRenderer, _texture, transformedVertices, NUM_VERTICES, nullptr, 0) != 0)
    {
        ILD_Log("Failed to render VertexArray for text! SDL error: " << SDL_GetError());
    }
}

bool priv::TextImpl::SetupTexture(TTF_Font & sdlFont, SDL_Renderer & renderer)
{
    // Super weird situation here... SDL_ttf considers an alpha value of 0 to be OPAQUE and changes it to 255.
    // Don't understand why, but for now just return false so nothing gets rendered when the color is fully
    // transparent.
    if ((int) _fillColor.a == 0)
    {
        return false;
    }

    SDL_Color sdlColor;
    sdlColor.r = _fillColor.r;
    sdlColor.g = _fillColor.g;
    sdlColor.b = _fillColor.b;
    sdlColor.a = _fillColor.a;

    if (TTF_SetFontSize(&sdlFont, _characterSize) < 0)
    {
        ILD_Log("Unable to set character size of text! SDL_ttf error: " << TTF_GetError());
        return false;
    }

    SDL_Surface * textSurface = TTF_RenderText_Blended(&sdlFont, _text.c_str(), sdlColor);
    if (!textSurface)
    {
        ILD_Log("Unable to render text surface! SDL_ttf error: " << TTF_GetError());
        return false;
    }

    if (_texture != nullptr)
    {
        SDL_DestroyTexture(_texture);
    }
    _texture = SDL_CreateTextureFromSurface(&renderer, textSurface);
    if (!_texture)
    {
        ILD_Log("Unable to create texture from rendered text! SDL error: " << SDL_GetError());
        SDL_FreeSurface(textSurface);
        return false;
    }

    // Get image dimensions
    _dimensions.x = (float) textSurface->w;
    _dimensions.y = (float) textSurface->h;

    SDL_FreeSurface(textSurface);

    SetupVertexArray();

    _dirty = false;
    return true;
}

void priv::TextImpl::SetupVertexArray()
{
    _vertices = new SDL_Vertex[NUM_VERTICES];

    AddVertexArrayVert(0, ild::Vector2f(0, 0));
    AddVertexArrayVert(1, ild::Vector2f(1, 0));
    AddVertexArrayVert(2, ild::Vector2f(1, 1));
    AddVertexArrayVert(3, ild::Vector2f(1, 1));
    AddVertexArrayVert(4, ild::Vector2f(0, 0));
    AddVertexArrayVert(5, ild::Vector2f(0, 1));
}

void priv::TextImpl::AddVertexArrayVert(int index, const ild::Vector2f & vertexNormalizedPosition)
{
    SDL_FPoint vertexPosition;
    vertexPosition.x = vertexNormalizedPosition.x * _dimensions.x;
    vertexPosition.y = vertexNormalizedPosition.y * _dimensions.y;

    SDL_FPoint vertexTexPosition;
    vertexTexPosition.x = vertexNormalizedPosition.x;
    vertexTexPosition.y = vertexNormalizedPosition.y;

    SDL_Color sdlColor;
    sdlColor.r = 255;
    sdlColor.g = 255;
    sdlColor.b = 255;
    sdlColor.a = 255;

    _vertices[index].position = vertexPosition;
    _vertices[index].tex_coord = vertexTexPosition;
    _vertices[index].color = sdlColor;
}

/* HAL Interface Implementation */

Text::Text() : _fontKey(std::string())
{
    _pimpl = std::make_unique<priv::TextImpl>();
}

Text::Text(const std::string & string, const std::string & fontKey, unsigned int characterSize) : _fontKey(fontKey)
{
    _pimpl = std::make_unique<priv::TextImpl>();

    this->string(string);
    this->characterSize(characterSize);
}

void Text::Draw(ildhal::RenderTarget & renderTarget, ildhal::RenderStates & renderStates)
{
    TTF_Font & sdlFont = ild::ResourceLibrary::Get<Font>(_fontKey)->fontImpl().sdlFont();

    textImpl().Draw(
        sdlFont,
        renderTarget.renderTargetImpl().sdlRenderer(),
        renderTarget.renderTargetImpl().view(),
        renderStates);
}

/* getters and setters */

const ild::Color Text::fillColor() const
{
    return textImpl().fillColor();
}

void Text::fillColor(const ild::Color & color)
{
    if (color == textImpl().fillColor())
    {
        return;
    }

    textImpl().fillColor(color);
    textImpl().dirty(true);
}

ild::FloatRect Text::localBounds() const
{
    ild::FloatRect rect;
    rect.width = textImpl().dimensions().x;
    rect.height = textImpl().dimensions().y;
    return rect;
}

unsigned int Text::characterSize() const
{
    return textImpl().characterSize();
}

void Text::characterSize(unsigned int size)
{
    if (size == textImpl().characterSize())
    {
        return;
    }

    textImpl().characterSize(size);
    textImpl().dirty(true);
}

const std::string & Text::string() const
{
    return textImpl().text();
}

void Text::string(const std::string & newString)
{
    if (newString == textImpl().text())
    {
        return;
    }

    textImpl().text(newString);
    textImpl().dirty(true);
}

const std::string & Text::fontKey() const
{
    return _fontKey;
}

void Text::fontKey(const std::string & fontKey)
{
    _fontKey = fontKey;
}

bool Text::smooth() const
{
    // SDL fonts are always smooth for now
    return true;
}

void Text::smooth(bool newSmooth) const
{
    // SDL fonts are always smooth for now
}

priv::TextImpl & Text::textImpl() const
{
    return static_cast<priv::TextImpl &>(*_pimpl);
}

} // namespace ildhal
