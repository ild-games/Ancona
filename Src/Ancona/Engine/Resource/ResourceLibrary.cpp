#include <Ancona/Engine/Config/Config.hpp>
#include <Ancona/Engine/Resource/ResourceLibrary.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>
#include <Ancona/Engine/Resource/AbstractLoader.hpp>

using namespace ild;

void ResourceLibrary::RegisterLoader(AbstractLoader * loader)
{
    _loaders[loader->GetResourceName()] = loader;
}

void ResourceLibrary::Request(const RequestList & request)
{
}

void ResourceLibrary::Return(const RequestList & request)
{
    for(auto & resource : request)
    {
        auto loader = _loaders[resource.first];
        auto & type = loader->GetResourceType(); 

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
       auto requestIter = request.Next();
       if(requestIter == request.end())
       {
            //We are done loading so return true
            return true;
       }

       auto loader = _loaders[requestIter->first];
       auto type = loader->GetResourceType();
       resource_map & resources = _resources[type];

       auto resourceIter = resources.find(requestIter->second);
       if(resourceIter == resources.end())
       {
            //The resource does not exist in the dictionary and needs to be loaded
            onDisk = true;
            resources[requestIter->second].first = loader->Load(requestIter->second);

            resourceIter = resources.find(requestIter->second);
            resourceIter->second.second = 0;
       }
   
       resourceIter->second.second++;
   }
}

const std::string & ResourceLibrary::ResourceRoot()
{
    return Config::GetOption("ResourceRoot"); 
}
