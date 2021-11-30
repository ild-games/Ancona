#include <Ancona/Util2D/Collision/Box3.hpp>

using namespace ild;

Box3::Box3(
    const Vector3f & position,
    const Vector3f & dimension,
    const Vector2f & rotation) :
        Position(position),
        Dimension(dimension),
        Rotation(rotation)
{
}

bool Intersects(const Box3 & box)
{
    return false;

}

bool Contains(const Box3 & box)
{
    return false;

}
