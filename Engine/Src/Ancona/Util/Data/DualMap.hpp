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
template <typename T, typename V> class DualMap
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
    DualMap(const std::initializer_list<std::pair<const T, V>> &normal)
    {
        _normal.reset(new std::map<T, V>(normal));
        _reverse.reset(new std::map<V, T>());
        for (auto &normalPair : *_normal)
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
    void Add(const T &key, const V &val)
    {
        ILD_Assert(!ContainsKey(key), "Key already exists in map");
        ILD_Assert(!ContainsValue(val), "Value already exists in map");
        (*_normal)[key] = val;
        (*_reverse)[val] = key;
    }

    /**
     * @brief Deletes a key and its value from the DualMap.
     *
     * @param key Key to delete
     */
    void RemoveByKey(const T &key)
    {
        ILD_Assert(ContainsKey(key), "Key does not exist in map");
        auto valOfNormal = _normal->find(key);
        _reverse->erase(valOfNormal->second);
        _normal->erase(valOfNormal);
    }

    /**
     * @brief Deletes a value and its key from the DualMap.
     *
     * @param val Value to delete
     */
    void RemoveByValue(const V &val)
    {
        ILD_Assert(ContainsValue(val), "Value does not exist in map");
        auto keyOfReverse = _reverse->find(val);
        _normal->erase(keyOfReverse->second);
        _reverse->erase(keyOfReverse);
    }

    /**
     * @brief Returns the key associated with the given value.
     *
     * @param value Value used to get associated key.
     *
     * @return Associated key.
     */
    const T &GetKey(V value)
    {
        ILD_Assert(ContainsValue(value), "Value does not exist in map");
        return _reverse->at(value);
    }

    /**
     * @brief Returns the value associated with the given key.
     *
     * @param key Key used to get associated value.
     *
     * @return Associated value.
     */
    const V &GetValue(T key)
    {
        ILD_Assert(ContainsKey(key), "Key does not exist in map") return _normal->at(key);
    }

    /**
     * @brief Checks if the given key exists in the DualMap.
     *
     * @param key Key to check.
     *
     * @return True if it exists, otherwise false.
     */
    bool ContainsKey(T key)
    {
        return _normal->find(key) != _normal->end();
    }

    /**
     * @brief Checks if the given value exists in the DualMap.
     *
     * @param value Value to check.
     *
     * @return True if it exists, otherwise false.
     */
    bool ContainsValue(V value)
    {
        return _reverse->find(value) != _reverse->end();
    }

  private:
    std::unique_ptr<std::map<T, V>> _normal;
    std::unique_ptr<std::map<V, T>> _reverse;
};

} // namespace ild

#endif
