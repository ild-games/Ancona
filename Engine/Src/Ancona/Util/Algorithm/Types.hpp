#ifndef Ancona_Util_Algorithm_Types_hpp
#define Ancona_Util_Algorithm_Types_hpp

/**
 * @description Generates a series of templates that can be used to test if a
 * class contains a specific method.  The templates will be generated in the current
 * namespace. The macro must be placed outside of a class definition.
 *
 * Usage:
 * GENERATE_METHOD_TESTER(Foo)
 *
 * void bar(int arg1, int arg2, std::true_type)
 * {
 *     std::cout << "Bar True " << arg1 << arg2;
 * }
 *
 * void bar(int arg1, int arg2, std::false_type)
 * {
 *     std::cout << "Bar False " << arg1 << arg2;
 * }
 *
 * bar(4, 2, HasMethod::Foo<AwesomeClass,int>());
 *
 * Will print Bar True 42 if AwesomeClass contains the method Foo(int).  Will
 * print Bar False 42 if it does not contain the method.
 *
 * @param METHOD_NAME Name of the method that will be tested for.
 *
 * @author Jeff Swenson
 */
#define GENERATE_METHOD_TESTER(METHOD_NAME)                                                                            \
    namespace HasMethod                                                                                                \
    {                                                                                                                  \
    namespace Internal                                                                                                 \
    {                                                                                                                  \
    template <typename T, typename... Args>                                                                            \
    constexpr auto METHOD_NAME(int) -> decltype((*(T *)NULL).METHOD_NAME((*(Args *)NULL)...), std::true_type())        \
    {                                                                                                                  \
        return std::true_type();                                                                                       \
    }                                                                                                                  \
    template <typename... Args> constexpr std::false_type METHOD_NAME(float)                                           \
    {                                                                                                                  \
        return std::false_type();                                                                                      \
    }                                                                                                                  \
    }                                                                                                                  \
    template <typename... Args> constexpr auto METHOD_NAME() -> decltype(Internal::METHOD_NAME<Args...>(0))            \
    {                                                                                                                  \
        return Internal::METHOD_NAME<Args...>(0);                                                                      \
    }                                                                                                                  \
    }

#endif
