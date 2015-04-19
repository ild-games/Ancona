#include <Ancona/Core2D/Systems/Drawable/FadeDrawableSystem.hpp>
#include <Ancona/Engine/EntityFramework/UpdateStep.hpp>

using namespace ild;

/* Component */
FadeDrawableComponent::FadeDrawableComponent(
        DrawableComponent & drawableComponent,
        float fadeIn,
        float fadeSpeed) :
    _drawableComponent(drawableComponent),
    FADE_SPEED(fadeSpeed),
    _fadeIn(fadeIn)
{
}

void FadeDrawableComponent::Update(float delta)
{
    std::vector<Drawable *> drawables = _drawableComponent.GetKeylessDrawables();
    for(Drawable * drawable : drawables)
    {
        int alpha = drawable->GetAlpha();
        if(_fadeIn)
        {
            alpha += (FADE_SPEED * delta);
            if(alpha > 255)
            {
                alpha = 255;
            }
        }
        else
        {
            alpha -= (FADE_SPEED * delta);
            if(alpha < 0)
            {
                alpha = 0;
            }
        }
        drawable->SetAlpha(alpha);
    }
}

/* System */
FadeDrawableSystem::FadeDrawableSystem(
        SystemManager & manager) :
    UnorderedSystem(manager, UpdateStep::Update)
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
    FadeDrawableComponent * comp = new FadeDrawableComponent(
            drawableComponent,
            fadeIn,
            fadeSpeed);
    AttachComponent(entity, comp);

    return comp;
}

