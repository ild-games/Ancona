#ifndef Ancona_Core2D_Systems_Audio_AutoStartMusicSystem_H_
#define Ancona_Core2D_Systems_Audio_AutoStartMusicSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>
#include <Ancona/Core2D/Systems/Audio/MusicSystem.hpp>

namespace ild
{

class AutoStartMusicComponent
{
    public:
        AutoStartMusicComponent() {}

        void FetchDependencies(const Entity & entity);
        void Serialize(Archive & arc);
        void Update(float delta);

    private:

        std::string _musicKeyToPlay;
        MusicSystem * _musicSystem;
};

class AutoStartMusicSystem : public UnorderedSystem<AutoStartMusicComponent>
{
    public:
        AutoStartMusicSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta) override;

        AutoStartMusicComponent * CreateComponent(const Entity & entity);

};

}

#endif
