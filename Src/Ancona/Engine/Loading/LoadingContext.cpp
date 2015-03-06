#include <Ancona/Engine/Loading/LoadingContext.hpp>
#include <Ancona/Engine/Loading/FunctionalFactory.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>

using namespace ild;

LoadingContext::LoadingContext(ScreenSystemsContainer & systems) :
    _systems(systems)
{
    auto namedComponentInflaters = systems.GetSystemManager().GetComponentInflaters();
    for(auto & namedComponentPair : namedComponentInflaters)
    {
        _inflaterMap.AddAbstract(namedComponentPair.first, namedComponentPair.second);
    }
    _inflaterMap.AddStatic<ShapeDrawable>("shape-drawable");
    _inflaterMap.AddStatic<AnimatedDrawable>("animated-drawable");
    _inflaterMap.AddStatic<SpriteDrawable>("sprite-drawable");
    _inflaterMap.AddStatic<TextDrawable>("text-drawable");
    _inflaterMap.AddFunctional("rectangle-shape", &factories::RectangleInflate);
    _inflaterMap.AddFunctional("circle-shape", &factories::CircleInflate);
}

