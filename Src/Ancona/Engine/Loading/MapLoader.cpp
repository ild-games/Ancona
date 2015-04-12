#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Loading/Loading.hpp>
#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>

using namespace ild;

MapLoader::MapLoader(
        std::string key, 
        ScreenSystemsContainer & systems) : 
    _key(key), 
    _request(new RequestList()),
    _loadingContext(new LoadingContext(systems)),
    _profile(systems.GetProfile())
{
    Assert(_profile != -1, "A profile must be specified for the map");
}

float MapLoader::PercentLoaded()
{
    switch(_state)
    {
        case LoadingMapFile:
            return 0;
        case LoadingAssets:
            return _request->PercentLoaded() / 80;
        case LoadingEntities:
            return 80;
        case LoadingComponents:
            return 81;
        case DoneLoading:
            return 100;
    }
    Assert(false, "Unknown map loader state");
    return 0;
}

bool MapLoader::ContinueLoading()
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
        case LoadingComponents:
            LoadComponents();
            break;
        case DoneLoading:
            return false;
    }
    return true;
}

void MapLoader::LoadMapFile()
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

    _state = LoadingState::LoadingAssets;
}

void MapLoader::LoadAssets()
{
    if(ResourceLibrary::DoneLoading(*_request)) 
    {
        _state = LoadingState::LoadingEntities;
    }
}

void MapLoader::LoadEntities()
{
    for(Json::Value & curEntity : _mapRoot["entities"])
    {
        _loadingContext->GetSystems().GetSystemManager().CreateEntity(curEntity.asString());
    }
    _state = LoadingState::LoadingComponents;
}

void MapLoader::LoadComponents()
{
    Archive mapArc(_mapRoot["systems"], *_loadingContext.get());
    Archive saveArc(_saveRoot["systems"], *_loadingContext.get());
    for(auto systemNamePair : _loadingContext->GetSystems().GetSystemManager().GetKeyedSystems())
    {
        if (mapArc.HasProperty(systemNamePair.first))
        {
            mapArc.EnterProperty(systemNamePair.first);
            _loadingContext->GetSystems().GetSystem<AbstractSystem>(systemNamePair.first)->Serialize(mapArc);
            mapArc.ExitProperty();
        }
       if(saveArc.HasProperty(systemNamePair.first))
       {
           saveArc.EnterProperty(systemNamePair.first);
           _loadingContext->GetSystems().GetSystem<AbstractSystem>(systemNamePair.first)->Serialize(saveArc);
           saveArc.ExitProperty();
       }
    }
    _loadingContext->GetSystems().GetSystemManager().FetchWaitingDependencies();
    _state = LoadingState::DoneLoading;
}
