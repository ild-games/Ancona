#ifndef Ancona_Util_Algorithm_ContainerExtensions_H_
#define Ancona_Util_Algorithm_ContainerExtensions_H_

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

namespace alg
{

template <class Container, class T>
bool contains(Container & c, T & v)
{
    return std::find(c.begin(), c.end(), v) != c.end();
}

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

}

#endif
