#ifndef Ancona_Engine_Loading_Archive_H_
#define Ancona_Engine_Loading_Archive_H_

#include <stack>
#include <string>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Loading/ClassConstructor.hpp>
#include <Ancona/Engine/Loading/LoadingContext.hpp>
#include <Ancona/Engine/Loading/PolymorphicMap.hpp>
#include <Ancona/Engine/Loading/Serializer.hpp>

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
        /**
         * @brief Constructs an Archive.
         *
         * @param root Root of the json for the archive.
         * @param context Current loading context.
         */
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

       /**
       * @brief Serialize or deserialize the property based on if the game is being loaded or saved.
       *        When loading it will check if the property has a __cpp_type value.  If it does that
       *        will be used to look up the polymorphic serializer in PolymorphicMap.  If it is not
       *        in the map then the normal serializer will be used.  The object will be constructed
       *        using ClassConstructor<T>.  By default ClassConstructor uses the object's default
       *        constructor.  When saving the polymorphic serializer will be used if one exists in
       *        the PolymorphicMap.  Otherwise the standard serializer will be used.
       *
       * @tparam T Type of the property being archived.
       * @param property Pointer that is being archived.
       * @param key Key of the JSON for this property.
       */
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

        /**
         * @copydoc ild::operator()(T *& property, const Key & key)
         */
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

        /**
        * @copydoc ild::operator()(T *& property, const Key & key)
        */
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

        /**
         * @brief Serializes a system from the given system key.
         *
         * @tparam SystemType Type of the system being serialized.
         * @param systemProperty System reference that will be set to the desired system.
         * @param systemKey Key of the system.
         */
        template <class SystemType>
        void system(SystemType *& systemProperty, const std::string & systemKey)
        {
            if (_loading) 
            {
                systemProperty = _context.GetSystems().GetSystem<SystemType>(systemKey);
            }
        }

        /**
         * @brief Loads the entity from the KEY of the entity in json.
         *
         * @param entity Entity reference that will be set to the desired entity.
         * @param entityJsonKey Key of the entity.
         */
        void entityUsingJsonKey(Entity & entity, const std::string & entityJsonKey)
        {
            if(_loading)
            {
                entity = GetEntity(CurrentBranch()[entityJsonKey].asString());
            }
            //TODO ANC-79 implement saving
        }

        /**
         * @brief Enter the context of the given property.
         *
         * @param name Property that will be serialized.
         */
        void EnterProperty(const std::string & name);

        /**
         * @brief Enter the context of the given property.
         *
         * @param name Property that will be serialized.
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
