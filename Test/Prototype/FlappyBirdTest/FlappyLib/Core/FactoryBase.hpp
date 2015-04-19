#ifndef Test_Prototype_FlappyBirdTest_Core_FactoryBase_H_
#define Test_Prototype_FlappyBirdTest_Core_FactoryBase_H_

#include <Ancona/Framework/Screens/ScreenManager.hpp>
#include "../InputDevices/FlappyInputHandler.hpp"

namespace ild
{

class FactoryBase
{
    public:
        virtual FlappyInputHandler * GetInputHandler(ScreenManager & screenManager) = 0; 
};

}

#endif
