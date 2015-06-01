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

/**
 * @brief DualMap encapsulates a std::map but manages a reversed map of the same data.
 * If you use a map<std::string, int> a map<int, std::string> of duplicate data is managed
 * along with the original map.
 *
 * @tparam T value type for the normal map's key
 * @tparam V value type for the normal map's values
 *
 * @author Tucker Lein
 */
template<typename T, typename V>
class DualMap
{
    public:
        /**
         * @brief Default constructor with blank maps.
         */
        DualMap()
        {
            _normal.reset(new std::map<T, V>());
            _reverse.reset(new std::map<V, T>());
        }

        /**
         * @brief Constructs the DualMap with an initializer list
         *
         * @param normal Initializer list of pairs so the DualMap can be constructed using this syntax:
         *               { { "hello", 0 },
         *                 { "goodbye", 1} }
         */
        DualMap(std::initializer_list<std::pair<const T, V>> normal)
        {
            _normal.reset(new std::map<T, V>(normal));
            _reverse.reset(new std::map<V, T>());
            for(auto normalPair : *_normal)
            {
                _reverse->insert({normalPair.second, normalPair.first});
            }
        }

        /**
         * @brief Adds a key and value into the DualMap.
         *
         * @param key Key to add, will be the value in the reverse map.
         * @param val Value to add, will be the key in the reverse map.
         */
        void Add(T key, V val)
        {
            Assert(!ContainsKey(key), "Key already exists in map");
            _normal->at(key) = val;
            _reverse->at(val) = key;
        }

        /**
         * @brief Deletes a key and its value from the DualMap.
         *
         * @param key Key to delete
         */
        void Delete(T key)
        {
            Assert(ContainsKey(key), "Key does not exist in map");
            V valOfNormal = _normal->at(key);
            _normal->erase(key);
            _reverse->erase(valOfNormal);
        }

        T GetKey(V value)
        {
            Assert(ContainsValue(value), "Value does not exist in map");
            _reverse->at(value);
        }

        V GetValue(T key)
        {
            Assert(ContainsKey(key), "Key does not exist in map")
            _normal->at(key);
        }

        bool ContainsKey(T key)
        {
            return alg::contains(_normal, key);
        }

        bool ContainsValue(V value)
        {
            return alg::contains(_reverse, value);
        }

    private:
        std::unique_ptr<std::map<T, V>> _normal;
        std::unique_ptr<std::map<V, T>> _reverse;

};

}


#endif
