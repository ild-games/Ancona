#ifndef Ancona_Engine_Resource_SFMLResourceLoader_H_
#define Ancona_Engine_Resource_SFMLResourceLoader_H_

#include <string>

#include <Ancona/Framework/Resource/AbstractLoader.hpp>

namespace ild
{

/**
 * @brief SFMLLoader can be used to define a loader for any SFML resource type that implements loadFromFile
 *
 * @tparam SFMLType Type of SFML resource to be loaded
 *
 * @author Jeff Swenson
 */
template <class SFMLType>
class SFMLResourceLoader : public AbstractLoader
{
    public:
        /**
         * @brief Initialize the resource loader with values that make sense for the template arguments
         *
         * @param resourceName Name that describes resource type
         * @param fileExtension File extension used for the resource
         * @param directory Describes the directory the resource is stored in
         */
        SFMLResourceLoader(
                const std::string & resourceName,
                const std::string & fileExtension,
                const std::string & directory) :
            AbstractLoader(resourceName,typeid(SFMLType)),
            _fileExtension(fileExtension), _directory(directory)
        {
        }

        /**
         * @copydoc ild::AbstractLoader::Load
         */
        void * Load(const std::string & resourceKey) override
        {
            SFMLType * object = new SFMLType();
            std::string fileName = GetResourceFileName(
                    _directory,
                    resourceKey,
                    _fileExtension);

            if(!(object->loadFromFile(fileName)))
            {
                //If the load failed then null should be returned
                delete object;
                return NULL;
            }
            return object;
        }

        /**
         * @copydoc ild::AbstractLoader::DeleteResource
         */
        void DeleteResource(void * resource) override
        {
            SFMLType * object = static_cast<SFMLType *>(resource);
            delete object;
        }

    private:
        std::string _fileExtension;
        std::string _directory;
};

}

#endif
