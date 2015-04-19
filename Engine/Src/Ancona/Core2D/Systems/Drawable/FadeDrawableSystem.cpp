#include <Ancona/Core2D/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Framework/EntityFramework/UpdateStep.hpp>

using namespace ild;

/* Component */
FadeDrawableComponent::FadeDrawableComponent(
        DrawableComponent & drawableComponent,
        FadeDrawableSystem * system,
        const Entity & owner,
        float fadeIn,
        bool destroySelf,
        float fadeSpeed) :
    _drawableComponent(drawableComponent),
    _system(system),
    _owner(owner),
    FADE_SPEED(fadeSpeed),
    _fadeIn(fadeIn),
    _destroySelf(destroySelf)
{
}

void FadeDrawableComponent::Update(float delta)
{
    std::vector<Drawable *> drawables = _drawableComponent.keylessDrawables();
    for(Drawable * drawable : drawables)
    {
        drawable->alpha(FadeStep(drawable->alpha(), delta));
    }
}

int FadeDrawableComponent::FadeStep(int alpha, float delta)
{
    bool timeToRemove = false;
    if(_fadeIn)
    {
        alpha += (FADE_SPEED * delta);
        if(alpha > 255)
        {
            alpha = 255;
            timeToRemove = true;
        }
    }
    else
    {
        alpha -= (FADE_SPEED * delta);
        if(alpha < 0)
        {
            alpha = 0;
            timeToRemove = true;
        }
    }
    if(_destroySelf && timeToRemove)
    {
        _system->QueueDeleteComponent(_owner);
        _destroySelf = false;
    }
    return alpha;
}

/* System */
FadeDrawableSystem::FadeDrawableSystem(
        const std::string & name,
        SystemManager & manager) :
    UnorderedSystem(name, manager, UpdateStep::Update)
{
}

void FadeDrawableSystem::Update(float delta)
{
    for(EntityComponentPair comp : *this) 
    {
        comp.second->Update(delta);
    }
}

FadeDrawableComponent * FadeDrawableSystem::CreateComponent(
        const Entity & entity,
        DrawableComponent & drawableComponent,
        bool fadeIn,
        float fadeSpeed)
{
    FadeDrawableComponent *comp = new FadeDrawableComponent(
            drawableComponent,
            this,
            entity,
            fadeIn,
            fadeSpeed);
    AttachComponent(entity, comp);

    return comp;
}

