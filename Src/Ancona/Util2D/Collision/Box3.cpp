#include <Ancona/Util2D/Collision/Box3.hpp>

using namespace ild;

Box3::Box3(const sf::Vector3f & position,
           const sf::Vector3f & dimension,
           const sf::Vector2f & rotation)
        : Position(position),Dimension(dimension),
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
