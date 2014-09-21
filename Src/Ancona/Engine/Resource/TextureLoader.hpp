#ifndef Ancona_Engine_Resource_TextureLoader_H
#define Ancona_Engine_Resource_TextureLoader_H

namespace ild
{


/**
 * @brief Class that loads texture resources
 * @owner 
 */
class TextureLoader : public AbstractLoader
{
    public:
        /**
         * @brief Initialize the loader and register it with the ResourceLibrary
         */
        TextureLoader();

        /**
         * @brief See ild::AbstractLoader::Load
         */
        void * Load(const std::string & resourceKey);

        /**
         * @brief See ild::AbstractLoader::DeleteResource
         */
        void * DeleteResource(void * resource);
};

}

#endif
