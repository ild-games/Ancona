#ifndef Test_Prototype_FlappyBirdTest_Platforms_Android_AndroidFactory_H_
#define Test_Prototype_FlappyBirdTest_Platforms_Android_AndroidFactory_H_

#include <Ancona/Engine/Screens/ScreenManager.hpp>
#include "InputDevices/FlappyTouch.hpp"
#include "Core/FactoryBase.hpp"

namespace ild
{

class AndroidFactory : public FactoryBase
{
    public:
        FlappyTouch * GetInputHandler(ScreenManager & screenManager);
};

}

#endif
