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

class ResourceLibrary
{
    public:
        /**
         * @brief Used to retrieve a resource from the library
         *
         * @tparam T Type of resource to be retrived
         * @param key Key that is used to identify the resource
         *
         * @return A pointer to the resource
         */
        template <class T>
        static T * Get(const std::string & key)
        {
            return dynamic_cast<T *>(_resources.at(typeid(T)).at(key).first);
        }

        /**
         * @brief Used to register a loader with the resource library
         *
         * @param loader Loader that should be library
         */
        static void RegisterLoader(AbstractLoader * loader);

        /**
         * @brief Request the resources contained in the list.  The resources will
         * be loaded into the resource library.
         *
         * @param request List of resources to be loaded.
         */
        static void Request(const RequestList & request);

        /**
         * @brief Return the resources contained in the list.  If no other list has
         * a request for an resource then the resource will be deleted.
         *
         * @param request List of resources to be returned.
         */
        static void Return(const RequestList & request);

        /**
         * @brief Check if the request list is done loading.
         *
         * @param request List that describes the requested resources.
         *
         * @return True if the list is done loading.  False otherwise.
         */
        static bool DoneLoading(RequestList & request);

        /**
         * @brief Return a string that contains the path to the resource root.
         *
         * @return Path to the resource root.
         */
        static const std::string & ResourceRoot();

    private:
        /**
         * @brief Typedefine to clean up _resources definition
         */
        typedef std::unordered_map<std::string, std::pair<void *,int> > resource_map;
        /**
         * @brief Dictionary used to map the type of resource to the map that contains the resource.
         */
        static std::unordered_map<std::type_index, resource_map> _resources;
        /**
         * @brief Dictionary used to map the name of an resource type to the loader that can load it.
         */
        static std::unordered_map<std::string, AbstractLoader *> _loaders;
};

}


#endif
