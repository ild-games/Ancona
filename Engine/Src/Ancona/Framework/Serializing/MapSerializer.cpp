#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

MapSerializer::MapSerializer(
        std::string key, 
        ScreenSystemsContainer & systems,
        bool loading) :
    _key(key), 
    _request(new RequestList()),
    _loadingContext(new SerializingContext(systems)),
    _profile(systems.profile()),
    _loading(loading)
{
    Assert(_profile != -1, "A profile must be specified for the map");
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
            SaveMapFiles();
            return false;
    }
    return true;
}

void MapSerializer::LoadMapFile()
{
    std::ifstream saveStream(Config::GetOption("SaveData"), std::ifstream::binary);
    saveStream >> _saveRoot;
    _saveProfileRoot = _saveRoot["profiles"][_profile];
    _mapName = _saveProfileRoot["screen-maps"][_key].asString();
    Assert(_mapName != "", "Cannot have a null map");

    std::ifstream mapStream("Maps/" + _mapName + ".map", std::ifstream::binary);
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
    if(!_loading)
    {
        _state = SerializerState::LoadingEntities;
        return;
    }
    if(ResourceLibrary::DoneLoading(*_request)) 
    {
        _state = SerializerState::LoadingEntities;
    }
}

void MapSerializer::LoadEntities()
{
    if(!_loading)
    {
        _state = SerializerState::SerializingComponents;
        return;
    }
    for(Json::Value & curEntity : _mapRoot["entities"])
    {
        _loadingContext->systems().systemManager().CreateEntity(curEntity.asString());
    }
    _state = SerializerState::SerializingComponents;
}

void MapSerializer::SerializeComponents()
{
    Archive mapArc(_mapRoot["systems"], *_loadingContext.get(), _loading);
    Archive saveArc(_saveProfileRoot["systems"], *_loadingContext.get(), _loading);
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

void MapSerializer::SaveMapFiles()
{
    if(_loading)
    {
        return;
    }
    std::ofstream saveStream(Config::GetOption("SaveData"), std::ofstream::binary);
    _saveRoot["profiles"][_profile] = _saveProfileRoot;
    saveStream << _saveRoot;
    _saveRoot = _saveRoot["profiles"][_profile];

    std::ofstream mapStream("Maps/" + _mapName + ".map", std::ofstream::binary);
    Assert(mapStream.is_open(), "Failed to load the map file.");
    mapStream << _mapRoot;
}
