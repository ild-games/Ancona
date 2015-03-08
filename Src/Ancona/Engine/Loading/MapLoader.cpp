#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Loading/MapLoader.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

MapLoader::MapLoader(
        std::string key, 
        ScreenSystemsContainer & systems) : 
    _key(key), 
    _request(new RequestList()),
    _loadingContext(new LoadingContext(systems))
{
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
    Json::Value saveRoot;
    saveStream >> saveRoot;
    auto map = saveRoot["screen-maps"][_key].asString();
    Assert(map != "", "Cannot have a null map");

    std::ifstream mapStream("Maps/" + map + ".map", std::ifstream::binary);
    Assert(mapStream.is_open(), "Failed to load the map file.");
    mapStream >> _root;

    for(Json::Value & assetJson : _root["assets"])
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
    for(Json::Value & curEntity : _root["entities"])
    {
        _loadingContext->GetSystems().GetSystemManager().CreateEntity(curEntity.asString());
    }
    _state = LoadingState::LoadingComponents;
}

void MapLoader::LoadComponents()
{
    for(auto systemNamePair : _loadingContext->GetSystems().GetSystemManager().GetKeyedSystems())
    {
        for(Json::Value & componentJson : _root["components"][systemNamePair.first])
        {
            _loadingContext
                ->GetInflaterMap()
                .GetInflater(systemNamePair.first)
                ->Inflate(
                        componentJson,
                        _loadingContext->GetSystems().GetSystemManager().GetEntity(componentJson["entity"].asString()),
                        _loadingContext.get());
        }
    }
    _state = LoadingState::DoneLoading;
}
