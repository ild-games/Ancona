#ifndef Ancona_Engine_Serializing_ClassConstructor_H_
#define Ancona_Engine_Serializing_ClassConstructor_H_

namespace ild
{

/**
 * @brief Template that is used by the loading framework to construct objects.  The point
 * is it can be specialized to prevent construction or to construct an object using something
 * other than the default constructor.
 *
 * @author Jeff Swenson
 *
 * @tparam T Type that is constructed.
 */
template <typename T> class ClassConstructor
{
  public:
    static T *Construct()
    {
        return new T();
    }
};

} // namespace ild

/**
 * @brief Used to specify that a class is abstract and should not be constructed
 * by the loading system.
 *
 * Generates a ClassConstructor template specialization for an
 * abstract class.  Instead of calling the constructor it calls an assert that
 * prevents the abstract class from being initialized.
 *
 * @param CLASS Abstract class that cannot be serialized.
 */
#define GENERATE_ABSTRACT_CLASS_CONSTRUCTOR(CLASS)                                                                     \
    namespace ild                                                                                                      \
    {                                                                                                                  \
    template <> class ClassConstructor<CLASS>                                                                          \
    {                                                                                                                  \
      public:                                                                                                          \
        static CLASS *Construct()                                                                                      \
        {                                                                                                              \
            ILD_Assert(false, "Unable to construct abstract class #CLASS");                                            \
            return nullptr;                                                                                            \
        }                                                                                                              \
    };                                                                                                                 \
    }

#endif
