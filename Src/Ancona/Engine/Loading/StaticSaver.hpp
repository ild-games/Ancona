#ifndef Ancona_Engine_Loading_StaticSaver_H_
#define Ancona_Engine_Loading_StaticSaver_H_

#include <Ancona/Engine/Loading/AbstractSaver.hpp>

namespace ild
{

/**
 * @brief Used to save an object to JSON using a static factory method on the class.
 *
 * @tparam T Class to be saved. It must have a static function with the signature:
 *              Json::Value Save
 *
 * @author Tucker Leink
 */
template <typename T>
class StaticSaver : public AbstractSaver
{
    public:
        /**
         * @brief Call T::Save on the Template type to inflate an instance of the class.
         *
         * @param entity Entity associated with this save.
         * @param saverContext SaverContext at the time of this save.
         *
         * @return JSON it was saved to.
         */
        Json::Value Save(
                const Entity & entity,
                SaverContext * saverContext) override
        {
            return T::Save(
                    entity,
                    saverContext);
        }
};

}

#endif
