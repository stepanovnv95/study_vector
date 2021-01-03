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
          size_(capacity),
          data_(std::unique_ptr<T[]>(new T[capacity]))
    {}

    Vector(const Vector &other)
        : capacity_(other.capacity_),
          size_(other.size_),
          data_(std::unique_ptr<T[]>(new T[capacity_]))
    {
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    Vector& operator=(const Vector &other)
    {
        swap(Vector(other));
        return *this;
    }

    Vector(Vector&& other)
    {
        swap(other);
    }

    Vector& operator=(Vector&& other)
    {
        swap(other);
        return *this;
    }

    size_t capacity() const
    {
        return capacity_;
    }

    size_t size() const
    {
        return size_;
    }

    const T& operator[](size_t i) const
    {
        return data_[i];
    }

    T& operator[](size_t i)
    {
        return data_[i];
    }

    void push_back(const T &obj)
    {
        if (size_ == capacity_) {
            reallocate();
        }
        pushToEnd(obj);
    }

    void swap(Vector &other)
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

private:
    void reallocate()
    {
        size_t newCapacity = capacity_ == 0 ? 10 : capacity_ * 2;
        auto newData = std::unique_ptr<T[]>(new T[newCapacity]);
        std::copy(data_.get(), data_.get() + size_, newData.get());
        data_.swap(newData);
        capacity_ = newCapacity;
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
