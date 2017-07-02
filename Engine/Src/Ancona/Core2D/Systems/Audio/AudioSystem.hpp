#ifndef Ancona_Core2D_Systems_AudioSystem_H_
#define Ancona_Core2D_Systems_AudioSystem_H_

#include <unordered_map>
#include <string>
#include <memory>

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

#include "Sound.hpp"

namespace ild
{
/**
 * @brief Describes a path for other entities to follow
 */
class AudioComponent
{
    public:
        /* Ancona */
        AudioComponent() {}

        void FetchDependencies(const Entity & entity);

        void Serialize(Archive & arc);

        std::weak_ptr<Sound> GetSound(std::string key) { return _hashedSounds[key]; }

    private:
        std::vector<std::shared_ptr<Sound>> _sounds;
        std::unordered_map<std::string, std::shared_ptr<Sound>> _hashedSounds;
};

class AudioSystem : public UnorderedSystem<AudioComponent>
{
    public:
        AudioSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta) override;

        AudioComponent * CreateComponent(
                const Entity & entity);

};

}

#endif
