#ifndef Ancona_Engine_Loading_AbstractInflater_H_
#define Ancona_Engine_Loading_AbstractInflater_H_

#include <string>

#include <json/json.h>

#include <Ancona/Engine/EntityFramework/Entity.hpp>


namespace ild
{

class LoadingContext;

/**
 * @brief AbstractInflater used to polymorphically construct objects
 *  from JSON.
 * @author Jeff Swenson
 */
class AbstractInflater
{
    public:
        /**
         * @brief Create an instance of a class from the JSON object.  The
         * class that is inflated is determined by the child of the 
         * AbstractLoader.
         *
         * @param object JSON to be inflated into the object.
         * @param entity Entity associated with this inflation.
         * @param loadingContext LoadingContext at the time of this inflate.
         *
         * @return A pointer to the inflated object.
         */
        virtual void * Inflate(
                const Json::Value & object,
                const Entity entity,
                LoadingContext * loadingContext) = 0;

        /**
         * @brief Create an instance of a class from the JSON object.  The
         * class that is inflated is determined by the child of the 
         * AbstractLoader. The object will be casted to the specified type.
         *
         * @tparam T Type to cast the inflated object to.
         * @param object JSON to be inflated into the object.
         * @param entity Entity associated with this inflation.
         * @param loadingContext LoadingContext at the time of this inflate.
         *
         * @return A pointer casted to the specified type.
         */
        template <typename T>
        T * InflateTo(
                const Json::Value & object,
                const Entity entity,
                LoadingContext * loadingContext)
        {
            return dynamic_cast<T>(Inflate(object, entity, loadingContext));
        }
};

}

#endif
