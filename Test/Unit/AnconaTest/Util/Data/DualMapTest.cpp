#include <gtest/gtest.h>

#include <Ancona/Util/Data/DualMap.hpp>

using namespace ild;

TEST(DualMap, SetAndRetrieve)
{
    DualMap<std::string, int> dualMap;

    dualMap.Add("Hello", 12);
    
    ASSERT_EQ(dualMap.GetValue("Hello"), 12) << "value is not set correctly";
    ASSERT_EQ(dualMap.GetKey(12), "Hello") << "key is not set correctly";
}

TEST(DualMap, CheckNoDuplicates)
{
    DualMap<std::string, int> dualMap;
    dualMap.Add("Hello", 12);

    EXPECT_THROW(dualMap.Add("Hello", 11), AssertException) << "key duplicate should not be allowed";
    EXPECT_THROW(dualMap.Add("Goodbye", 12), AssertException) << "value duplicate should not be allowed";
}

TEST(DualMap, Contains)
{
    DualMap<std::string, int> dualMap;
    dualMap.Add("Hello", 1);

    ASSERT_EQ(dualMap.ContainsKey("Hello"), true) << "set key is not recognized as being contained";
    ASSERT_EQ(dualMap.ContainsKey("hello"), false) << "incorrest key is thought to be contained on the DualMap";
    ASSERT_EQ(dualMap.ContainsValue(1), true) << "set value is not recognized as being contained";
    ASSERT_EQ(dualMap.ContainsValue(0), false) << "incorrest value is thought to be contained on the DualMap";
}

TEST(DualMap, Delete)
{
    DualMap<std::string, int> dualMap;
    dualMap.Add("Hello", 1);
    dualMap.Add("Goodbye", 2);

    dualMap.RemoveByKey("Hello");
    ASSERT_EQ(dualMap.ContainsKey("Hello"), false) << "key is not removed correctly when removing by key";
    ASSERT_EQ(dualMap.ContainsValue(1), false) << "value is not removed correctly when removing by key";
    ASSERT_EQ(dualMap.ContainsKey("Goodbye"), true) << "incorrect key was removed when removing by key";
    ASSERT_EQ(dualMap.ContainsValue(2), true) << "incorrect value was removed when removing by key";

    dualMap.Add("Later", 3);

    dualMap.RemoveByValue(2);
    ASSERT_EQ(dualMap.ContainsKey("Goodbye"), false) << "key is not removed correctly when removing by value";
    ASSERT_EQ(dualMap.ContainsValue(2), false) << "value is not removed correctly when removing by value";
    ASSERT_EQ(dualMap.ContainsKey("Later"), true) << "incorrect key was removed when removing by value";
    ASSERT_EQ(dualMap.ContainsValue(3), true) << "incorrect value was removed when removing by value";
}