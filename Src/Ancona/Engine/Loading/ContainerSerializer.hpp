#ifndef Ancona_Engine_Loading_ContainerSerializer_H_
#define Ancona_Engine_Loading_ContainerSerializer_H_

#include <unordered_map>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/Serializer.hpp>

template <class Key, class Value>
struct Serializer<std::unordered_map<Key, Value *>>
{
    static void Serialize(T & property, Archive & arc)
    {
        if(arc.IsLoading())
        {
            for(auto entityKey : arc.GetTopJson()->getMemberNames())
            {
                Value * value = new Value();
                arc(*value, entityKey);
                
            }
        }
        else
        {

        }
    }
};

#endif
