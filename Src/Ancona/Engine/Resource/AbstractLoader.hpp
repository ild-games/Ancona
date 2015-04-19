#ifndef Ancona_Engine_Resource_AbstractLoader_H_
#define Ancona_Engine_Resource_AbstractLoader_H_

#include <string>
#include <typeindex>
#include <fstream>

namespace ild
{

/**
 * @brief Class that all resource loaders should inherit from
 *
 * @author Jeff Swenson
 * @author Tucker Lein
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
        virtual void DeleteResource(void * resource) = 0;

        /* getters and setters */
        const std::type_index &resourceType() { return _resourceType; }
        const std::string & resourceName() { return _resourceName; }

    private:
        /**
         * @brief Name that describes the resource type
         */
        std::string _resourceName;
        /**
         * @brief Type of the resource the loader loads
         */
        std::type_index _resourceType;

    protected:
        /**
         * @brief Return a string that describes the resource file location
         *
         * @param resourceDir Resource directory where the resource is 
         * located. Relative to the Resource root directory
         * @param resourceKey Filename (without extension) of resource to
         * load
         * @param fileExtension allowed filetype
         *
         * @return String that describes the resource file location
         */
        std::string GetResourceFileName(
                const std::string & resourceDir, 
                const std::string & resourceKey, 
                const std::string & fileExtension);
};

}

#endif
