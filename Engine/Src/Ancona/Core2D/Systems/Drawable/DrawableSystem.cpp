#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>
#include <Ancona/Util/Algorithm.hpp>

using namespace ild;

DrawableSystem::DrawableSystem(
        std::string systemName,
        ildhal::Window & window,
        SystemManager & systemManager) :
    UnorderedSystem(systemName, systemManager, UpdateStep::Draw),
    _window(window),
    _renderTexture(new sf::RenderTexture()),
    _windowSprite(new sf::Sprite()),
    _renderView(new sf::View())
{
}

void DrawableSystem::Update(float delta)
{
    ILD_Assert(_defaultCamera != nullptr, "Default camera not set");

    //RenderUsingTexture(delta);
    RenderUsingWindow(delta);
}

void DrawableSystem::RenderUsingTexture(float delta)
{
    _renderTexture->clear(sf::Color::Black);

    for (auto & camera : _cameras)
    {
        camera->Draw(*_renderTexture, _window, delta);
    }

    _renderTexture->display();
    _renderTexture->setSmooth(true);
    _windowSprite->setTexture(_renderTexture->getTexture());
    sf::RenderStates states(sf::BlendNone);
    _window.Draw(*_windowSprite, states);
}

void DrawableSystem::RenderUsingWindow(float delta) 
{
    for (auto & camera : _cameras)
    {
        camera->Draw(_window.GetRenderTarget(), _window, delta);
    }
    _window.SetView(_defaultCamera->view());
}

void DrawableSystem::SetupWindowRenderElements() 
{
    auto defaultSize = _defaultCamera->view().getSize();
    _renderTexture->create(defaultSize.x, defaultSize.y);
    _renderView->setSize(defaultSize);
    _renderView->setCenter(defaultSize.x / 2, defaultSize.y / 2);
    _window.SetView(*_renderView);
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

    if(alg::find(_cameras, camera) == _cameras.end())
    {
        _cameras.push_back(camera);
    }

    AttachComponent(entity, comp);
    return comp;
}

void DrawableSystem::OnComponentRemove(Entity entity, DrawableComponent * component)
{
    for(CameraComponent * camera : _cameras)
    {
        camera->RemoveDrawableComponent(component);
    }
}

/* getters and setters */
void DrawableSystem::defaultCamera(CameraComponent *defaultCamera)
{
    if(_defaultCamera != nullptr)
    {
        RemoveCamera(_defaultCamera);
    }
    _defaultCamera = defaultCamera;
    SetupWindowRenderElements();
}
