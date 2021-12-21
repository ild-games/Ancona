#pragma once

#include <sstream>
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
    static void _log(std::ostringstream & stream) { _log(stream.str()); }
};

} // namespace ild

#define ILD_Log(message)                      \
    {                                         \
        std::ostringstream stream;            \
        stream << message;                    \
        ild::LogControls::_log(stream.str()); \
    }
