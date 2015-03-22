#ifndef Ancona_Engine_Loading_AbstractSaver_H_
#define Ancona_Engine_Loading_AbstractSaver_H_

#include <string>

#include <jsoncpp/json/json.h>

#include <Ancona/Engine/EntityFramework/Entity.hpp>

namespace ild
{

class SaverContext;

/**
 * @brief AbstractSaver used to polymorphically save objects to JSON.
 *
 * @author Tucker Lein
 */
class AbstractSaver
{
    public:
        /**
         * @brief Saves an instance of a class to a JSON object. The class that is 
         *        saved is determined by the child of the AbstractLoader.
         *
         * @param entity Entity associated with this save.
         * @param saverContext SaverContext at the time of this inflate.
         *
         * @return JSON that was saved.
         */
        virtual Json::Value Save(
                const Entity & entity,
                SaverContext * saverContext) = 0;

};

}

#endif 
