#ifndef Ancona_Engine_Loading_MapLoader_H_
#define Ancona_Engine_Loading_MapLoader_H_

#include <memory>
#include <string>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Engine/Loading/LoadingContext.hpp>
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
    /**
     * @brief State the loader is in.
     */
    enum LoadingState 
    {
        LoadingMapFile,
        LoadingAssets,
        LoadingEntities,
        LoadingComponents,
        DoneLoading
    };

    public:
        /**
         * @brief Create a loader to initialize the systems.
         *
         * @param key Key that describes the map the screen is currently on.
         * @param systems Instance of the system container for the screen being loaded.
         */
        MapLoader(std::string key, ScreenSystemsContainer & systems);

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

        /* getters and setters */
        std::shared_ptr<RequestList> GetRequestList() { return _request; }

    private:

        void LoadMapFile();
        void LoadAssets();
        void LoadEntities();
        void LoadComponents();
        void LoadSpecifiedSystem(std::pair<std::string, AbstractSystem *> systemNamePair, Archive & currentArc);

        /**
         * @brief Key that describes the map the screen is currently on.
         */
        std::string _key;
        /**
         * @brief List of assets needed by the map.
         */
        std::shared_ptr<RequestList> _request;
        /**
         * @brief State in the loading process that the object is in.
         */
        LoadingState _state = LoadingMapFile;
        /**
         * @brief Root of the map json being loaded.
         */
        Json::Value _mapRoot;
        /**
         * @brief Root of the save json for the file.
         */
        Json::Value _saveRoot;
        /**
         * @brief Loading context for the current load.
         */
        std::unique_ptr<LoadingContext> _loadingContext;
        /**
         * @brief Profile of the game session.
         */
        int _profile;
};

}

#endif
