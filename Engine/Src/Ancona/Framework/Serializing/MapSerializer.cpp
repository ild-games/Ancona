#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

MapSerializer::MapSerializer(
        std::string key, 
        ScreenSystemsContainer & systems) : 
    _key(key), 
    _request(new RequestList()),
    _loadingContext(new SerializingContext(systems)),
    _profile(systems.profile())
{
    Assert(_profile != -1, "A profile must be specified for the map");
}

float MapSerializer::PercentLoaded()
{
    switch(_state)
    {
        case LoadingMapFile:
            return 0;
        case LoadingAssets:
            return _request->PercentLoaded() / 80;
        case LoadingEntities:
            return 80;
        case SerializingComponents:
            return 81;
        case DoneSerializing:
            return 100;
    }
    Assert(false, "Unknown map loader state");
    return 0;
}

bool MapSerializer::ContinueLoading()
{
    switch(_state)
    {
        case LoadingMapFile:
            LoadMapFile();
            break;
        case LoadingAssets:
            LoadAssets();
            break;
        case LoadingEntities:
            LoadEntities();
            break;
        case SerializingComponents:
            SerializeComponents();
            break;
        case DoneSerializing:
            return false;
    }
    return true;
}

void MapSerializer::LoadMapFile()
{
    std::ifstream saveStream(Config::GetOption("SaveData"), std::ifstream::binary);
    saveStream >> _saveRoot;
    _saveRoot = _saveRoot["profiles"][_profile];
    auto map = _saveRoot["screen-maps"][_key].asString();
    Assert(map != "", "Cannot have a null map");

    std::ifstream mapStream("Maps/" + map + ".map", std::ifstream::binary);
    Assert(mapStream.is_open(), "Failed to load the map file.");
    mapStream >> _mapRoot;

    for(Json::Value & assetJson : _mapRoot["assets"])
    {
        _request->Add(
                assetJson["type"].asString(),
                assetJson["key"].asString());
    }
    _request->Start();

    _state = SerializerState::LoadingAssets;
}

void MapSerializer::LoadAssets()
{
    if(ResourceLibrary::DoneLoading(*_request)) 
    {
        _state = SerializerState::LoadingEntities;
    }
}

void MapSerializer::LoadEntities()
{
    for(Json::Value & curEntity : _mapRoot["entities"])
    {
        _loadingContext->systems().systemManager().CreateEntity(curEntity.asString());
    }
    _state = SerializerState::SerializingComponents;
}

void MapSerializer::SerializeComponents()
{
    Archive mapArc(_mapRoot["systems"], *_loadingContext.get());
    Archive saveArc(_saveRoot["systems"], *_loadingContext.get());
    for(auto systemNamePair : _loadingContext->systems().systemManager().keyedSystems())
    {
        SerializeSpecifiedSystem(systemNamePair, mapArc);
        SerializeSpecifiedSystem(systemNamePair, saveArc);
    }
    _loadingContext->systems().systemManager().FetchWaitingDependencies();
    _state = SerializerState::DoneSerializing;
}

void MapSerializer::SerializeSpecifiedSystem(std::pair<std::string, AbstractSystem *> systemNamePair,
                                             Archive &currentArc)
{
    if (currentArc.HasProperty(systemNamePair.first))
    {
        currentArc.EnterProperty(systemNamePair.first);
        _loadingContext->systems().GetSystem<AbstractSystem>(systemNamePair.first)->Serialize(currentArc);
        currentArc.ExitProperty();
    }
}
