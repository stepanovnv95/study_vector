#ifndef STUDY_VECTOR_VECTOR_H
#define STUDY_VECTOR_VECTOR_H

#include <algorithm>
#include <memory>


namespace study {

template <class T>
class Vector
{
public:
    Vector()
        : capacity_(0),
          size_(0)
    {}

    explicit Vector(size_t capacity)
        : capacity_(capacity),
          size_(0),
          data_(std::unique_ptr<T[]>(new T[capacity]))
    {}

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
        auto newData = std::unique_ptr<T[]>(new T[newCapacity]);
        std::copy(data_.get(), data_.get() + size_, newData.get());
        data_.swap(newData);
    }

    void pushToEnd(const T &obj)
    {
        data_[size_] = obj;
        ++size_;
    }

    size_t capacity_;
    size_t size_;
    std::unique_ptr<T[]> data_;
};

}

#endif //STUDY_VECTOR_VECTOR_H
