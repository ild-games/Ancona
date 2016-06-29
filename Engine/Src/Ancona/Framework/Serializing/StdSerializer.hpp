#ifndef Ancona_Engine_Serializing_StdSerializer_H_
#define Ancona_Engine_Serializing_StdSerializer_H_

#include <string>
#include <vector>

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>

namespace ild {

const float FLOAT_INF = std::numeric_limits<float>::infinity();
const double DOUBLE_INF = std::numeric_limits<double>::infinity();

#define GENERATE_PRIMITIVE_SERIALIZER(type, method) \
    template <> struct Serializer<type> { \
        static void Serialize(type & property, Archive & arc) { \
            if(arc.loading()) { \
                property = arc.CurrentBranch().method(); \
            } else { \
                arc.CurrentBranch() = property; \
            } \
        } \
    };

template <> struct Serializer<float> {
    static void Serialize(float & property, Archive & arc) {
        if(arc.loading()) {
            if(arc.CurrentBranch().isString() && arc.CurrentBranch().asString() == "inf")
            {
                property = FLOAT_INF;
            }
            else
            {
                property = arc.CurrentBranch().asFloat();
            }
        } else {
            if(property == FLOAT_INF)
            {
                arc.CurrentBranch() = "inf";
            }
            else
            {
                arc.CurrentBranch() = property;
            }
        }
    }
};

template <> struct Serializer<double> {
    static void Serialize(double & property, Archive & arc) {
        if(arc.loading()) {
            if(arc.CurrentBranch().isString() && arc.CurrentBranch().asString() == "inf")
            {
                property = DOUBLE_INF;
            }
            else
            {
                property = arc.CurrentBranch().asDouble();
            }
        } else {
            if(property == DOUBLE_INF)
            {
                arc.CurrentBranch() = "inf";
            }
            else
            {
                arc.CurrentBranch() = property;
            }
        }
    }
};

GENERATE_PRIMITIVE_SERIALIZER(Json::Value::Int, asInt)

GENERATE_PRIMITIVE_SERIALIZER(bool, asBool)

GENERATE_PRIMITIVE_SERIALIZER(std::string, asString)

GENERATE_PRIMITIVE_SERIALIZER(const char*, asCString)

GENERATE_PRIMITIVE_SERIALIZER(Json::Value::UInt, asUInt)

GENERATE_PRIMITIVE_SERIALIZER(Json::Value::Int64, asInt64)

#ifndef _WIN32
GENERATE_PRIMITIVE_SERIALIZER(u_char, asUInt)
#endif

template<class T>
struct Serializer<std::vector<T>> {
    static void Serialize(std::vector<T> &property, Archive &arc) {
        if (arc.loading()) {
            for (size_t i = 0; i < arc.CurrentBranch().size(); i++) {
                property.emplace_back();
                arc(property.back(), i);
            }
        }
        else {
            for (size_t i = 0; i < property.size(); i++) {
                arc(property[i], i);
            }
        }
    }
};

template<class T, class V>
struct Serializer<std::pair<T, V>> {
    static void Serialize(std::pair<T, V> & property, Archive & arc) {
        arc(property.first, "first");
        arc(property.second, "second");
    }
};

template<class T>
struct Serializer<std::map<std::string, T>> {
    static void Serialize(std::map<std::string, T> &property, Archive &arc) {
        if (arc.loading()) {
            for (auto &entityKey : arc.CurrentBranch().getMemberNames()) {
                arc(property[entityKey], entityKey);
            }
        }
        else {
            for (auto &keyValPair : property) {
                arc(property[keyValPair.first], keyValPair.first);
            }
        }

    }
};

}


#endif
