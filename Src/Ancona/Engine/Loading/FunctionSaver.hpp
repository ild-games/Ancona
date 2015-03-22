#ifndef Ancona_Engine_Loading_FunctionSaver_H_
#define Ancona_Engine_Loading_FunctionSaver_H_

#include <functional>

#include <Ancona/Engine/Loading/AbstractSaver.hpp>

namespace ild
{

/**
 * @brief A saver which uses a passed in function as the save function.
 *
 * @author Tucker Lein
 */
class FunctionSaver : public AbstractSaver
{
    public:
        /**
         * @brief Constructs the function saver with the given function.
         *
         * @param saverFunc Function to be used as the saver.
         */
        FunctionSaver(
                std::function<Json::Value(
                    const Entity & entity,
                    SaverContext * saverContext)> saverFunc) :
            _saverFunc(saverFunc) { }

        /**
         * @brief Saver that will be called from the map saver, simply passes it along to the saver function given to the FunctionSaver.
         *
         * @param entity Entity associated with this saver.
         * @param saverContext SaverContext at the time of this save.
         *
         * @return JSON containing the saved values.
         */
        Json::Value Save(
                const Entity & entity,
                SaverContext * saverContext) override
        {
            return _saverFunc(entity, saverContext);
        }

    private:
        std::function<Json::Value(const Entity & entity, SaverContext * saverContext)> _saverFunc;
};

}

#endif
