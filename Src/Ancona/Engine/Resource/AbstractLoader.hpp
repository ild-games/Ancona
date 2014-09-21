#ifndef Ancona_Engine_Resource_AbstractLoader_H_
#define Ancona_Engine_Resource_AbstractLoader_H_

#include <string>
#include <typeindex>

namespace ild
{

/**
 * @brief Class that all resource loaders should inherit from
 * @owner Jeff Swenson & Tucker Lein
 */
class AbstractLoader
{
    public:
        /**
         * @brief Initialzie and create the abstract loader.
         *
         * @param resourceName Name that describes the resource type to be loaded EX "Texture"
         * @param resourceType Type of resource that the loader will load
         */
        AbstractLoader(const std::string & resourceName, const std::type_index & resourceType);

        /**
         * @brief Load the resource that corresponds to the given key from disk
         *
         * @param resourceKey String that describes a unique resource
         */
        virtual void * Load(const std::string & resourceKey) = 0;

        /**
         * @brief Delete the resource given as an argument.  The resource must be of the same type loaded
         * by the loader.
         *
         * @param resource A pointer to the resource object.
         */
        virtual void  * DeleteResource(void * resource);

        /**
         * @brief Get a type_index that refers to the type of resource loaded by the loader.
         *
         * @return Type_index for the loaded type.
         */
        const std::type_index & GetResourceType();

        /**
         * @brief Get the name that describes the resource type. EX "Texture"
         *
         * @return A string that describes the resource type.
         */
        const std::string & GetResourceName();
    private:
        /**
         * @brief Name that describes the resource type
         */
        std::string _resourceName;
        /**
         * @brief Type of the resource the loader loads
         */
        std::type_index _resourceType;
};

}

#endif
