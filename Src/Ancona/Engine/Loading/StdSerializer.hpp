#ifndef Ancona_Engine_Loading_StdSerializer_H_
#define Ancona_Engine_Loading_StdSerializer_H_

#include <string>
#include <vector>

#include <Ancona/Engine/Loading/Archive.hpp>
#include <Ancona/Engine/Loading/Serializer.hpp>

namespace ild
{

#define GENERATE_STDSERIALIZER(type, method) \
    template <> struct Serializer<type> { \
        static void Serialize(type & property, Archive & arc) { \
            if(arc.IsLoading()) { \
                property = arc.GetTopJson()->method(); \
            } else { \
                (*arc.GetTopJson()) = property; \
            } \
        } \
    };

GENERATE_STDSERIALIZER(Json::Value::Int, asInt)
GENERATE_STDSERIALIZER(float, asFloat)
GENERATE_STDSERIALIZER(double, asDouble)
GENERATE_STDSERIALIZER(bool, asBool)
GENERATE_STDSERIALIZER(std::string, asString)
GENERATE_STDSERIALIZER(const char*, asCString)
GENERATE_STDSERIALIZER(Json::Value::UInt, asUInt)
GENERATE_STDSERIALIZER(Json::Value::Int64, asInt64)

template <class T>
struct Serializer<std::vector<T>>
{
    static void Serialize(std::vector<T> & property, Archive & arc)
    {
        if(arc.IsLoading())
        {
            for(int i = 0; i < arc.GetTopJson()->size(); i++)
            {
                property.emplace_back();
                arc(property.back(), i);
            }
        } 
        else
        {
            for(int i = 0; i < property.size(); i++)
            {
                arc(property[i], i);
            }
        }
    }
};

}

#endif
