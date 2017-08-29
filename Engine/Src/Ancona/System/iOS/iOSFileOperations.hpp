#ifndef Ancona_Systems_iOS_iOSFileOperations_H_
#define Ancona_Systems_iOS_iOSFileOperations_H_

#include <Ancona/System/FileOperations.hpp>

namespace ild
{

/**
 * @brief File operations specific to the iOS file operating system.
 */
class iOSFileOperations
{
    friend class FileOperations;

    private:
        static const std::string & iOSFileOperations::ResourceDir();
};

}

#endif
