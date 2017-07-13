#ifndef Ancona_Engine_Resource_SoundBufferLoader_H_
#define Ancona_Engine_Resource_SoundBufferLoader_H_

#include <SFML/Audio.hpp>

#include <Ancona/Framework/Resource/SFMLResourceLoader.hpp>

namespace ild
{

/**
 * @brief SoundBuffer loader is used to load an sf::SoundBuffer
 */
class SoundBufferLoader : public SFMLResourceLoader<sf::SoundBuffer>
{
    public:
        /**
         * @brief Initialize a sound buffer loader and register it with the ResourceLibrary
         *
         * @param resourceName Resource Type to be used (EX "SoundWAV")
         * @param fileExtension File extension to be used (EX "wav")
         */
        SoundBufferLoader(
                const std::string & resourceName,
                const std::string & fileExtension);
};

}


#endif
