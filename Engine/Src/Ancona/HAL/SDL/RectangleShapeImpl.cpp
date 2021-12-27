#include <memory>

#include <SDL2/SDL.h>

#include <Ancona/HAL/SDL/RectangleShapeImpl.hpp>
#include <Ancona/HAL/SDL/RenderStatesImpl.hpp>
#include <Ancona/HAL/SDL/RenderTargetImpl.hpp>

namespace ildhal
{

/* Pimpl Implementation */
priv::RectangleShapeImpl::RectangleShapeImpl(const ild::Vector2f & size) : _size(size)
{
}

void priv::RectangleShapeImpl::Draw(SDL_Renderer & sdlRenderer, const ildhal::RenderStates & renderStates)
{
    SDL_SetRenderDrawColor(&sdlRenderer, _fillColor.r, _fillColor.g, _fillColor.b, _fillColor.a);

    SDL_FRect sdlRect;

    const ild::Transform & transform = renderStates.renderStatesImpl().transform();
    sdlRect.x = transform.position().x - _origin.x;
    sdlRect.y = transform.position().y - _origin.y;
    sdlRect.w = _size.x;
    sdlRect.h = _size.y;
    SDL_RenderFillRectF(&sdlRenderer, &sdlRect);
}

/* HAL Interface Implementation */

RectangleShape::RectangleShape()
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>();
}

RectangleShape::RectangleShape(const ild::Vector2f & size)
{
    _pimpl = std::make_unique<priv::RectangleShapeImpl>(size);
}

void RectangleShape::Draw(ildhal::RenderTarget & renderTarget, const ildhal::RenderStates & renderStates)
{
    rectangleShapeImpl().Draw(renderTarget.renderTargetImpl().sdlRenderer(), renderStates);
}

/* getters and setters */

const ild::Vector2f RectangleShape::size() const
{
    return rectangleShapeImpl().size();
}

void RectangleShape::size(const ild::Vector2f & newSize)
{
    rectangleShapeImpl().size(newSize);
}

ild::FloatRect RectangleShape::localBounds() const
{
    ild::FloatRect rect;
    rect.width = rectangleShapeImpl().size().x;
    rect.height = rectangleShapeImpl().size().y;
    return rect;
}

priv::RectangleShapeImpl & RectangleShape::rectangleShapeImpl() const
{
    return static_cast<priv::RectangleShapeImpl &>(*_pimpl);
}

} // namespace ildhal
