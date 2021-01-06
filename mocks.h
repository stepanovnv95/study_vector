#ifndef STUDY_VECTOR_MOCKS_H
#define STUDY_VECTOR_MOCKS_H


inline unsigned int ConstructDestructCounterMock_construct = 0;
inline unsigned int ConstructDestructCounterMock_destruct = 0;

class ConstructDestructCounterMock
{
public:
    ConstructDestructCounterMock()
    {
        ++ConstructDestructCounterMock_construct;
    }

    ~ConstructDestructCounterMock()
    {
        ++ConstructDestructCounterMock_destruct;
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

    CopyMoveMock(const CopyMoveMock& other)
        : defaultConstructed(false),
          copyConstructed(true),
          moveConstructed(false)
    {}

    CopyMoveMock(CopyMoveMock&& other)
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

    CopyNoexceptMoveMock(const CopyNoexceptMoveMock& other)
        : defaultConstructed(false),
          copyConstructed(true),
          moveConstructed(false)
    {}

    CopyNoexceptMoveMock(CopyNoexceptMoveMock&& other) noexcept
        : defaultConstructed(false),
          copyConstructed(false),
          moveConstructed(true)
    {}

    bool defaultConstructed;
    bool copyConstructed;
    bool moveConstructed;
};

#endif //STUDY_VECTOR_MOCKS_H
