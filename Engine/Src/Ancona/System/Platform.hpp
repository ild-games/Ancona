#ifndef Ancona_Systems_Platform_H_
#define Ancona_Systems_Platform_H_

#include <iostream>
#include <memory>

namespace ild
{

/**
 * @brief 
 */
class Platform
{
    public:
        static std::unique_ptr<std::istream> GetInputFileStream(const std::string & desiredFile);          
};

}

#endif
