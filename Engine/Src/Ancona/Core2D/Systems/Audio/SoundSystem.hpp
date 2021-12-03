#ifndef Ancona_Core2D_Systems_SoundSystem_H_
#define Ancona_Core2D_Systems_SoundSystem_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

#include "Sound.hpp"

namespace ild
{
/**
 * @brief Describes a path for other entities to follow
 */
class SoundComponent
{
  public:
    /* Ancona */
    SoundComponent()
    {
    }

    void FetchDependencies(const Entity &entity);

    void Update(float delta);
    void Serialize(Archive &arc);

    std::shared_ptr<Sound> GetSound(const std::string &key);
    void SetVolume(float volumePercent);

    SoundComponent &operator=(SoundComponent &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        for (auto &sound : rhs._sounds)
        {
            auto newSound = new Sound(sound->key(), sound->pitch());
            _sounds.push_back(std::shared_ptr<Sound>(newSound));
        }

        for (auto &sound : _sounds)
        {
            _hashedSounds.insert({sound->key(), sound});
        }
        return *this;
    }

  private:
    std::vector<std::shared_ptr<Sound>> _sounds;
    std::unordered_map<std::string, std::shared_ptr<Sound>> _hashedSounds;
};

class SoundSystem : public UnorderedSystem<SoundComponent>
{
  public:
    SoundSystem(std::string name, SystemManager &manager);

    void Update(float delta) override;
    void OnLoad() override;

    SoundComponent *CreateComponent(const Entity &entity);
    void SetVolume(float volumePercent);
};

} // namespace ild

#endif
