#ifndef Ancona_Engine_Resource_ResourceLibrary_H_
#define Ancona_Engine_Resource_ResourceLibrary_H_

#include <string>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace ild
{

class RequestList;
class AbstractLoader;

class ResourceHolder 
{
    public:
        ResourceHolder(void * rawResource, int referenceCount, AbstractLoader * loader) :
            rawResource(rawResource),
            referenceCount(referenceCount),
            loader(loader)
        {
        }
        
        void * rawResource;
        int referenceCount = 0;  
        AbstractLoader * loader;
};

class ResourceLibrary
{
    public:
        /**
         * @brief  Used to retrieve a resource from the library
         *
         * @tparam T Type of resource to be retrived
         * @param  key Key that is used to identify the resource
         *
         * @return A pointer to the resource
         */
        template <class T>
        static T * Get(const std::string & key)
        {
            return static_cast<T *>(
                    _resources.at(typeid(T)).at(key).rawResource);
        }

        /**
         * @brief Used to register a loader with the resource 
         *        library
         *
         * @param loader Loader that should be library
         */
        static void RegisterLoader(AbstractLoader * loader);

        /**
         * @brief Request the resources contained in the list.  
         *        The resources will be loaded into the resource 
         *        library.
         *
         * @param request List of resources to be loaded.
         */
        static void Request(const RequestList & request);

        /**
         * @brief Return the resources contained in the list.  
         *        If no other list has a request for an resource 
         *        then the resource will be deleted.
         *
         * @param request List of resources to be returned.
         */
        static void Return(const RequestList & request);

        /**
         * @brief  Check if the request list is done loading.
         *
         * @param  request List that describes the requested 
         *         resources.
         *
         * @return True if the list is done loading.  False 
         *         otherwise.
         */
        static bool DoneLoading(RequestList & request);

        static void ProvideAlternateSource(
            const std::string & type, 
            const std::string & key, 
            const std::string & alternateSource);

        static void ClearAlternateSource(const std::string & type, const std::string & key);

        /**
         * @brief  Return a string that contains the path to the 
         *         resource root.
         *
         * @return Path to the resource root.
         */
        static std::string ResourceRoot();

        /**
         * @brief Looks through the resources and deletes any that have a
         *        reference counter of 0.
         */
        static void GarbageCollect();
        

    private:
        /**
         * @brief Typedefine to clean up _resources definition
         */
        typedef std::unordered_map<std::string, ResourceHolder> resource_map;
        /**
         * @brief Dictionary used to map the type of resource 
         *        to the map that contains the resource.
         */
        static std::unordered_map<std::type_index, resource_map> _resources;
        /**
         * @brief Dictionary used to map the name of an resource 
         *        type to the loader that can load it.
         */
        static std::unordered_map<std::string, AbstractLoader *> _loaders;

        static std::unordered_map<std::string, std::unordered_map<std::string, std::string>> _alternateSources;

        static void DeleteResource(const std::string & type, const std::string & key);
        static const std::string & FileToLoad(const std::string & type, const std::string & key);
};

}


#endif
