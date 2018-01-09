#ifndef Ancona_Util_Assert_H_
#define Ancona_Util_Assert_H_

#include <ostream>
#include <string>
#include <stdexcept>

namespace ild
{

class AssertException : public std::runtime_error
{
    public:
        AssertException(const std::string & message);
};

class AssertControls
{
    public:
        /**
         * @brief If set to true Assert will throw an exception on failure.  If set to false it will
         * not.  This value defaults to true.
         *
         * @param value Bool that determines the setting.
         */
        static void SetThrowException(bool value);
        /**
         * @brief If an error stream is set then when asserts fail it will be logged to the stream.
         * If null is given as the error stream then no failed asserts will be logged.
         *
         * @param errorStream Stream that errors should be output to.
         */
        static void SetErrorStream(std::ostream * errorStream);

        /**
         * @brief Used to implement assert.  Should not be used outside of this file.
         */
        static void _ild_assert(bool condition, const std::string & message, const char * fileName, int lineNumber);
    private:
        static bool _throwException;
        static std::ostream * _errorStream;
};

}

#ifdef NDEBUG // CMake defines the NDEBUG macro for release builds.
#define ILD_Assert(condition, message) {}
#endif

#ifndef NDEBUG
#define ILD_Assert(condition,message) {\
    ild::AssertControls::_ild_assert(condition, message, __FILE__, __LINE__);\
}
#endif

#endif
