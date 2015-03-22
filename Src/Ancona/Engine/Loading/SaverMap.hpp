#ifndef Ancona_Engine_Loading_SaverMap_H_
#define Ancona_Engine_Loading_SaverMap_H_

#include <memory>
#include <string>
#include <unordered_map>

#include <Ancona/Engine/Loading/AbstractSaver.hpp>
#include <Ancona/Engine/Loading/DynamicSaver.hpp>
#include <Ancona/Engine/Loading/FunctionSaver.hpp>
#include <Ancona/Engine/Loading/StaticSaver.hpp>

namespace ild
{

/**
 * @brief Manages the map of savers for saving in save data.
 *
 * @author Tucker Lein
 */
class SaverMap
{
    public:
        /**
         * @brief Adds a static saver to the type map.
         *
         * @param key Key of the inflater.
         */
        template <typename T>
        void AddStatic(std::string key)
        {
            _typeMap.emplace(
                    key,
                    std::unique_ptr<AbstractSaver>(
                        new StaticSaver<T>()));
        }

        /**
         * @brief Adds a dynamic saver to the type map.
         *
         * @param key Key of the saver.
         * @param object The factory used to save the objects.
         */
        template <typename T>
        void AddDynamic(std::string key, T & object)
        {
            _typeMap.emplace(
                    key,
                    std::unique_ptr<AbstractSaver>(
                        new DynamicSaver<T>(object)));
        }

        /**
         * @brief Adds a functional saver to the type map.
         *
         * @param key Key of the saver.
         * @param saverFunction Function to do the saving.
         */
        void AddFunctional(
                std::string key,
                const std::function<Json::Value(
                    const Entity & entity,
                    SaverContext * saverContext)> saverFunction)
        {
            _typeMap.emplace(
                    key,
                    std::unique_ptr<AbstractSaver>(
                        new FunctionSaver(saverFunction)));
        }

        /**
         * @brief Adds a saver to the type map.
         *
         * @param key Key of the inflater.
         * @param saver Saver to add.
         */
        void AddAbstract(std::string key, AbstractSaver * saver)
        {
            _typeMap.emplace(
                    key,
                    std::unique_ptr<AbstractSaver>(saver));
        }

        /**
         * @brief Get the saver from the map.
         *
         * @param key Key of the saver.
         *
         * @return The requested saver.
         */
        AbstractSaver * GetSaver(std::string key)
        {
            return _typeMap[key].get();
        }

    private:
        /**
         * @brief Map of keys to respective savers.
         */
        std::unordered_map<std::string, std::unique_ptr<AbstractSaver> > _typeMap;
};

}

#endif
