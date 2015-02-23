#ifndef Ancona_Engine_Loading_MapLoader_H_
#define Ancona_Engine_Loading_MapLoader_H_

#include <string>

#include <json/json.h>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Engine/Resource/RequestList.hpp>

namespace ild
{

/**
 * @brief MapLoader is used to intialize an Entity System from a JSON map
 * file.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class MapLoader
{
    enum LoadingState 
    {
        LoadingMapFile,
        LoadingAssets,
        LoadingEntities
    };

    public:
        /**
         * @brief Create a loader to initialize the systems.
         *
         * @param key Key that describes the screen file.
         * @param systems Systems that the entities should be loaded into.
         */
        MapLoader(std::string key, SystemManager & systems);

        /**
         * @brief  Calculates the percentage of map loaded.
         *
         * @return Percentage between 0..1 of the map loaded.
         */
        float PercentLoaded();

        /**
         * @brief Continue the loading process of the Map.
         *
         * @return True if the map is still loading.  False otherwise.
         */
        bool ContinueLoading();

    private:

        void LoadMapFile();
        void LoadAssets();
        void LoadEntities();

        /**
         * @brief Key that describes the map.
         */
        std::string _key;
        /**
         * @brief Pointer to the System Manager that contains the systems
         * the entities should be loaded into.
         */
        SystemManager & _manager;
        /**
         * @brief List of assets needed by the map.
         */
        RequestList _request;
        /**
         * @brief State in the loading process that the object is in.
         */
        LoadingState _state = LoadingMapFile;
        /**
         * @brief Root of the map json being loaded.
         */
        Json::Value _root;
};

}

#endif
