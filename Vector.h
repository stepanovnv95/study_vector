#ifndef STUDY_VECTOR_VECTOR_H
#define STUDY_VECTOR_VECTOR_H

#include <algorithm>


namespace study {

template <class T>
class Vector
{
public:
    Vector()
        : capacity_(0),
          size_(0),
          data_(nullptr)
    {}

    ~Vector()
    {
        if (data_) {
            delete [] data_;
        }
    }

    size_t size() const
    {
        return size_;
    }

    void pushBack(const T &obj)
    {
        if (size_ == capacity_) {
            reallocate();
        }
        pushToEnd(obj);
    }

private:
    void reallocate()
    {
        size_t newCapacity = capacity_ == 0 ? 10 : capacity_ * 2;
        T *newData = new T[newCapacity];
        std::copy(data_, data_ + size_, newData);
        if (data_) {
            delete[] data_;
        }
        data_ = newData;
    }

    void pushToEnd(const T &obj)
    {
        data_[size_] = obj;
        ++size_;
    }

    size_t capacity_;
    size_t size_;
    T *data_;
};

}

#endif //STUDY_VECTOR_VECTOR_H
