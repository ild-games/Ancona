#ifndef Ancona_Engine_Resource_HalResourceLoader_H_
#define Ancona_Engine_Resource_HalResourceLoader_H_

#include <string>

#include <Ancona/Framework/Resource/AbstractLoader.hpp>

namespace ild
{

/**
 * @brief HalResourceLoader can be used to define a loader for any Hal resource type that implements loadFromFile
 *
 * @tparam HalType Type of Hal resource to be loaded
 *
 * @author Jeff Swenson
 */
template <class HalType> class HalResourceLoader : public AbstractLoader
{
  public:
    /**
     * @brief Initialize the resource loader with values that make sense for the template arguments
     *
     * @param resourceName Name that describes resource type
     * @param fileExtension File extension used for the resource
     */
    HalResourceLoader(const std::string &resourceName, const std::string &fileExtension)
        : AbstractLoader(resourceName, typeid(HalType)), _fileExtension(fileExtension)
    {
    }

    /**
     * @copydoc ild::AbstractLoader::Load
     */
    void *Load(const std::string &resourceKey) override
    {
        HalType *object = new HalType();
        std::string fileName = GetResourceFileName(resourceKey, _fileExtension);

        if (!(object->LoadFromFile(fileName)))
        {
            // If the load failed then null should be returned
            delete object;
            return NULL;
        }
        return object;
    }

    /**
     * @copydoc ild::AbstractLoader::DeleteResource
     */
    void DeleteResource(void *resource) override
    {
        HalType *object = static_cast<HalType *>(resource);
        delete object;
    }

  private:
    std::string _fileExtension;
};

} // namespace ild

#endif
