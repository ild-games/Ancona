#ifndef Test_Prototype_ImpossibleDuck_Core_DesktopPlatform_H_
#define Test_Prototype_ImpossibleDuck_Core_DesktopPlatform_H_

#include "PlatformBase.hpp"
#include "../Input/ImpossibleKeyboard.hpp"

namespace ild
{

class DesktopPlatform : public PlatformBase
{
    public:
        ImpossibleKeyboard * inputHandler() override;
};

}

#endif
