#ifndef Ancona_System_Log_H_
#define Ancona_System_Log_H_

#include <string>
#include <sstream>

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
        static void _log(std::ostream & stream) {
            std::ostringstream & stringStream = dynamic_cast<std::ostringstream&>(stream);
            _log(stringStream.str());
        }
};

}

#define ILD_Log(message) {\
    ild::LogControls::_log(message);\
}

#endif
