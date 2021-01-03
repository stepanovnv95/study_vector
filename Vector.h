#ifndef STUDY_VECTOR_VECTOR_H
#define STUDY_VECTOR_VECTOR_H

#include <algorithm>
#include <memory>


namespace study {

template <class T>
class Vector
{
public:
    using value_type = T;

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

    void resize(size_t count)
    {
        if (count < capacity_) {
            reallocate(count);
        }
        size_ = count;
    }

    template <class VT>
    class Iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = VT;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

    private:
        friend class Vector;
        Iterator(T *ptr)
            : ptr_(ptr)
        {}

    public:
        bool operator==(const Iterator& other)
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other)
        {
            return !(*this == other);
        }

        Iterator& operator++()
        {
            ++ptr_;
            return *this;
        }

        reference operator*()
        {
            return *ptr_;
        }

        pointer operator->()
        {
            return ptr_;
        }

    private:
        VT* ptr_;
    };

    Iterator<T> begin()
    {
        return Iterator<T>(data_.get());
    }

    Iterator<T> end()
    {
        return Iterator<T>(data_.get() + size_);
    }

    Iterator<const T> cbegin() const
    {
        return Iterator<const T>(data_.get());
    }

    Iterator<const T> cend() const
    {
        return Iterator<const T>(data_.get() + size_);
    }

private:
    void reallocate(size_t count=0)
    {
        size_t newCapacity;
        if (count == 0) {
            newCapacity = capacity_ == 0 ? 10 : capacity_ * 2;
        } else {
            newCapacity = count;
        }
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
