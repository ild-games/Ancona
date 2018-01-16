#ifndef Ancona_Engine_Serializing_MapSerializer_H_
#define Ancona_Engine_Serializing_MapSerializer_H_

#include <memory>
#include <string>

#include <Ancona/Framework/EntityFramework/AbstractSystem.hpp>
#include <Ancona/Framework/Resource/RequestList.hpp>
#include <Ancona/Framework/Serializing/SerializingContext.hpp>
#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/System/FileOperations.hpp>
#include <Ancona/Util/Json.hpp>

namespace ild
{

/**
 * @brief MapSerializer is used to serialize or deserialize an Entity System from a JSON map
 * file.
 *
 * @author Jeff Swenson
 * @author Tucker Lein
 */
class MapSerializer
{
    /**
     * @brief State the Serializer is in.
     */
    enum SerializerState
    {
        LoadingMetaData,
        LoadingMapFile,
        LoadingAssets,
        LoadingEntities,
        SerializingComponents,
        DoneSerializing
    };

    public:
        /**
         * @brief Create a serializer to initialize the systems.
         *
         * @param key Key that describes the map the screen is currently on.
         * @param systems Instance of the system container for the screen being serialized.
         * @param loading True if the MapSerializer is loading the map, false if it is saving it.
         * @param snapshotSave True if everything will be saved, otherwise only specified systems will be saved. Defaults to false.
         */
        MapSerializer(
                std::string key,
                ScreenSystemsContainer & systems,
                std::shared_ptr<RequestList> request,
                bool loading,
                bool snapshotSave = false);

        /**
         * @brief Continue the loading process of the Map.
         *
         * @return True if the map is still loading.  False otherwise.
         */
        bool ContinueLoading();

        /* getters and setters */
        std::shared_ptr<RequestList> requestList() { return _request; }

    private:

        void LoadMetaData();
        void LoadMapFile();
        void LoadAssets();
        void LoadEntities();
        void SerializeComponents();
        void SerializeSpecifiedSystem(std::pair<std::string, AbstractSystem *> systemNamePair, Archive &currentArc);

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
        SerializerState _state = LoadingMetaData;
        /**
         * @brief Root of the map json being loaded.
         */
        rapidjson::Document _mapRoot;
        /**
         * @brief Root of the save json for the file.
         */
        rapidjson::Document _saveRoot;
        /**
         * @brief Root of the save json for the specified profile being serialized.
         */
        rapidjson::Value _saveProfileRoot;
        /**
         * @brief Name of the map being serialized.
         */
        std::string _mapName;
        /**
         * @brief Serializing context for the current load.
         */
        std::shared_ptr<SerializingContext> _loadingContext;
        /**
         * @brief Profile of the game session.
         */
        int _profile;
        /**
         * @brief True if the MapSerializer is loading the map, false if it is saving it.
         */
        bool _loading;
        /**
         * @brief True if the saving will save everything, false if not.
         */
        bool _snapshotSave;

        static std::unique_ptr<rapidjson::Document> _lastMapRoot;
        static std::string _lastMapLoaded;
};

}

#endif
