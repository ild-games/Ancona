#ifndef Ancona_Engine_Loading_MapSaver_H_
#define Ancona_Engine_Loading_MapSaver_H_

#include <memory>
#include <string>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/Core/Systems/ScreenSystemsContainer.hpp>
#include <Ancona/Engine/Loading/SaverContext.hpp>

namespace ild
{

/**
 * @brief MapSaver is used to save the Entity System to a JSON map file.
 *
 * @author Tucker Lein
 */
class MapSaver
{
    public:
        /**
         * @brief Create a saver to save the systems.
         *
         * @param key Key that describes the map the screen is currently on.
         * @param systems Instance of the system container for the screen being saved.
         */
        MapSaver(std::string key, ScreenSystemsContainer & system);

        /**
         * @brief Saves the entity data to the save file.
         */
        void Save();
        
        /**
         * @brief Loads in the save file.
         */
        void LoadSaveFile();

    private:
        /**
         * @brief Key that describes the map the screen is currently on.
         */
        std::string _key;
        /**
         * @brief JSON for the save file.
         */
        Json::Value _saveRoot;

        void SaveComponents();

};

}

#endif
