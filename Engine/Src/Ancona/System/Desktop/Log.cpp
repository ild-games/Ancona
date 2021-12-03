#include <iostream>

#include <Ancona/System/Log.hpp>

using namespace ild;

void LogControls::_log(const std::string &msg)
{
    std::cout << "[Ancona] " << msg << std::endl;
}
