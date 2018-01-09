#include <Ancona/Util/Json.hpp>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

using namespace ild;

MapSerializer::MapSerializer(
        std::string key,
        ScreenSystemsContainer & systems,
        std::shared_ptr<RequestList> request,
        bool loading,
        bool snapshotSave) :
    _key(key),
    _request(request),
    _loadingContext(new SerializingContext(systems)),
    _profile(systems.profile()),
    _loading(loading),
    _snapshotSave(snapshotSave)
{
    ILD_Assert(_profile != -1, "A profile must be specified for the map");
}

bool MapSerializer::ContinueLoading()
{
    switch (_state)
    {
        case LoadingMetaData:
            LoadMetaData();
            break;
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

void MapSerializer::LoadMetaData()
{
    for (auto it : _loadingContext->systems())
    {
        if (_loading) 
        {
            it.second->OnLoad(); 
        }
    }
    _state = SerializerState::LoadingMapFile;
}

void MapSerializer::LoadMapFile()
{
    auto saveStream = FileOperations::GetInputFileStream(Config::GetOption("SaveData"));
    rapidjson::IStreamWrapper saveStreamWrapper(*saveStream);
    _saveRoot.ParseStream(saveStreamWrapper);

    _saveProfileRoot = _saveRoot["profiles"][_profile];
    _mapName = _saveProfileRoot["screen-maps"][_key].GetString();
    ILD_Assert(_mapName != "", "Cannot have a null map");
    std::string mapFileName = "maps/" + _mapName + ".map";

    auto mapStream = FileOperations::GetInputFileStream(mapFileName);
    rapidjson::IStreamWrapper mapStreamWrapper(*mapStream);
    _mapRoot.ParseStream(mapStreamWrapper);

    if (_loading)
    {
        for (auto iter = _mapRoot["assets"].Begin(); iter < _mapRoot["assets"].End(); iter++)
        {
            rapidjson::Value & assetJson = *iter;
            auto type = assetJson["type"].GetString();
            auto key = assetJson["key"].GetString();
            if (!_request->Contains(type, key)) 
            {
                _request->Add(type, key);
            }
        }
        _request->Start();
    }

    _state = SerializerState::LoadingAssets;
}

void MapSerializer::LoadAssets()
{
    if (!_loading)
    {
        _state = SerializerState::LoadingEntities;
        return;
    }
    if (ResourceLibrary::DoneLoading(*_request))
    {
        _state = SerializerState::LoadingEntities;
    }
}

void MapSerializer::LoadEntities()
{
    if (!_loading)
    {
        _state = SerializerState::SerializingComponents;
        return;
    }
    for (auto iter = _mapRoot["entities"].Begin(); iter < _mapRoot["entities"].End(); iter++)
    {
        rapidjson::Value & curEntity = *iter;
        _loadingContext->systems().systemManager().CreateEntity(curEntity.GetString());
    }
    _state = SerializerState::SerializingComponents;
}

void MapSerializer::SerializeComponents()
{
    Archive mapArc(&_mapRoot["systems"], _loadingContext, _loading, _mapRoot.GetAllocator(), _snapshotSave);
    Archive saveArc(&_saveProfileRoot["systems"], _loadingContext, _loading, _saveRoot.GetAllocator(), true);
    for (auto systemNamePair : _loadingContext->systems().systemManager().keyedSystems())
    {
        SerializeSpecifiedSystem(systemNamePair, mapArc);
        SerializeSpecifiedSystem(systemNamePair, saveArc);
    }
    if (_loading)
    {
        _loadingContext->systems().systemManager().FetchWaitingDependencies();
    }
    _state = SerializerState::DoneSerializing;
}

void MapSerializer::SerializeSpecifiedSystem(
        std::pair<std::string, AbstractSystem *> systemNamePair,
        Archive & currentArc)
{
    if (currentArc.HasProperty(systemNamePair.first))
    {
        auto shouldContinue = currentArc.EnterProperty(systemNamePair.first, !currentArc.loading(), rapidjson::Type::kObjectType);
        if (shouldContinue) 
        {
            _loadingContext->systems().GetSystem<AbstractSystem>(systemNamePair.first)->Serialize(currentArc);
            currentArc.ExitProperty();
        }
    }
}
