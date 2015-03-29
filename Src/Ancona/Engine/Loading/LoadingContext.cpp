#include <Ancona/Engine/Loading/LoadingContext.hpp>
#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/ShapeDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/AnimatedDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/SpriteDrawable.hpp>
#include <Ancona/Engine/Core/Systems/Drawable/TextDrawable.hpp>

using namespace ild;

LoadingContext::LoadingContext(ScreenSystemsContainer & systems) :
    _systems(systems)
{
}

