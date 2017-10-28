#include <iostream>
#include <asl.h>

#include <Ancona/System/Log.hpp>

#import <Foundation/Foundation.h>

using namespace ild;

void LogControls::_log(const std::string & msg)
{
    NSString * iOSMsg = [NSString stringWithUTF8String:msg.c_str()];
    NSLog(iOSMsg);
}
