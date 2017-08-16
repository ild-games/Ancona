#include <algorithm>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Resource/AbstractLoader.hpp>

using namespace ild;

std::unordered_map<std::type_index, ResourceLibrary::resource_map> ResourceLibrary::_resources;

std::unordered_map<std::string, AbstractLoader *> ResourceLibrary::_loaders;

std::unordered_map<std::string, std::unordered_map<std::string, std::string>> ResourceLibrary::_alternateSources;

void ResourceLibrary::RegisterLoader(AbstractLoader * loader)
{
    _loaders[loader->resourceName()] = loader;
}

void ResourceLibrary::Request(const RequestList & request)
{
}

void ResourceLibrary::Return(const RequestList & request)
{
    for (auto & resource : request)
    {
        auto loader = _loaders[resource.first];
        auto & type = loader->resourceType();

        //Decrement the reference count of the resource by one
        auto resourceIterator = _resources[type].find(resource.second);
        if (resourceIterator != _resources[type].end()) 
        {
            resourceIterator->second.referenceCount -= 1;
        }
    }
}

void ResourceLibrary::GarbageCollect()
{
    for (auto & type : _resources) 
    {
        auto resourceIterator = type.second.begin();
        while (resourceIterator != type.second.end()) 
        {
            if (resourceIterator->second.referenceCount <= 0)
            {
                resourceIterator->second.loader->DeleteResource(resourceIterator->second.rawResource);
                resourceIterator = type.second.erase(resourceIterator);
            }
            else 
            {
                resourceIterator++;
            }
        }
    }
}

void ResourceLibrary::DeleteResource(const std::string & type, const std::string & key) 
{
    auto loader = _loaders[type];
    ResourceLibrary::resource_map & resources = _resources[loader->resourceType()];
    auto resourceIter = resources.find(key);

    if (resourceIter != resources.end()) 
    {
        resourceIter->second.loader->DeleteResource(resourceIter->second.rawResource);
        resources.erase(resourceIter);
    }
}

bool ResourceLibrary::DoneLoading(RequestList & request)
{
    bool onDisk = false; 
    while (!onDisk)
    {
        auto requestIter = request.Next();
        if (requestIter == request.end())
        {
            // after the current RequestList has loaded, garbage collect
            // unused resources still present in the resources map
            GarbageCollect();
            
            // We are done loading so return true
            return true;
        }

        auto loader = _loaders[requestIter->first];
        auto type = loader->resourceType();
        ResourceLibrary::resource_map & resources = _resources[type];

        auto resourceIter = resources.find(requestIter->second);
        if (resourceIter == resources.end())
        {
            //The resource does not exist in the dictionary and needs to be loaded
            onDisk = true;
            auto rawResource = loader->Load(FileToLoad(requestIter->first, requestIter->second));
            resources.emplace(requestIter->second, ResourceHolder(rawResource, 0, loader));

            resourceIter = resources.find(requestIter->second);
        }

        resourceIter->second.referenceCount++;
    }
    return false;
}

const std::string & ResourceLibrary::FileToLoad(const std::string & type, const std::string & key) 
{
    if (_alternateSources[type].find(key) == _alternateSources[type].end()) 
    {
        return key;
    }

    return _alternateSources[type][key];
}

void ResourceLibrary::ProvideAlternateSource(const std::string & type, const std::string & key, const std::string & alternateSource) 
{
    _alternateSources[type][key] = alternateSource;
    DeleteResource(type, key);
}

void ResourceLibrary::ClearAlternateSource(const std::string & type, const std::string & key)
{
    _alternateSources[type].erase(key);
    DeleteResource(type, key);
}

const std::string & ResourceLibrary::ResourceRoot()
{
    return Config::GetOption("ResourceRoot"); 
}
