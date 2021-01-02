#include <gtest/gtest.h>
#include "Vector.h"


TEST(StudyVectorTest, DefaultSize)
{
    study::Vector<int> v;
    ASSERT_EQ(v.size(), 0);
}

TEST(StudyVectorTest, SizeAfterPushBack)
{
    study::Vector<int> v;
    v.pushBack(int());
    v.pushBack(int());
    ASSERT_EQ(v.size(), 2);
}
