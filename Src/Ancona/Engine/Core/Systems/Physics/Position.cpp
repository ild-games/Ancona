
#include <Ancona/Engine/Core/Systems/Physics/Position.hpp>


namespace ild
{

std::ostream & operator << (std::ostream& os, const Point&pt)
{
    os << "(" << pt.x << "," << pt.y << ")";
    return os;
}

}
