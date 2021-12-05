#include <cmath>

#include <Ancona/Core/Game.hpp>
#include <Ancona/Core2D/Systems/CameraSystem.hpp>
#include <Ancona/Core2D/Systems/Drawable/DrawableSystem.hpp>
#include <Ancona/Graphics/Rect.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Assert.hpp>
#include <Ancona/Util/Vector2.hpp>

using namespace ild;

/* Component */
CameraComponent::CameraComponent() : _offset(Vector2f(0, 0))
{
}

CameraComponent::CameraComponent(const View &originalView, float renderPriority, DrawableSystem *drawableSystem,
                                 float scale, Vector2f offset, Vector2f upperBounds, Vector2f lowerBounds)
    : _view(View(originalView)), _renderPriority(renderPriority), _scale(scale), _offset(offset),
      _lowerBounds(lowerBounds), _upperBounds(upperBounds), _drawableSystem(drawableSystem)
{
}

void CameraComponent::Update(float delta)
{
}

void CameraComponent::Draw(ildhal::RenderTarget &target, ildhal::Window &window, float delta)
{
    auto effectivePosition = GetEffectiveCenter();
    _view.center(effectivePosition.x, effectivePosition.y);

    Box2 cameraBounds(Vector2f(_view.center().x - (_view.size().x), _view.center().y - (_view.size().y)),
                      Vector2f(_view.size().x * 2.0f, _view.size().y * 2.0f), Vector2f(), _view.rotation());

    ApplyLetterboxView(window.size().x, window.size().y);
    target.view(_view);

    if (!_sorted)
    {
        alg::sort(_renderQueue, [](DrawableComponent *lhs, DrawableComponent *rhs) {
            return lhs->topDrawable()->renderPriority() < rhs->topDrawable()->renderPriority();
        });
    }

    for (DrawableComponent *drawable : _renderQueue)
    {
        auto drawableBox = drawable->BoundingBox();
        if (cameraBounds.Intersects(drawableBox))
        {
            drawable->Draw(target, delta);
        }
        drawable->PostDrawUpdate(delta);
    }
}

void CameraComponent::ApplyLetterboxView(int windowWidth, int windowHeight)
{
    float windowRatio = (float)windowWidth / (float)windowHeight;
    float viewRatio = _view.size().x / _view.size().y;
    float sizeX = 1.0f;
    float sizeY = 1.0f;
    float posX = 0.0f;
    float posY = 0.0f;

    if (windowRatio >= viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1.0f - sizeX) / 2.0f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1.0f - sizeY) / 2.0f;
    }

    _view.viewport(FloatRect(posX, posY, sizeX, sizeY));
}

Vector2f CameraComponent::GetEffectiveCenter()
{
    Vector2f effectivePosition;
    if (_followPosition != nullptr)
    {
        effectivePosition = _followPosition->interpolatedPosition(Game::InterpolationAlpha) + _offset;
    }
    else
    {
        effectivePosition = _startingCenter + _offset;
    }

    effectivePosition.x = std::max(std::min(effectivePosition.x, _upperBounds.x), _lowerBounds.x);
    effectivePosition.y = std::max(std::min(effectivePosition.y, _upperBounds.y), _lowerBounds.y);

    return effectivePosition;
}

void CameraComponent::AddDrawableComponent(DrawableComponent *drawable)
{
    ILD_Assert(!alg::contains(_renderQueue, drawable), "Can't add the same drawable twice.");
    _sorted = false;
    _renderQueue.push_back(drawable);
}

void CameraComponent::RemoveDrawableComponent(DrawableComponent *drawable)
{
    if (std::find(_renderQueue.begin(), _renderQueue.end(), drawable) != _renderQueue.end())
    {
        _renderQueue.erase(alg::remove(_renderQueue, drawable));
    }
}

void CameraComponent::FetchDependencies(const Entity &entity)
{
    if (_follows != nullentity)
    {
        _followPosition = (*_positionSystem)[_follows];
    }
    _view.size(_size);
    _view.center(_size.x / 2.0f, _size.y / 2.0f);
    _startingCenter = _view.center();
    scale(_originalScale);
    _drawableSystem->AddCamera(this);
    if (_default)
    {
        _drawableSystem->defaultCamera(this);
    }
}

void CameraComponent::Serialize(Archive &arc)
{
    arc(_renderPriority, "renderPriority");
    arc(_originalScale, "scale");
    arc(_default, "default");
    arc(_size, "size");
    arc(_offset, "offset");
    arc(_lowerBounds, "lowerBounds");
    arc(_upperBounds, "upperBounds");
    arc.entityUsingJsonKey(_follows, "follows");
    arc.system(_positionSystem, "position");
    arc.system(_drawableSystem, "drawable");
}

void CameraComponent::follows(Entity follows)
{
    _follows = follows;
    _followPosition = _positionSystem->at(follows);
}

/* getters and setters */
void CameraComponent::scale(float scale)
{
    ILD_Assert(scale != float(0), "Scale cannot be 0");
    _view.Zoom(1.0f / _scale);
    _scale = scale;
    _view.Zoom(_scale);
}

/* System */
CameraSystem::CameraSystem(std::string name, SystemManager &manager)
    : UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void CameraSystem::Update(float delta)
{
    for (EntityComponentPair comp : *this)
    {
        comp.second->Update(delta);
    }
}

CameraComponent *CameraSystem::CreateComponent(const Entity &entity, const View &originalView, float renderPriority,
                                               DrawableSystem *drawableSystem, float scale)
{
    CameraComponent *comp = new CameraComponent(originalView, renderPriority, drawableSystem, scale);
    AttachComponent(entity, comp);
    return comp;
}
