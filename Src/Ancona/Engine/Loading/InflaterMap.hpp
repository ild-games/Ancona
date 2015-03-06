#ifndef Ancona_Engine_Loading_InflaterMap_H_
#define Ancona_Engine_Loading_InflaterMap_H_


#include <memory>
#include <string>
#include <unordered_map>

#include <Ancona/Engine/Loading/AbstractInflater.hpp>
#include <Ancona/Engine/Loading/DynamicInflater.hpp>
#include <Ancona/Engine/Loading/FunctionInflater.hpp>
#include <Ancona/Engine/Loading/StaticInflater.hpp>

namespace ild
{

/**
 * @brief Manages the map of inflators for loading in save data.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class InflaterMap
{
    public:
        /**
         * @brief Adds a static inflater to the type map.
         *
         * @param key Key of the inflater.
         */
        template <typename T>
        void AddStatic(std::string key)
        {
            _typeMap.emplace(
                    key, 
                    std::unique_ptr<AbstractInflater>(
                        new StaticInflater<T>()));
        }

        /**
         * @brief Adds a dynamic inflater to the type map.
         *
         * @param key Key of the inflater.
         * @param object The factory used to inflate the objects.
         */
        template <typename T>
        void AddDynamic(std::string key, T & object)
        {
            _typeMap.emplace(
                    key, 
                    std::unique_ptr<AbstractInflater>(
                        new DynamicInflater<T>(object)));
        }

        /**
         * @brief Adds a functional inflater to the type map.
         *
         * @param key Key of the inflater.
         * @param inflaterFunction Function to do the inflating.
         */
        void AddFunctional(
                std::string key, 
                const std::function<void *(
                    const Json::Value, 
                    const Entity entity, 
                    LoadingContext * loadingContext)> inflaterFunction);

        /**
         * @brief Adds an inflater to the type map.
         *
         * @param key Key of the inflater.
         * @param inflater Inflater to add.
         */
        void AddAbstract(std::string key, AbstractInflater * inflater);

        /**
         * @brief Get the inflater from the map.
         *
         * @param key Key of the inflater.
         *
         * @return The requested inflater.
         */
        AbstractInflater * GetInflater(std::string key);

    private:
        /**
         * @brief Map of keys to respective inflators.
         */
        std::unordered_map<std::string, std::unique_ptr<AbstractInflater> > _typeMap;
};

}

#endif
