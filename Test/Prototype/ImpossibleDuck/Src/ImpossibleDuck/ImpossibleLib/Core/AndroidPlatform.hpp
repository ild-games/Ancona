#ifndef Test_Prototype_ImpossibleDuck_Core_AndroidPlatform_H_
#define Test_Prototype_ImpossibleDuck_Core_AndroidPlatform_H_

#include "PlatformBase.hpp"
#include "../Input/ImpossibleTouch.hpp"

namespace ild
{

class AndroidPlatform : public PlatformBase
{
    public:
        ImpossibleTouch * inputHandler() override;
};

}

#endif
