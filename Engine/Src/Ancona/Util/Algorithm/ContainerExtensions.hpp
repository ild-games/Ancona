#ifndef Ancona_Util_Algorithm_ContainerExtensions_H_
#define Ancona_Util_Algorithm_ContainerExtensions_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace alg
{

template <class Container, class T>
bool contains(Container & c, T & v)
{
    return std::find(c.begin(), c.end(), v) != c.end();
}

}

#endif
