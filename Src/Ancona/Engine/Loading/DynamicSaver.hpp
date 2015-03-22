#ifndef Ancona_Engine_Loading_DynamicSaver_H_
#define Ancona_Engine_Loading_DynamicSaver_H_

#include <Ancona/Engine/Loading/AbstractSaver.hpp>

namespace ild
{

/**
 * @brief Used to save an object to JSON using a member function of a class.
 *
 * @tparam T The class that has the factory saver method. 
 *
 * @author Tucker Lein
 */
template <typename T>
class DynamicSaver : public AbstractSaver
{
    public:
        /**
         * @brief Construct an instance of a saver that will use the supplied object as a factory.
         *
         * @param factory Reference of an object to use as the factory.
         */
        DynamicSaver(T & factory) : _factory(factory) { }

        /**
         * @brief Call factory.Save on the Template type to save an instance of the class.
         *
         * @param entity Entity associated with this save.
         * @param saverContext SaverContext at the time of this save.
         *
         * @return The JSON it saved itself to.
         */
        Json::Value Save(
                const Entity & entity,
                SaverContext * saverContext) override
        {
            return _factory.Save(entity, saverContext);
        }

    private:
        T & _factory;
};

}

#endif
