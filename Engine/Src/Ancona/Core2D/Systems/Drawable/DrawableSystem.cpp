#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>
#include <Ancona/HAL.hpp>
#include <Ancona/Util/Algorithm.hpp>

namespace ild
{

DrawableSystem::DrawableSystem(std::string systemName, ildhal::Window & window, SystemManager & systemManager) :
        UnorderedSystem(systemName, systemManager, UpdateStep::Draw),
        _window(window),
        _renderTexture(new ildhal::RenderTexture()),
        _windowSprite(new ildhal::Sprite()),
        _renderView(new View())
{
}

void DrawableSystem::Update(float delta)
{
    ILD_Assert(_defaultCamera != nullptr, "Default camera not set");

    // RenderUsingTexture(delta);
    RenderUsingWindow(delta);
}

void DrawableSystem::RenderUsingTexture(float delta)
{
    _renderTexture->Clear(Color::Black);

    for (auto & camera : _cameras)
    {
        camera->Draw(*_renderTexture, _window, delta);
    }

    _renderTexture->Display();
    _renderTexture->smooth(true);
    // _windowSprite->texture(_renderTexture->texture()); // need to implement
    ildhal::RenderStates states(ildhal::BlendNone);
    _window.Draw(*_windowSprite, states);
}

void DrawableSystem::RenderUsingWindow(float delta)
{
    for (auto & camera : _cameras)
    {
        camera->Draw(_window, _window, delta);
    }
    _window.view(_defaultCamera->view());
}

void DrawableSystem::SetupWindowRenderElements()
{
    auto defaultSize = _defaultCamera->view().size();
    _renderTexture->Create(defaultSize.x, defaultSize.y);
    _renderView->size(defaultSize);
    _renderView->center(defaultSize.x / 2.0f, defaultSize.y / 2.0f);
    _window.view(*_renderView);
}

void DrawableSystem::AddCamera(CameraComponent * camera)
{
    _cameras.push_back(camera);
    alg::sort(
        _cameras,
        [](CameraComponent * lhs, CameraComponent * rhs)
        {
            return lhs->renderPriority() < rhs->renderPriority();
        });
}

void DrawableSystem::RemoveCamera(CameraComponent * camera)
{
    _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), camera), _cameras.end());
}

DrawableComponent * DrawableSystem::CreateComponent(
    const Entity & entity,
    std::unique_ptr<Drawable> topDrawable,
    PositionSystem * position)
{
    ILD_Assert(_defaultCamera != nullptr, "Default camera not set");
    return CreateComponent(entity, std::move(topDrawable), position, _defaultCamera);
}

DrawableComponent * DrawableSystem::CreateComponent(
    const Entity & entity,
    std::unique_ptr<Drawable> topDrawable,
    PositionSystem * position,
    CameraComponent * camera)
{
    auto comp = new DrawableComponent(std::move(topDrawable), this, position, camera);

    if (alg::find(_cameras, camera) == _cameras.end())
    {
        _cameras.push_back(camera);
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    for (CameraComponent * camera : _cameras)
    {
        camera->RemoveDrawableComponent(component);
    }
}

/* getters and setters */
void DrawableSystem::defaultCamera(CameraComponent * defaultCamera)
{
    if (_defaultCamera != nullptr)
    {
        RemoveCamera(_defaultCamera);
    }
    _defaultCamera = defaultCamera;
    SetupWindowRenderElements();
}

} // namespace ild
