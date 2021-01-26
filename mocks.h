#ifndef STUDY_VECTOR_MOCKS_H
#define STUDY_VECTOR_MOCKS_H


inline unsigned int ConstructDestructCounterMock_constructed = 0;
inline unsigned int ConstructDestructCounterMock_destructed = 0;

class ConstructDestructCounterMock
{
public:
    ConstructDestructCounterMock()
    {
        ++ConstructDestructCounterMock_constructed;
    }

    ~ConstructDestructCounterMock()
    {
        ++ConstructDestructCounterMock_destructed;
    }
};


inline unsigned int ConstructDestructCounterWithThrowOnCopyMock_constructBeforeThrow = 0;

class ConstructDestructCounterWithThrowOnConstructMock : public ConstructDestructCounterMock
{
public:
    ConstructDestructCounterWithThrowOnConstructMock()
            : ConstructDestructCounterMock()
    {
        if (ConstructDestructCounterWithThrowOnCopyMock_constructBeforeThrow == 0) {
            throw std::exception();
        }
        --ConstructDestructCounterWithThrowOnCopyMock_constructBeforeThrow;
    }
};


class CopyMoveMock
{
public:
    CopyMoveMock()
        : defaultConstructed(true),
          copyConstructed(false),
          moveConstructed(false)
    {}

    CopyMoveMock(const CopyMoveMock&)
        : defaultConstructed(false),
          copyConstructed(true),
          moveConstructed(false)
    {}

    CopyMoveMock(CopyMoveMock&&)
        : defaultConstructed(false),
          copyConstructed(false),
          moveConstructed(true)
    {}

    bool defaultConstructed;
    bool copyConstructed;
    bool moveConstructed;
};


class CopyNoexceptMoveMock
{
public:
    CopyNoexceptMoveMock()
        : defaultConstructed(true),
          copyConstructed(false),
          moveConstructed(false)
    {}

    CopyNoexceptMoveMock(const CopyNoexceptMoveMock&)
        : defaultConstructed(false),
          copyConstructed(true),
          moveConstructed(false)
    {}

    CopyNoexceptMoveMock(CopyNoexceptMoveMock&&) noexcept
        : defaultConstructed(false),
          copyConstructed(false),
          moveConstructed(true)
    {}

    bool defaultConstructed;
    bool copyConstructed;
    bool moveConstructed;
};

#endif //STUDY_VECTOR_MOCKS_H
