#ifndef ImpossibleDuck_Screens_ImpossibleScreen_H_
#define ImpossibleDuck_Screens_ImpossibleScreen_H_

#include <memory>

#include <Ancona/Framework/Screens/AbstractScreen.hpp>
#include "../Systems/ImpossibleGameSystems.hpp"

namespace ild
{

class ImpossibleScreen : public AbstractScreen
{
    public:
        ImpossibleScreen(
                ScreenManager & manager,
                ImpossibleInputHandler * inputHandler);

        void Update(float delta);

        void Init();

        void Draw(float delta);

        /* getters and setters */
        ScreenSystemsContainer * systemsContainer() override { return _systems.get(); }
    private:
        std::unique_ptr<ImpossibleInputHandler> _inputHandler;
        std::unique_ptr<ImpossibleGameSystems> _systems;
        Entity player;

};

}
#endif
