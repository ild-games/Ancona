#ifndef Ancona_System_Android_Log_H_
#define Ancona_System_Android_Log_H_

#include <string>

namespace ild
{

/**
 * @brief Log functions a platform must implement.
 *
 * @author Tucker Lein
 */
class LogControls
{
    public:
        /**
         * @brief Used to implement the log macro, should not be used outside of this file.
         *
         * @param msg Message to print out
         */
        static void _log(const std::string & msg);
};

}

#define ILD_Log(message) {\
    LogControls::_log(message);\
}

#endif
