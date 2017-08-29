#import <Foundation/Foundation.h>

#include <Ancona/System/iOS/iOSFileOperations.hpp>

using namespace ild;

const std::string & iOSFileOperations::ResourceDir() 
{
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *objcResourceDir = [bundle resourcePath];
    const char *cStrResourceDir = [objcResourceDir fileSystemRepresentation];
    return std::string(cStrResourceDir);
}
