#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Loading/MapLoader.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Util/Assert.hpp>

using namespace ild;

MapLoader::MapLoader(
        std::string key, 
        SystemManager & systems) : 
    _key(key), 
    _manager(systems)
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
    }
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
    }
}

void MapLoader::LoadMapFile()
{
    std::ifstream saveStream(Config::GetOption("SaveData"), std::ifstream::binary);
    Json::Value saveRoot;
    saveStream >> saveRoot;
    auto map = saveRoot["screen-maps"][_key].asString();
    Assert(map != "", "Cannot have a null map");

    std::ifstream mapStream(map, std::ifstream::binary);
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
    if(ResourceLibrary::DoneLoading(_request)) 
    {
        _state = LoadingState::LoadingEntities;
    }
}

void MapLoader::LoadEntities()
{
    
}
