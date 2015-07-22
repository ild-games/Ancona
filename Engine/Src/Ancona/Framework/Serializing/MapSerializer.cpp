#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

MapSerializer::MapSerializer(
        std::string key, 
        ScreenSystemsContainer & systems,
        bool loading,
        bool snapshotSave) :
    _key(key), 
    _request(new RequestList()),
    _loadingContext(new SerializingContext(systems)),
    _profile(systems.profile()),
    _loading(loading),
    _snapshotSave(snapshotSave)
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
    auto saveStream = FileOperations::GetInputFileStream(Config::GetOption("SaveData"));
    Json::Reader reader;
    reader.parse(*saveStream, _saveRoot);

    _saveProfileRoot = _saveRoot["profiles"][_profile];
    _mapName = _saveProfileRoot["screen-maps"][_key].asString();
    Assert(_mapName != "", "Cannot have a null map");
    std::string mapFileName = "Maps/" + _mapName + ".map";

    auto mapStream = FileOperations::GetInputFileStream(mapFileName);
    reader.parse(*mapStream, _mapRoot);

    if(_loading)
    {
        for(Json::Value & assetJson : _mapRoot["assets"])
        {
            _request->Add(
                    assetJson["type"].asString(),
                    assetJson["key"].asString());
        }
        _request->Start();
    }

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
    SerializeEntitySystemSaveables();
    _state = SerializerState::SerializingComponents;
}

void MapSerializer::SerializeEntitySystemSaveables()
{
    Archive entitySaveablesArc(_mapRoot, *_loadingContext.get(), _loading);
    _loadingContext->systems().systemManager().Serialize(entitySaveablesArc);
}

void MapSerializer::SerializeComponents()
{
    Archive mapArc(_mapRoot["systems"], *_loadingContext.get(), _loading, _snapshotSave);
    Archive saveArc(_saveProfileRoot["systems"], *_loadingContext.get(), _loading, true);
    for(auto systemNamePair : _loadingContext->systems().systemManager().keyedSystems())
    {
        SerializeSpecifiedSystem(systemNamePair, mapArc);
        SerializeSpecifiedSystem(systemNamePair, saveArc);
    }
    if(_loading)
    {
        _loadingContext->systems().systemManager().FetchWaitingDependencies();
    }
    _mapRoot["systems"] = mapArc.CurrentBranch();
    _saveRoot["systems"] = saveArc.CurrentBranch();
    _state = SerializerState::DoneSerializing;
}

void MapSerializer::SerializeSpecifiedSystem(
        std::pair<std::string, AbstractSystem *> systemNamePair,
        Archive & currentArc)
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

    auto saveStream = FileOperations::GetOutputFileStream(Config::GetOption("SaveData"));
    _saveRoot["profiles"][_profile] = _saveProfileRoot;
    (*saveStream) << _saveRoot;

    auto mapStream = FileOperations::GetOutputFileStream("Maps/" + _mapName + ".map");
    (*mapStream) << _mapRoot;
}
