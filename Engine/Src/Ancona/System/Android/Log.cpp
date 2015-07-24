#include <android/log.h>

#include <Ancona/System/Log.hpp>

using namespace ild;

void LogControls::_log(const std::string & msg)
{
    __android_log_print(ANDROID_LOG_VERBOSE, "com.sfml.example", "[Ancona] %s", msg.c_str());
}
