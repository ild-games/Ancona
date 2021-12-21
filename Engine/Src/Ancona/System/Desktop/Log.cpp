#include <iostream>

#include <Ancona/System/Log.hpp>

namespace ild
{

void LogControls::_log(const std::string & msg)
{
    std::cout << "[Ancona] " << msg << '\n';
}

} // namespace ild
