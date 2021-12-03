#ifndef Ancona_Core2D_Systems_Audio_MusicSystem_H_
#define Ancona_Core2D_Systems_Audio_MusicSystem_H_

#include <unordered_map>

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

#include "Music.hpp"

namespace ild
{

class MusicComponent
{
  public:
    MusicComponent()
    {
    }

    void FetchDependencies(const Entity &entity);
    void Serialize(Archive &arc);
    void Update(float delta);

    std::shared_ptr<Music> GetMusic(const std::string &key);
    std::shared_ptr<Music> GetFirstMusic();
    const std::vector<std::shared_ptr<Music>> &GetAllMusics();
    bool HasMusic(const std::string &key);

  private:
    std::vector<std::shared_ptr<Music>> _musics;
    std::unordered_map<std::string, std::shared_ptr<Music>> _hashedMusics;
};

class MusicSystem : public UnorderedSystem<MusicComponent>
{
  public:
    MusicSystem(std::string name, SystemManager &manager);

    void Update(float delta) override;

    MusicComponent *CreateComponent(const Entity &entity);
    void PlayMusic(const std::string &musicToPlay);
    void PauseAllMusic();
};

} // namespace ild

#endif
