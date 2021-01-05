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

#endif //STUDY_VECTOR_MOCKS_H
