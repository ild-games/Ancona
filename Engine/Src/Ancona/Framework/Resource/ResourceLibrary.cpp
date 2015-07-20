#include <Ancona/Framework/Config/Config.hpp>
#include <Ancona/Framework/Resource/ResourceLibrary.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Resource/AbstractLoader.hpp>

#include <android/log.h>

using namespace ild;

typedef std::unordered_map<std::string, std::pair<void *,int> > resource_map;

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
    for(auto & resource : request)
    {
        auto loader = _loaders[resource.first];
        auto & type = loader->resourceType();

        //Decrement the reference count of the resource by one
        auto resourceIterator = _resources[type].find(resource.second);
        resourceIterator->second.second -= 1;
        if(resourceIterator->second.second == 0)
        {
            //If the reference count is zero then we need to delete the resource
            loader->DeleteResource(resourceIterator->second.first);
            _resources[type].erase(resourceIterator);
        }
    }
}

bool ResourceLibrary::DoneLoading(RequestList & request)
{
    bool onDisk = false; 
    while(!onDisk)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "in while loop");
        auto requestIter = request.Next();
        if(requestIter == request.end())
        {
            __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "done loading");
            //We are done loading so return true
            return true;
        }
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "after end check");

        auto loader = _loaders[requestIter->first];
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "after loader lookup");
        auto type = loader->resourceType();
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "after loader type lookup " + type);
        resource_map & resources = _resources[type];
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "after resource map lookup");

        auto resourceIter = resources.find(requestIter->second);
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "pre Load");
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", requestIter->second.c_str());
        if(resourceIter == resources.end())
        {
            //The resource does not exist in the dictionary and needs to be loaded
            onDisk = true;
            resources[requestIter->second].first = loader->Load(requestIter->second);

            resourceIter = resources.find(requestIter->second);
            resourceIter->second.second = 0;
        }
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", "post Load");
        __android_log_print(ANDROID_LOG_VERBOSE, "com.example.sfml", requestIter->second.c_str());

        resourceIter->second.second++;
    }
    return false;
}

const std::string & ResourceLibrary::ResourceRoot()
{
    return Config::GetOption("ResourceRoot"); 
}
