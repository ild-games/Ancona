#ifndef ANCONA_UTIL_DATA_DUALMAP_H
#define ANCONA_UTIL_DATA_DUALMAP_H

#include <initializer_list>
#include <map>
#include <memory>
#include <utility>

#include "../Algorithm.hpp"
#include "../Assert.hpp"

namespace ild
{

template<typename T, typename V>
class DualMap
{
    public:
        DualMap(std::initializer_list<std::pair<const T, V>> normal)
        {
            _normal.reset(new std::map<T, V>(normal));
            _reverse.reset(new std::map<V, T>());
            for(auto normalPair : *_normal)
            {
                _reverse->insert({normalPair.second, normalPair.first});
            }
        }

        void Add(T key, V val)
        {
            Assert(alg::contains(_normal, key), "Key already exists in map");
            _normal->at(key) = val;
            _reverse->at(val) = key;
        }

        void Delete(T key)
        {
            Assert(!alg::contains(_normal, key), "Key does not exists in map");
            V valOfNormal = _normal->at(key);
            _normal->erase(key);
            _reverse->erase(valOfNormal);
        }

        const std::map<T, V> & normal() { return *(_normal.get()); }
        const std::map<V, T> & reverse() { return *(_reverse.get()); }
    private:
        std::unique_ptr<std::map<T, V>> _normal;
        std::unique_ptr<std::map<V, T>> _reverse;

};

}


#endif
