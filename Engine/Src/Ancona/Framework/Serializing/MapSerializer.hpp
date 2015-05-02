#ifndef Ancona_Engine_Serializing_MapSerializer_H_
#define Ancona_Engine_Serializing_MapSerializer_H_

#include <memory>
#include <string>

#include <jsoncpp/json/json.h>

#include <Ancona/Framework/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Framework/EntityFramework/AbstractSystem.hpp>
#include "SerializingContext.hpp"
#include <Ancona/Framework/Resource/RequestList.hpp>

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
         */
        MapSerializer(std::string key, ScreenSystemsContainer & systems);

        /**
         * @brief Continue the loading process of the Map.
         *
         * @return True if the map is still loading.  False otherwise.
         */
        bool ContinueLoading();

        /* getters and setters */
        std::shared_ptr<RequestList> requestList() { return _request; }

    private:

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
        SerializerState _state = LoadingMapFile;
        /**
         * @brief Root of the map json being loaded.
         */
        Json::Value _mapRoot;
        /**
         * @brief Root of the save json for the file.
         */
        Json::Value _saveRoot;
        /**
         * @brief Serializing context for the current load.
         */
        std::unique_ptr<SerializingContext> _loadingContext;
        /**
         * @brief Profile of the game session.
         */
        int _profile;
};

}

#endif
