#ifndef Ancona_Engine_Resource_ResourceLibrary_H_
#define Ancona_Engine_Resource_ResourceLibrary_H_

#include <pair>
#include <type_index>
#include <unordered_map>

namespace ild
{

class ResourceLibrary
{
    public:
        template <class T>
        static T * Get(const std::string & key)
        {
            return dynamic_cast<T *>(_assets.at(typeid(T)).at(key).first);
        }

    private:
        typedef std::unordered_map<std::string, std::pair<void *,int> > asset_map;
        static std::unordered_map<std::type_index, asset_map> _assets;
        static std::unordered_map<std::string, AbstractLoader *> _loaders;
};

}


#endif
