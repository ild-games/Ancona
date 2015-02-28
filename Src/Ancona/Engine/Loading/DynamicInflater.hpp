#ifndef Ancona_Engine_Loading_DynamicInflater_H_
#define Ancona_Engine_Loading_DynamicInflater_H_

namespace ild
{

/**
 * @brief Used to inflate an object from JSON using a member function of 
 * a class.
 *
 * @tparam T The class that has the factory inflater method.  It must have
 * a method with the 
 * @author Jeff Swenson
 */
template <typename T>
class DynamicInflater : public AbstractInflater
{
    public:
        /**
         * @brief Construct an instance of an inflater that will use the
         * supplied object as a factory.
         *
         * @param factory Reference of an object to use as the factory.
         */
        DynamicInflater(T & factory) : _factory(factory) {};

        /**
         * @brief Call factory.Inflate(const Json::Value &) on the Template
         * type to inflate an instance of class.
         *
         * @param object JSON to be inflated into the object.
         *
         * @return A pointer to the inflated object.
         */
        void * Inflate(const Json::Value & object) override
        {
            return _factory.Inflate(object);
        }
    private:
        T & _factory;
};

}

#endif
