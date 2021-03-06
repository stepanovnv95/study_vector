#include <functional>
#include <gtest/gtest.h>
#include "Vector.h"
#include "mocks.h"


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

TEST(StudyVectorTest, MoveConstructor)
{
    study::Vector<int> v1(1);
    v1[0] = 2;
    study::Vector<int> v2(std::move(v1));

    ASSERT_EQ(v2[0], 2);
}

TEST(StudyVectorTest, InitializerListConstructor)
{
    study::Vector<int> v({ -1, 0, 1 });
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0], -1);
    ASSERT_EQ(v[1], 0);
    ASSERT_EQ(v[2], 1);
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

TEST(StudyVectorTest, EmplacePush)
{
    study::Vector<CopyMoveMock> v;
    v.emplace_back();
    ASSERT_TRUE(v[0].defaultConstructed);
}

TEST(StudyVectorTest, PushBack)
{
    study::Vector<int> v;
    v.push_back(0);

    ASSERT_EQ(v.size(), 1);
    ASSERT_GT(v.capacity(), 1);
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

TEST(StudyVectorTest, ResizeUp)
{
    study::Vector<int> v;
    v.push_back(-2);
    v.resize(2);

    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], -2);

    v.resize(100);
    ASSERT_EQ(v.size(), 100);
    ASSERT_EQ(v[0], -2);
}

TEST(StudyVectorTest, ResizeDown)
{
    ConstructDestructCounterMock_constructed = 0;
    ConstructDestructCounterMock_destructed = 0;
    study::Vector<ConstructDestructCounterMock> v(10);
    v.resize(5);
    ASSERT_EQ(ConstructDestructCounterMock_constructed, 10);
    ASSERT_EQ(ConstructDestructCounterMock_destructed, 5);
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

TEST(StudyVectorTest, RangeFor)
{
    study::Vector<int> v;
    v.push_back(-1);
    v.push_back(-1);
    v.push_back(-1);

    size_t counter = 0;
    for (auto value : v) {
        ASSERT_EQ(value, -1);
        ++counter;
    }
    ASSERT_EQ(counter, 3);
}

TEST(StudyVectorTest, CopyOnReallocate)
{
    study::Vector<CopyMoveMock> v(1);
    v.resize(100);
    const CopyMoveMock& mock = v[0];
    ASSERT_FALSE(mock.defaultConstructed);
    ASSERT_TRUE(mock.copyConstructed);
    ASSERT_FALSE(mock.moveConstructed);
}

TEST(StudyVectorTest, MoveOnReallocate)
{
    study::Vector<CopyNoexceptMoveMock> v(1);
    v.resize(100);
    const CopyNoexceptMoveMock& mock = v[0];
    ASSERT_FALSE(mock.defaultConstructed);
    ASSERT_FALSE(mock.copyConstructed);
    ASSERT_TRUE(mock.moveConstructed);
}

TEST(StudyVectorTest, ThrowOnConstructFromSize)
{
    ConstructDestructCounterMock_constructed = 0;
    ConstructDestructCounterMock_destructed = 0;
    ConstructDestructCounterWithThrowOnCopyMock_constructBeforeThrow = 2;
    ASSERT_ANY_THROW(study::Vector<ConstructDestructCounterWithThrowOnConstructMock> v(5));
    ASSERT_EQ(ConstructDestructCounterMock_constructed, 3);
    ASSERT_EQ(ConstructDestructCounterMock_destructed, 3);
}

TEST(StudyVectorTest, StdCopy)
{
    std::vector<int> stdVector = {1, 2, 3};
    study::Vector<int> studyVector(stdVector.size());
    std::copy(stdVector.cbegin(), stdVector.cend(), studyVector.begin());
    ASSERT_EQ(studyVector[0], 1);
    ASSERT_EQ(studyVector[1], 2);
    ASSERT_EQ(studyVector[2], 3);
}

TEST(StudyVectorTest, StdFind)
{
    study::Vector<char> v = {'x', 'y', 'z'};
    auto findIt = std::find(v.cbegin(), v.cend(), 'y');
    ASSERT_EQ(*findIt, 'y');
    findIt = std::find(v.cbegin(), v.cend(), 'a');
    ASSERT_EQ(findIt, v.cend());
}

TEST(StudyVectorTest, Pointer)
{
    int x = 1;
    study::Vector<int*> v;
    v.push_back(&x);
    *v[0] = 2;
    ASSERT_EQ(x, 2);
}

TEST(StudyVectorTest, StdRef)
{
    int x = 1;
    study::Vector<std::reference_wrapper<int>> v;
    v.push_back(std::ref(x));
    int &cx = v[0];
    ++cx;
    ASSERT_EQ(x, 2);
}
