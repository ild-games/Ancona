#ifndef Ancona_Engine_Loading_StaticInflater_H_
#define Ancona_Engine_Loading_StaticInflater_H_

#include <Ancona/Engine/Loading/AbstractInflater.hpp>

namespace ild
{

/**
 * @brief Used to inflate an object from JSON using a static factory method
 * on the class.
 *
 * @tparam T Class to be inflated.  It must have a static function with the
 * signature T * Inflate(const Json::Value &)
 * @author Jeff Swenson
 */
template <typename T>
class StaticInflater : public AbstractInflater
{
    public:
        /**
         * @brief Call T::Inflate(const Json::Value &) on the Template 
         * type to inflate an instance of the class.
         *
         * @param object JSON to be inflated into the object.
         * @param entity Entity associated with this inflation.
         * @param loadingContext LoadingContext at the time of this inflate.
         *
         * @return A pointer to the inflated object.
         */
        void * Inflate(
                const Json::Value & object,
                const Entity & entity,
                LoadingContext * loadingContext) override 
        {
            return T::Inflate(
                    object,
                    entity,
                    loadingContext);
        }
};

}

#endif
