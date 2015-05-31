#ifndef Ancona_Util_Algorithm_ContainerExtensions_H_
#define Ancona_Util_Algorithm_ContainerExtensions_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace alg
{

template <class Container, class T>
int indexOf(Container & c, T & v)
{
    return std::find(c.begin(), c.end(), v) - c.begin();
}

}

#endif
