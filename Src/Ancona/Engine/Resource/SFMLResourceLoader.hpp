#ifndef Ancona_Engine_Resource_SFMLResourceLoader_H_
#define Ancona_Engine_Resource_SFMLResourceLoader_H_

#include <Ancona/Engine/Resource/AbstractLoader.hpp>

#include <string>

namespace ild
{

/**
 * @brief SFMLLoader can be used to define a loader for any SFML resource type that implements loadFromFile
 * @owner Jeff Swenson
 *
 * @tparam SFMLType Type of SFML resource to be loaded
 */
template <class SFMLType>
class SFMLResourceLoader : public AbstractLoader
{
    public:
        /**
         * @brief Initialize the resource loader with values that make sense for the template arguments
         * @brief resourceName Name that describes resource type
         * @brief fileExtension File extension used for the resource
         * @brief directory Describes the directory the resource is stored in
         */
        SFMLResourceLoader(const std::string & resourceName, 
                           const std::string & fileExtension,
                           const std::string & directory) 
                           : AbstractLoader(resourceName,typeid(SFMLType)),
                           _fileExtension(fileExtension), _directory(directory)
        {
        }

        /**
         * @brief see ild::ResourceLoader
         */
        void * Load(const std::string & resourceKey)
        {
            SFMLType * object = new SFMLType();
            std::string fileName = GetResourceFileName(
                    _directory, resourceKey, _fileExtension
                    );

            if(!(object->loadFromFile(fileName)))
            {
                //If the load failed then null should be returned
                delete object;
                return NULL;
            }
            PostLoad(object);
            return object;
        }

        /**
         * @brief see ild::ResourceLoader
         */
        void DeleteResource(void * resource)
        {
            SFMLType * object = static_cast<SFMLType *>(resource);
            delete object;
        }
    protected:
        virtual void PostLoad(SFMLType * loadedObj) { }
    private:
        std::string _fileExtension;
        std::string _directory;
};

}

#endif
