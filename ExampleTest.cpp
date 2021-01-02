#include "gtest/gtest.h"
#include <vector>


TEST(ExampleTest, StdVectorSize) {
    std::vector<int> v;
    ASSERT_EQ(v.size(), 0);
    v.push_back(int());
    ASSERT_EQ(v.size(), 1);
}
