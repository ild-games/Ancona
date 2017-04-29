#include <algorithm>
#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Resource/AbstractLoader.hpp>

using namespace ild;

typedef std::unordered_map<std::string, ResourceHolder> resource_map;

std::unordered_map<std::type_index, resource_map> ResourceLibrary::_resources;

std::unordered_map<std::string, AbstractLoader *> ResourceLibrary::_loaders;

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
        resourceIterator->second.referenceCount -= 1;
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
        resource_map & resources = _resources[type];

        auto resourceIter = resources.find(requestIter->second);
        if (resourceIter == resources.end())
        {
            //The resource does not exist in the dictionary and needs to be loaded
            onDisk = true;
            resources.emplace(requestIter->second, ResourceHolder(loader->Load(requestIter->second), 0, loader));

            resourceIter = resources.find(requestIter->second);
        }

        resourceIter->second.referenceCount++;
    }
    return false;
}

const std::string & ResourceLibrary::ResourceRoot()
{
    return Config::GetOption("ResourceRoot"); 
}
