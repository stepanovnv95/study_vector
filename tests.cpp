#include <gtest/gtest.h>
#include "Vector.h"


TEST(StudyVectorTest, DefaultConstructor)
{
    study::Vector<int> v;

    ASSERT_EQ(v.capacity(), 0);
    ASSERT_EQ(v.size(), 0);
}

TEST(StudyVectorTest, ConstructWithSize)
{
    size_t s = 4;
    study::Vector<int> v(s);

    ASSERT_EQ(v.capacity(), s);
    ASSERT_EQ(v.size(), s);
}

TEST(StudyVectorTest, CopyConstructor)
{
    study::Vector<int> v1(2);
    v1[0] = 1;
    v1[1] = 3;
    study::Vector<int> v2(v1);

    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 3);
    ASSERT_EQ(v1[0], v2[0]);
    ASSERT_EQ(v1[1], v2[1]);
}

TEST(StudyVectorTest, AssigmentCopy)
{
    study::Vector<int> v1(2);
    v1[0] = 4;
    v1[1] = 5;
    study::Vector<int> v2;
    v2 = v1;

    ASSERT_EQ(v1.size(), v2.size());
    ASSERT_EQ(v2[0], 4);
    ASSERT_EQ(v2[1], 5);
    ASSERT_EQ(v1[0], v2[0]);
    ASSERT_EQ(v1[1], v2[1]);
}

TEST(StudyVectorTest, MoveConstructor)
{
    study::Vector<int> v1(1);
    v1[0] = 2;
    study::Vector<int> v2(std::move(v1));

    ASSERT_EQ(v2[0], 2);
}

TEST(StudyVectorTest, AssigmentMove)
{
    study::Vector<int> v1(1);
    v1[0] = 4;
    study::Vector<int> v2;
    v2 = std::move(v1);

    ASSERT_EQ(v2[0], 4);
}

TEST(StudyVectorTest, Capacity)
{
    {
        study::Vector<int> v;
        ASSERT_EQ(v.capacity(), 0);
    }
    {
        study::Vector<int> v(6);
        ASSERT_EQ(v.capacity(), 6);
    }
}

TEST(StudyVectorTest, Size)
{
    {
        study::Vector<int> v;
        ASSERT_EQ(v.size(), 0);
    }
    {
        study::Vector<int> v(6);
        ASSERT_EQ(v.size(), 6);
    }
}

TEST(StudyVectorTest, AccessOperator)
{
    study::Vector<int> v1(1);
    v1[0] = 2;
    const study::Vector<int> &v2 = v1;

    ASSERT_EQ(v2[0], 2);
}

TEST(StudyVectorTest, PushBack)
{
    study::Vector<int> v;
    v.push_back(0);

    ASSERT_EQ(v.size(), 1);
    ASSERT_GE(v.capacity(), 1);
    ASSERT_EQ(v[0], 0);
}

TEST(StudyVectorTest, Swap)
{
    study::Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    study::Vector<int> v2;
    v2.push_back(3);
    v1.swap(v2);

    ASSERT_EQ(v1.size(), 1);
    ASSERT_EQ(v2.size(), 2);
    ASSERT_EQ(v1[0], 3);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
}

TEST(StudyVectorTest, Iteration)
{
    study::Vector<int> v(5);
    int counter = 1;
    for (auto it = v.begin(); it != v.end(); ++it) {
        *it = counter;
        ++counter;
    }
    counter = 1;
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        ASSERT_EQ(*it, counter);
        ++counter;
    }
}
