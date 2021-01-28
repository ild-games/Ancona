#ifndef Ancona_Util_Algorithm_ContainerWrappers_H_
#define Ancona_Util_Algorithm_ContainerWrappers_H_

#include <algorithm>
#include <iterator>
#include <utility>

namespace alg
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
auto find_end(ContainerA & a, ContainerB & b) -> decltype(a.begin())
{
    return std::find_end(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class UPredicate>
auto find_end(ContainerA & a, ContainerB & b, UPredicate pred) -> decltype(a.begin())
{
    return std::find_end(a.begin(), a.end(), b.begin(), b.end(), pred);
}

template <class ContainerA, class ContainerB>
auto find_first_of(ContainerA & a, ContainerB & b) -> decltype(a.begin())
{
    return std::find_first_of(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class UPredicate>
auto find_first_of(ContainerA & a, ContainerB & b, UPredicate pred) -> decltype(a.begin())
{
    return std::find_first_of(a.begin(), a.end(), b.begin(), b.end(), pred);
}

template <class Container>
auto adjacent_find(Container & container) -> decltype(container.begin())
{
    return std::adjacent_find(container.begin(), container.end());    
}

template <class Container, class BinaryPredicate>
auto adjacent_find(Container & container, BinaryPredicate pred) -> decltype(container.begin())
{
    return std::adjacent_find(container.begin(), container.end(), pred);    
}

template <class Container, class T>
auto count(Container & container, const T& val) -> typename std::iterator_traits<decltype(container.begin())>::difference_type
{
    return std::count(container.begin(), container.end(), val);
}

template <class Container, class UPredicate>
auto count_if(Container & container, UPredicate pred) -> typename std::iterator_traits<decltype(container.begin())>::difference_type
{
    return std::count_if(container.begin(), container.end(), pred);
}

template <class ContainerA, class ContainerB>
auto mismatch(ContainerA & a, ContainerB & b) -> std::pair<decltype(a.begin()),decltype(b.begin())>
{
    return std::mismatch(a.begin(), a.end(), b.begin());
}

template <class ContainerA, class ContainerB, class BinaryPredicate>
auto mismatch(ContainerA & a, ContainerB & b, BinaryPredicate pred) -> std::pair<decltype(a.begin()),decltype(b.begin())>
{
    return std::mismatch(a.begin(), a.end(), b.begin(), pred);
}

template <class ContainerA, class ContainerB>
bool equal(ContainerA & a, ContainerB & b) 
{
    return std::equal(a.begin(), a.end(), b.begin());
}

template <class ContainerA, class ContainerB, class BinaryPredicate>
bool equal(ContainerA & a, ContainerB & b, BinaryPredicate pred) 
{
    return std::equal(a.begin(), a.end(), b.begin(), pred);
}

template <class ContainerA, class ContainerB>
bool is_permutation(ContainerA & a, ContainerB & b)
{
    return std::is_permutation(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class BinaryPredicate>
bool is_permutation(ContainerA & a, ContainerB & b, BinaryPredicate pred)
{
    return std::is_permutation(a.begin(), a.end(), b.begin(), b.end(), pred);
}

template <class ContainerA, class ContainerB>
auto search(ContainerA & a, ContainerB & b) -> decltype(a.begin())
{
    return std::search(a.begin(), a.end(), b.begin(), b.end());
}

template <class ContainerA, class ContainerB, class UPredicate>
auto search(ContainerA & a, ContainerB & b, UPredicate pred) -> decltype(a.begin())
{
    return std::search(a.begin(), a.end(), b.begin(), b.end(), pred);
}

template <class Container, class Size, class T>
auto search_n(Container & container, Size count, const T& val) -> decltype(container.begin())
{
    return std::search_n(container.begin(), container.end(), count, val);
}

template <class Container, class Size, class T, class BinaryPredicate>
auto search_n(Container & container, Size count, const T& val, BinaryPredicate pred) -> decltype(container.begin())
{
    return std::search_n(container.begin(), container.end(), count, val, pred);
}

template <class Container>
void sort(Container & container)
{
    std::sort(container.begin(), container.end());
}

template <class Container, class Compare>
void sort(Container & container, Compare comp)
{
    std::sort(container.begin(), container.end(), comp);
}

template <class Container, class Compare>
auto max_element(Container & container, Compare comp) -> decltype(container.begin())
{
    return std::max_element(container.begin(), container.end(), comp);
}

template <class Container, class T>
auto remove(Container & container, const T& value) -> decltype(container.begin())
{
    return std::remove(container.begin(), container.end(), value);
}

template <class Container, class UPredicate>
auto remove_if(Container & container, const UPredicate& pred) -> decltype(container.begin())
{
    return std::remove_if(container.begin(), container.end(), pred);
}



};


#endif
