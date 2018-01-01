#ifndef Ancona_Engine_Serializing_StdSerializer_H_
#define Ancona_Engine_Serializing_StdSerializer_H_

#include <string>
#include <vector>

#include <Ancona/Framework/Serializing/Archive.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/Util/StrUtil.hpp>

namespace ild {

const float FLOAT_INF = std::numeric_limits<float>::infinity();
const double DOUBLE_INF = std::numeric_limits<double>::infinity();

#define GENERATE_STDSERIALIZER(type, method, jsonType) \
    template <> struct Serializer<type> { \
        static void Serialize(type & property, Archive & arc) { \
            if(arc.loading()) { \
                property = arc.CurrentBranch().method(); \
            } else { \
                arc.CurrentBranch() = property; \
            } \
        } \
        static const rapidjson::Type SerializingType() { \
            return jsonType; \
        } \
    };

template <> struct Serializer<std::string> {
    static void Serialize(std::string & property, Archive & arc) {
        if (arc.loading()) {
            property = arc.CurrentBranch().GetString();
        } else {
            arc.CurrentBranch().SetString(property.c_str(), property.length());
        }
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kStringType;
    }
};

template <> struct Serializer<float> {
    static void Serialize(float & property, Archive & arc) {
        if(arc.loading()) {
            if (arc.CurrentBranch().IsString() && std::string(arc.CurrentBranch().GetString()) == "inf")
            {
                property = FLOAT_INF;
            }
            else
            {
                property = arc.CurrentBranch().GetFloat();
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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kNumberType;
    }
};

template <> struct Serializer<double> {
    static void Serialize(double & property, Archive & arc) {
        if(arc.loading()) {
            if (arc.CurrentBranch().IsString() && std::string(arc.CurrentBranch().GetString()) == "inf")
            {
                property = DOUBLE_INF;
            }
            else
            {
                property = arc.CurrentBranch().GetDouble();
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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kNumberType;
    }
};

GENERATE_STDSERIALIZER(int, GetInt, rapidjson::Type::kNumberType)

GENERATE_STDSERIALIZER(bool, GetBool, rapidjson::Type::kFalseType)

GENERATE_STDSERIALIZER(unsigned int, GetUint, rapidjson::Type::kNumberType)

GENERATE_STDSERIALIZER(int64_t, GetInt64, rapidjson::Type::kNumberType)

GENERATE_STDSERIALIZER(unsigned char, GetUint, rapidjson::Type::kStringType)

template<class T>
struct Serializer<std::vector<T>> {
    static void Serialize(std::vector<T> &property, Archive &arc) {
        if (arc.loading()) {
            for (size_t i = 0; i < arc.CurrentBranch().Size(); i++) {
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

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kArrayType;
    }
};

template<class T, class V>
struct Serializer<std::pair<T, V>> {
    static void Serialize(std::pair<T, V> & property, Archive & arc) {
        arc(property.first, "first");
        arc(property.second, "second");
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

template<class T>
struct Serializer<std::map<std::string, T>> {
    static void Serialize(std::map<std::string, T> &property, Archive &arc) {
        if (arc.loading()) {
            for (auto iter = arc.CurrentBranch().MemberBegin(); iter != arc.CurrentBranch().MemberEnd(); iter++) {
                auto entityKey = iter->name.GetString();
                arc(property[entityKey], entityKey);
            }
        }
        else {
            for (auto &keyValPair : property) {
                arc(property[keyValPair.first], keyValPair.first);
            }
        }
    }

    static const rapidjson::Type SerializingType() 
    {
        return rapidjson::Type::kObjectType;
    }
};

}


#endif
