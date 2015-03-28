#ifndef Ancona_Engine_Loading_Archive_H_
#define Ancona_Engine_Loading_Archive_H_

#include <string>
#include <stack>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Loading/Serializer.hpp>
#include <Ancona/Engine/Loading/PolymorphicMap.hpp>
#include <Ancona/Engine/Loading/LoadingContext.hpp>

namespace ild
{

/**
 * @brief Used to abstract the serialization and deserialization process to a single code path.
 *
 * @author Tucker Lein
 * @author Jeff Swenson
 */
class Archive 
{
    public:
        Archive(Json::Value root, LoadingContext & context);

        /**
         * @brief Serialize or deserialize the property based on if the game is being loaded or saved.
         *        The method used to serialize is determined by template specialization of the Serializer<> 
         *        struct. If there is no specialization of the struct it will call serialize (archive) on 
         *        the property.
         *
         * @tparam T Type of the property being archived.
         * @param property Thing being archived.
         * @param key Key of the JSON for this property.
         */
        template <class T>
        void operator ()(T & property,const std::string & key)
        {
            _jsonBranch.push(&(*_jsonBranch.top())[key]);
            Serializer<T>::Serialize(property, *this);
            _jsonBranch.pop();
        }

        template <class T>
        void operator ()(T *& property,const std::string & key)
        {
            _jsonBranch.push(&(*_jsonBranch.top())[key]);
            if(_loading)
            {
                auto & key = CurrentBranch()["__cpp_type"].asString();
                PolymorphicMap::GetSerializer(key)->Serialize(property, *this);
            } 
            else 
            {
                PolymorphicMap::GetSerializer(property)->Serialize(property, *this);
            }
            _jsonBranch.pop();
        }


        template <class T>
        void operator ()(std::unique_ptr<T> & property,const std::string & key)
        {
            if(_loading)
            {
                T * obj;
                this(obj, key);
                property.reset(obj);
            } 
            else 
            {
                T * obj = property.get();                    
                this(obj, key);
            }
        }
        
        template <class T>
        void operator ()(std::shared_ptr<T> & property,const std::string & key)
        {
            if(_loading)
            {
                T * obj;
                this(obj, key);
                property.reset(obj);
            } 
            else 
            {
                T * obj = property.get();                    
                this(obj, key);
            }
        }

        template <class SystemType>
        void system(SystemType *& systemProperty, const std::string & str)
        {
            if (_loading) 
            {
                systemProperty = _context.GetSystems().GetSystem<SystemType>(str);
            }
        }

        /* getters and setters */
        Json::Value * GetTopJson() { return _jsonBranch.top(); }
        bool IsLoading() { return _loading; }
        LoadingContext & GetContext() { return _context; }
        Entity GetEntity(const std::string & key) 
        { 
            return _context.GetSystems().GetSystemManager().GetEntity(key); 
        }


    private:
        bool _loading;
        Json::Value _root;
        /**
         * @brief Contains the visited levels of the JSON file, the top of the stack is the current json
         *        being archived.
         */
        std::stack<Json::Value *> _jsonBranch;
        LoadingContext & _context;

        Json::Value & CurrentBranch();
};

}

#endif
