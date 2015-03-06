#ifndef Ancona_Engine_Loading_FunctionInflater_H_
#define Ancona_Engine_Loading_FunctionInflater_H_

#include <functional>

#include <Ancona/Engine/Loading/AbstractInflater.hpp>

namespace ild
{

/**
 * @brief An inflater which uses a passed in function as the inflate function.
 *
 * @author Tucker Lein
 */
class FunctionInflater : public AbstractInflater
{
    public:
        /**
         * @brief Constructs the function inflater with the given function.
         *
         * @param inflaterFunc Function to be used as the inflater.
         */
        FunctionInflater(
                std::function<void *(
                    const Json::Value, 
                    const Entity entity, 
                    LoadingContext * loadingContext)> inflaterFunc) : 
            _inflaterFunc(inflaterFunc) { }

        /**
         * @brief Inflater that will be called from the map loader, simply passes it along to the inflater function given to the FunctionInflater.
         *
         * @param object JSON to be inflated into the object.
         * @param entity Entity associated with this inflation.
         * @param loadingContext LoadingContext at the time of this inflate.
         *
         * @return A pointer to the inflated object.
         */
        void * Inflate(
                const Json::Value & object,
                const Entity entity,
                LoadingContext * loadingContext) override 
        {
            return _inflaterFunc(object, entity, loadingContext);
        }

    private: 
        std::function<void *(const Json::Value, const Entity entity, LoadingContext * loadingContext)> _inflaterFunc;
            
};

}

#endif
