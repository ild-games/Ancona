#include <iostream>
#include <asl.h>

#include <Ancona/System/Log.hpp>

using namespace ild;

void LogControls::_log(const std::string & msg)
{
    asl_log(NULL, NULL, ASL_LEVEL_ERR, "[Ancona] " + msg);
}
