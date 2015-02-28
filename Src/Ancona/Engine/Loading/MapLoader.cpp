#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Loading/MapLoader.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

MapLoader::MapLoader(
        std::string key, 
        SystemManager & systems) : 
    _key(key), 
    _manager(systems),
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
            return _request.PercentLoaded() / 80;
        case LoadingEntities:
            return 80;
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
        _request.Add(
                assetJson["type"].asString(),
                assetJson["key"].asString());
    }

    _state = LoadingState::LoadingAssets;
}

void MapLoader::LoadAssets()
{
    // TODO REMOVE BELOW LINE
    _state = LoadingState::LoadingEntities;
    return;
    if(ResourceLibrary::DoneLoading(_request)) 
    {
        _state = LoadingState::LoadingEntities;
    }
}

void MapLoader::LoadEntities()
{
    for(std::string curKey : _root["components"].getMemberNames())
    {
        _loadingContext
            ->GetInflaterMap()
            .GetInflater(curKey)
            ->Inflate(_root);
    }
}
