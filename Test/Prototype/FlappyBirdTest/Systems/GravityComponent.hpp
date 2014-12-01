#ifndef Ancona_Game_Systems_GravityComponent_H_
#define Ancona_Game_Systems_GravityComponent_H_

#include <Ancona/Engine/Core/Systems/PositionSystem.hpp>

namespace ild
{

class GravityComponent
{
    public:
        GravityComponent(PositionComponent & positionComponent);

        void Update(float delta);

    private:
        const float GRAVITY_F = 200.0f;

        PositionComponent & _positionComponent;
};

}

#endif
