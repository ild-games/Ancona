#ifndef Test_Prototype_FlappyBirdTest_Platforms_Android_DesktopFactory_H_
#define Test_Prototype_FlappyBirdTest_Platforms_Android_DesktopFactory_H_

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include "InputDevices/FlappyKeyboard.hpp"
#include "Core/FactoryBase.hpp"

namespace ild 
{

class DesktopFactory : public FactoryBase
{
    public:
        FlappyKeyboard * GetInputHandler(ScreenManager & screenManager);
};

}

#endif
