#ifndef Ancona_Util_Algorithm_StandardWrappers_H_
#define Ancona_Util_Algorithm_StandardWrappers_H_

#include <algorithm>

using namespace alg
{

template <typename Container,typename UPredicate>
bool all_of(Container & container, UPredicate pred)
{
    std::all_of(container.begin(),container.end(),pred);
}


};


#endif
