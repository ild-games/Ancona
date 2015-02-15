#include <Ancona/Engine/Core/Systems/Drawable/DrawableComponent.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/DrawableSystem.hpp>

using namespace ild;

DrawableComponent::DrawableComponent(CameraComponent & cameraComponent) :
    _camera(cameraComponent)
{
}

void DrawableComponent::AddDrawable(
        const std::string key,
        Drawable * drawable)
{
    _drawables[key] = std::unique_ptr<Drawable>(drawable);
    _camera.AddDrawable(drawable);
}

void DrawableComponent::RemoveDrawable(const std::string key)
{
    _camera.RemoveDrawable(_drawables[key].get());
    _drawables.erase(key);
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
