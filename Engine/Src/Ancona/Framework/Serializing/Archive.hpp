#ifndef Ancona_Engine_Serializing_Archive_H_
#define Ancona_Engine_Serializing_Archive_H_

#include <stack>
#include <string>

#include "SerializingContext.hpp"
#include <Ancona/Framework/Serializing/ClassConstructor.hpp>
#include <Ancona/Framework/Serializing/PolymorphicMap.hpp>
#include <Ancona/Framework/Serializing/Serializer.hpp>
#include <Ancona/System/Log.hpp>
#include <Ancona/Util/Json.hpp>

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
     * @param loading True if the archive is loading data, false if saving.
     * @param snapshotSave True if the archive is saving via a snapshot (EVERYTHING gets saved), otherwise false.
     * Defaults to false.
     */
    Archive(rapidjson::Value *root, std::shared_ptr<SerializingContext> context, bool loading,
            rapidjson::MemoryPoolAllocator<> &allocator, bool snapshotSave = false);

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
    template <class T, class Key> void operator()(T &property, const Key &key)
    {
        auto shouldContinue = EnterProperty(key, !_loading, Serializer<T>::SerializingType());
        if (!shouldContinue)
        {
            return;
        }

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
    template <class T, class Key> void operator()(T *&property, const Key &key)
    {
        auto shouldContinue = EnterProperty(key, !_loading, Serializer<T>::SerializingType());
        if (!shouldContinue)
        {
            return;
        }

        if (_loading)
        {
            if (CurrentBranch().IsObject() && CurrentBranch().HasMember("__cpp_type"))
            {
                const std::string &cppType = CurrentBranch()["__cpp_type"].GetString();
                auto polymorphicSerializer = PolymorphicMap::serializer(cppType);
                polymorphicSerializer->Serialize((void *&)(property), *this);
            }
            else
            {
                property = ClassConstructor<T>::Construct();
                Serializer<T>::Serialize(*property, *this);
            }
        }
        else
        {
            if (CurrentBranch().IsObject() && CurrentBranch().HasMember("__cpp_type"))
            {
                const auto &cppType = CurrentBranch()["__cpp_type"].GetString();
                PolymorphicMap::serializer(cppType)->Serialize((void *&)(property), *this);
            }
            else
            {
                Serializer<T>::Serialize(*property, *this);
            }
        }
        ExitProperty();
    }

    /**
     * @copydoc ild::operator()(T *& property, const Key & key)
     */
    template <class T, class Key> void operator()(std::unique_ptr<T> &property, const Key &key)
    {
        if (_loading)
        {
            T *obj;
            (*this)(obj, key);
            property.reset(obj);
        }
        else
        {
            T *obj = property.get();
            (*this)(obj, key);
        }
    }

    /**
     * @copydoc ild::operator()(T *& property, const Key & key)
     */
    template <class T, class Key> void operator()(std::shared_ptr<T> &property, const Key &key)
    {
        if (_loading)
        {
            T *obj;
            (*this)(obj, key);
            property.reset(obj);
        }
        else
        {
            T *obj = property.get();
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
    template <class SystemType> void system(SystemType *&systemProperty, const std::string &systemKey)
    {
        if (_loading)
        {
            systemProperty = _context->systems().GetSystem<SystemType>(systemKey);
        }
    }

    /**
     * @brief Loads the SystemManager context during serialization.
     *
     * @param systemManager SystemManager reference that will be set to the SystemManager for the game.
     */
    void systemManager(SystemManager *&systemManager)
    {
        if (_loading)
        {
            systemManager = &_context->systems().systemManager();
        }
    }

    void screenManager(ScreenManager *&screenManager)
    {
        if (_loading)
        {
            screenManager = &_context->systems().screenManager();
        }
    }

    /**
     * @brief Loads the entity from the KEY of the entity in json.
     *
     * @param entity Entity reference that will be set to the desired entity.
     * @param entityJsonKey Key of the entity.
     */
    void entityUsingJsonKey(Entity &entity, const std::string &entityJsonKey)
    {
        if (_loading)
        {
            if (!CurrentBranch().HasMember(entityJsonKey))
            {
                return;
            }
            std::string json = CurrentBranch()[entityJsonKey].GetString();
            if (json != "")
            {
                entity = Archive::entity(json);
            }
        }
        else
        {
            auto entityKey = _context->systems().systemManager().GetEntityKey(entity);
            CurrentBranch()[entityJsonKey].SetString(entityKey.c_str(), entityKey.length());
        }
    }

    /**
     * @brief Enter the context of the given property.
     *
     * @param name Property that will be serialized.
     */
    bool EnterProperty(const std::string &name, bool createIfMissing,
                       const rapidjson::Type typeToCreate = rapidjson::Type::kNullType);

    /**
     * @brief Enter the context of the given property.
     *
     * @param name Property that will be serialized.
     */
    bool EnterProperty(const int &index, bool createIfMissing,
                       const rapidjson::Type typeToCreate = rapidjson::Type::kNullType);

    /**
     * @brief Test if the current json branch has the property.
     *
     * @param name Name of the property being tested.
     */
    bool HasProperty(const std::string &name);

    /**
     * @brief Exit the context of a given property.  Should only
     * be called if the function also called EnterProperty.
     */
    void ExitProperty();

    /**
     * @brief Get a reference to the rapidjson::value that is currently being
     * serialized to/from.
     * @return Reference to the top of the property stack.
     */
    rapidjson::Value &CurrentBranch();

    /* getters and setters */
    bool loading()
    {
        return _loading;
    }
    bool snapshotSave()
    {
        return _snapshotSave;
    }
    void loading(bool loading)
    {
        _loading = loading;
    }
    SerializingContext &context()
    {
        return *_context;
    }
    Entity entity(const std::string &key)
    {
        return _context->systems().systemManager().GetEntity(key);
    }

  private:
    bool _loading;
    bool _snapshotSave;
    rapidjson::Value *_root;
    /**
     * @brief Contains the visited levels of the JSON file, the top of the stack is the current json
     *        being archived.
     */
    std::stack<rapidjson::Value *> _jsonBranch;
    std::shared_ptr<SerializingContext> _context;
    rapidjson::MemoryPoolAllocator<> &_allocator;
};

} // namespace ild

#endif
