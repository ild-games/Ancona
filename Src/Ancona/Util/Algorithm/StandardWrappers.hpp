#ifndef Ancona_Util_Algorithm_StandardWrappers_H_
#define Ancona_Util_Algorithm_StandardWrappers_H_

#include <algorithm>

using namespace alg
{

template <typename Container,typename UPredicate>
bool all_of(Container & container, UPredicate pred)
{
    return std::all_of(container.begin(), container.end(), pred);
}

template <typename Container,typename UPredicate>
bool any_of(Container & container, UPredicate pred)
{
    return std::any_of(container.begin(), container.end(), pred);
}

template <typename Container,typename UPredicate>
bool none_of(Container & container, UPredicate pred)
{
    return std::none_of(container.begin(), container.end(), pred);
}

template <class Container, class Function>
Function for_each (Container & container, Function fn)
{
    return std::for_each(container.begin(), container.end(), fn);
}

template <class Container, class T>
auto find(Container & c, T & v) -> decltype(c.begin())
{
    return std::find(c.begin(), c.end(), v);
}

template <class Container, class UPredicate>
auto find_if(Container & c, UPredicate v) -> decltype(c.begin())
{
    return std::find_if(c.begin(), c.end(), v);
}

template <class Container, class UPredicate>
auto find_if_not(Container & c, UPredicate v) -> decltype(c.begin())
{
    return std::find_if_not(c.begin(), c.end(), v);
}

template <class ContainerA, class ContainerB>
auto find_end(ContainerA & a, ContainerB) -> decltype(a.begin())
{
    return std::find_end(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class UPredicate>
auto find_end(ContainerA & a, ContainerB & b, UPredicate pred) -> decltype(a.begin())
{
    return std::find_end(a.begin(), a.end(), b.begin(), b.end(), pred);
}

template <class ContainerA, class ContainerB>
auto find_first_of(ContainerA & a, ContainerB) -> decltype(a.begin())
{
    return std::find_first_of(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class UPredicate>
auto find_first_of(ContainerA & a, ContainerB & b, UPredicate pred) -> decltype(a.begin())
{
    return std::find_first_of(a.begin(), a.end(), b.begin(), b.end(), pred);
}

};


#endif
