#ifndef Ancona_Engine_Loading_AbstractInflater_H_
#define Ancona_Engine_Loading_AbstractInflater_H_

#include <string>

#include <json/json.h>

namespace ild
{

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
         *
         * @return A pointer to the inflated object.
         */
        virtual void * Inflate(const Json::Value & object) = 0;

        /**
         * @brief Create an instance of a class from the JSON object.  The
         * class that is inflated is determined by the child of the 
         * AbstractLoader. The object will be casted to the specified type.
         *
         * @tparam T Type to cast the inflated object to.
         * @param object JSON to be inflated into the object.
         *
         * @return A pointer casted to the specified type.
         */
        template <typename T>
        T * InflateTo(const Json::Value & object)
        {
            return dynamic_cast<T>(Inflate(object));
        }
};

}

#endif
