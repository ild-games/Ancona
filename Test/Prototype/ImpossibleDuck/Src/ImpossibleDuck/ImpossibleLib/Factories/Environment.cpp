#include "Environment.hpp"

#include <Ancona/Util/Algorithm.hpp>
#include <Ancona/Util/StrUtil.hpp>

using namespace ild;

void ImpossibleEnvironment::CreateCounter(ild::ImpossibleGameSystems *gameSystems)
{
    Entity counterEntity = gameSystems->systemManager().GetEntity("counter");
    CounterComponent & counterComponent = *gameSystems->counter()[counterEntity];
    counterComponent.AddCounter();
    int counterValue = counterComponent.counter();
    std::string counterString = alg::to_string(counterValue);
    TextDrawable & counterTextDrawable = *gameSystems->drawable()[counterEntity]->GetDrawable<TextDrawable>("counter-text");


    counterTextDrawable.text(StrUtil::Split(counterTextDrawable.text(), ' ')[0] + " " + counterString);
}

void ImpossibleEnvironment::SetupCollisions(ImpossibleGameSystems *gameSystems)
{
    gameSystems->collision().DefineCollisionCallback(
            gameSystems->collision().GetType("ground-type"),
            gameSystems->collision().GetType("ground-warp-type"),
            ImpossibleEnvironment::GroundToGroundWarpCollisionHandler(gameSystems));
}

std::function<void(Entity ground, Entity groundWarp)> ImpossibleEnvironment::GroundToGroundWarpCollisionHandler(ImpossibleGameSystems * systems)
{
    return[systems](Entity ground, Entity groundWarp)
    {
        Point oldLoc = systems->physics().at(ground)->GetMutableInfo().position();
        oldLoc.x = 800;
        systems->physics().at(ground)->GetMutableInfo().position(oldLoc);
    };
}
