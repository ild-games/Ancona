#ifndef ImpossibleGame_Systems_CounterSystem_H_
#define ImpossibleGame_Systems_CounterSystem_H_

#include <Ancona/Framework/EntityFramework/UnorderedSystem.hpp>
#include <Ancona/Framework/Serializing/Serializing.hpp>

namespace ild
{

class CounterComponent
{
    public:
        CounterComponent();

        CounterComponent(
                int startingNumber,
                int countInterval);

        void AddCounter();

        void FetchDependencies(const Entity & entity);

        void Serialize(Archive & arc);

        /* getters and setters */
        void counter(int counter) { _counter = counter; }
        void countInterval(int countInterval) { _countInterval = countInterval; }
        int counter() { return _counter; }
        int countInterval() { return _countInterval; }

    private:
        int _counter;
        int _countInterval;
};

class CounterSystem : public UnorderedSystem<CounterComponent>
{
    public:
        CounterSystem(
                std::string name,
                SystemManager & manager);

        void Update(float delta);

        CounterComponent * CreateComponent(
                const Entity & entity,
                int startingNumber = 0,
                int countInterval = 1);

};

}

#endif
