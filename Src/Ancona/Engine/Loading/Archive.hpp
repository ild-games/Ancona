#ifndef Ancona_Engine_Loading_Archive_H_
#define Ancona_Engine_Loading_Archive_H_

#include <string>
#include <stack>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Loading/ClassConstructor.hpp>
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
        template <class T, class Key>
        void operator ()(T & property,const Key & key)
        {
            EnterProperty(key);
            Serializer<T>::Serialize(property, *this);
            ExitProperty();
        }

        template <class T, class Key>
        void operator ()(T *& property,const Key & key)
        {
            EnterProperty(key);
            if(_loading)
            {
                if(CurrentBranch().isMember("__cpp_type"))
                {
                    const auto & cppType = CurrentBranch()["__cpp_type"].asString();
                    PolymorphicMap::GetSerializer(cppType)->Serialize((void *&)(property), *this);
                }
                else 
                {
                    property = ClassConstructor<T>::Construct();
                    Serializer<T>::Serialize(*property, *this);
                }
            } 
            else 
            {
                PolymorphicMap::GetSerializer(property)->Serialize((void *&)(property), *this);
            }
            ExitProperty();
        }

        template <class T, class Key>
        void operator ()(std::unique_ptr<T> & property,const Key & key)
        {
            if(_loading)
            {
                T * obj;
                (*this)(obj, key);
                property.reset(obj);
            } 
            else 
            {
                T * obj = property.get();                    
                (*this)(obj, key);
            }
        }
        
        template <class T, class Key>
        void operator ()(std::shared_ptr<T> & property,const Key & key)
        {
            if(_loading)
            {
                T * obj;
                (*this)(obj, key);
                property.reset(obj);
            } 
            else 
            {
                T * obj = property.get();                    
                (*this)(obj, key);
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

        void entityUsingJsonKey(Entity & entity, const std::string & entityJsonKey)
        {
            if(_loading)
            {
                entity = GetEntity(CurrentBranch()[entityJsonKey].asString());
            }
            //TODO saving
        }

        /**
         * @brief Enter the context of the given property.
         *
         * @param Property that will be serialized.
         */
        void EnterProperty(const std::string & name);

        /**
         * @brief Enter the context of the given property.
         *
         * @param Property that will be serialized.
         */
        void EnterProperty(const int & name);

        /**
         * @brief Test if the current json branch has the property.
         *
         * @param name Name of the property being tested.
         */
        bool HasProperty(const std::string & name);

        /**
         * @brief Exit the context of a given property.  Should only
         * be called if the function also called EnterProperty.
         */
        void ExitProperty();

        /**
         * @brief Get a reference to the Json::Value that is currently being
         * serialized to/from.
         * @return Reference to the top of the property stack.
         */
        Json::Value & CurrentBranch();

        /* getters and setters */
        bool IsLoading() { return _loading; }
        LoadingContext & GetContext() { return _context; }
        Entity GetEntity(const std::string & key) 
        { 
            return _context.GetSystems().GetSystemManager().GetEntity(key); 
        }


    private:
        bool _loading = true;
        Json::Value _root;
        /**
         * @brief Contains the visited levels of the JSON file, the top of the stack is the current json
         *        being archived.
         */
        std::stack<Json::Value *> _jsonBranch;
        LoadingContext & _context;


};

}

#endif
