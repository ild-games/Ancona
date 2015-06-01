#include <gtest/gtest.h>

#include <vector>

#include <Ancona/Util/Algorithm/ContainerExtensions.hpp>

TEST(ContainerExtensions, Contains)
{
    std::vector<std::string> stringVector = { "hello", "goodbye", "test", "testing" };
    
    ASSERT_EQ(alg::contains(stringVector, "hello"), true) << "'hello' should be considered contained";
    ASSERT_EQ(alg::contains(stringVector, "nothello"), false) << "'nothello' should not be considered contained" ;
}
