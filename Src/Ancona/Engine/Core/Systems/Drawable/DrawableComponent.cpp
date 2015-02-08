#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent(
        DrawableSystem & drawableSystem) :
    _drawableSystem(drawableSystem)
{
}

void DrawableComponent::AddDrawable(
        const std::string key,
        Drawable * drawable)
{
    _drawables[key] = std::unique_ptr<Drawable>(drawable);
    _drawableSystem.AddDrawable(drawable);
}

void DrawableComponent::RemoveDrawable(const std::string key)
{
    _drawableSystem.RemoveDrawable(_drawables[key].get());
}

/* getters and setters */
std::vector<Drawable *> DrawableComponent::GetDrawables()
{
    std::vector<Drawable *> toReturn;
    for(std::map<std::string, std::unique_ptr<Drawable> >::iterator it = _drawables.begin(); it != _drawables.end(); ++it)
    {
        toReturn.push_back(it->second.get());
    }
    return toReturn;
}
