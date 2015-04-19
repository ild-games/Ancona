
#include <gtest/gtest.h>
#include <utility>
#include <vector>

#include <Ancona/Engine/EntityFramework/SystemManager.hpp>
#include <Ancona/Util/Assert.hpp>
#include "MockSystem.hpp"

using namespace ild;

TEST(EntitySystem, CreatesUniqueEntities)
{
    SystemManager manager;
    std::vector<Entity> entities;
    for(int i = 0; i < 5; i++)
    {
        entities.push_back(manager.CreateEntity());
    }

    //Test the entities given for uniqueness
    for(int i = 0; i < 5; i++)
    {
        for(int n = 0; n < 5; n++)
        {
            if(i == n)
            {
                ASSERT_EQ(entities[i],entities[n]);
            }
            else
            {
                ASSERT_NE(entities[i],entities[n]);
            }
        }
    }
}

TEST(EntitySystem, RegisterAndUpdateSystem)
{
    SystemManager manager;
    MockSystem & system = *(new MockSystem(manager));
    Entity entity = manager.CreateEntity();
    MockComponent * component = system.CreateComponent(entity);

    ASSERT_FALSE(component->WasUpdated());

    manager.Update(10, UpdateStep::Update);

    ASSERT_TRUE(component->WasUpdated());
}

TEST(EntitySystem, DeleteEntity)
{
    SystemManager manager;
    MockSystem & system = *(new MockSystem(manager));
    std::vector<Entity> entity;
    std::vector<MockComponent *> component;
    for(int i = 0; i < 5; i++)
    {
        entity.push_back(manager.CreateEntity());
        component.push_back(system.CreateComponent(entity[i]));
    }

    ASSERT_EQ(entity.size(), system.ComponentCount());

    for(MockComponent * comp : component)
    {
        ASSERT_FALSE(comp->WasUpdated());
    }

    manager.Update(10,UpdateStep::Update); 

    for(MockComponent * comp : component)
    {
        ASSERT_TRUE(comp->WasUpdated());
        comp->ClearUpdate();
    }

    //Delete all entities but entity[1] and entity[4]
    manager.DeleteEntity(entity[0]);
    manager.DeleteEntity(entity[2]);
    manager.DeleteEntity(entity[3]);

    ASSERT_EQ(system.ComponentCount(), 2);

    ASSERT_FALSE(component[1]->WasUpdated());
    ASSERT_FALSE(component[4]->WasUpdated());

    manager.Update(10, UpdateStep::Update);

    ASSERT_TRUE(component[1]->WasUpdated());
    ASSERT_TRUE(component[4]->WasUpdated());
}

TEST(EntitySystem, RemoveComponent)
{
    SystemManager manager;
    MockSystem & system = *(new MockSystem(manager));
    std::vector<Entity> entity;
    std::vector<MockComponent *> component;
    for(int i = 0; i < 5; i++)
    {
        entity.push_back(manager.CreateEntity());
        component.push_back(system.CreateComponent(entity[i]));
    }

    ASSERT_EQ(entity.size(), system.ComponentCount());

    for(MockComponent * comp : component)
    {
        ASSERT_FALSE(comp->WasUpdated());
    }

    manager.Update(10,UpdateStep::Update); 

    for(MockComponent * comp : component)
    {
        ASSERT_TRUE(comp->WasUpdated());
        comp->ClearUpdate();
    }

    //Delete all entities but entity[1] and entity[4]
    system.RemoveComponent(entity[0]);
    system.RemoveComponent(entity[2]);
    system.RemoveComponent(entity[3]);

    ASSERT_EQ(system.ComponentCount(), 2);

    ASSERT_FALSE(component[1]->WasUpdated());
    ASSERT_FALSE(component[4]->WasUpdated());

    manager.Update(10, UpdateStep::Update);

    ASSERT_TRUE(component[1]->WasUpdated());
    ASSERT_TRUE(component[4]->WasUpdated());
}

TEST(EntitySystem, ComponentRemoved)
{
    SystemManager manager;
    MockSystem & system = *(new MockSystem(manager));
    Entity entity1 = manager.CreateEntity();
    Entity entity2 = manager.CreateEntity();

    system.CreateComponent(entity1);
    system.CreateComponent(entity2);

    ASSERT_FALSE(system.ComponentRemoved);

    system.RemoveComponent(entity2);
    ASSERT_TRUE(system.ComponentRemoved);

    system.ComponentRemoved = false;

    manager.DeleteEntity(entity1);
    ASSERT_TRUE(system.ComponentRemoved);

    ASSERT_EQ(system.ComponentCount(), 0);
}

TEST(EntitySystem, AssertGaurds)
{
    SystemManager manager;
    MockSystem & system = *(new MockSystem(manager));
    Entity entity1 = manager.CreateEntity();
    Entity entity3 = manager.CreateEntity();

    bool assertFailed = false;
    try
    {
        system.RemoveComponent(entity1);
    }
    catch (AssertException & e)
    {
        assertFailed = true;
    }
    catch (...)
    {
        //No other exception should be thrown
        ASSERT_FALSE(true);
    }
    ASSERT_TRUE(assertFailed);
    assertFailed = false;

    assertFailed = false;
    try
    {
        //The entity 1337 was never created
        manager.DeleteEntity(1337);
    }
    catch (AssertException & e)
    {
        assertFailed = true;
    }
    catch (...)
    {
        //No other exception should be thrown
        ASSERT_FALSE(true);
    }
    ASSERT_TRUE(assertFailed);
    assertFailed = false;

    system.CreateComponent(entity3);
    assertFailed = false;
    try
    {
        system.CreateComponent(entity3);
    }
    catch (AssertException & e)
    {
        assertFailed = true;
    }
    catch (...)
    {
        //No other exception should be thrown
        ASSERT_FALSE(true);
    }
    ASSERT_TRUE(assertFailed);
    assertFailed = false;
}

TEST(EntitySystem, KeyedEntityRetrival)
{
    SystemManager manager;
    new MockSystem(manager);
    Entity entity1 = manager.CreateEntity("EntityA");
    Entity entity2 = manager.CreateEntity("EntityB");

    ASSERT_EQ(entity1,manager.GetEntity("EntityA")) << "Incorrect entity fetched by key";
    ASSERT_EQ(entity2,manager.GetEntity("EntityB")) <<"Incorrect entity fetched by key";
    ASSERT_EQ(nullentity,manager.GetEntity("EntityC")) <<"nullentity should be returned if the key does not map to an entity";
}

TEST(EntitySystem, KeyedEntityRetrivalAfterDelete)
{
    SystemManager manager;
    new MockSystem(manager);
    Entity entity1 = manager.CreateEntity("EntityA");
    Entity entity2 = manager.CreateEntity("EntityB");

    ASSERT_EQ(entity1,manager.GetEntity("EntityA")) << "Incorrect entity fetched by key";
    ASSERT_EQ(entity2,manager.GetEntity("EntityB")) <<"Incorrect entity fetched by key";
    ASSERT_EQ(nullentity,manager.GetEntity("EntityC")) <<"nullentity should be returned if the key does not map to an entity";

    manager.DeleteEntity(entity1);

    ASSERT_EQ(nullentity,manager.GetEntity("EntityA")) << "Key for deleted entity should return nullentity";
    ASSERT_EQ(entity2,manager.GetEntity("EntityB")) <<"Incorrect entity fetched by key";
    ASSERT_EQ(nullentity,manager.GetEntity("EntityC")) <<"nullentity should be returned if the key does not map to an entity";


    entity1 = manager.CreateEntity("EntityA");

    ASSERT_EQ(entity1,manager.GetEntity("EntityA")) << "Entity key should be able to be reused after deleting the original entity";
    ASSERT_EQ(entity2,manager.GetEntity("EntityB")) <<"Incorrect entity fetched by key";
    ASSERT_EQ(nullentity,manager.GetEntity("EntityC")) <<"nullentity should be returned if the key does not map to an entity";
}
