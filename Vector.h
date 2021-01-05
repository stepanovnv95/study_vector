#ifndef STUDY_VECTOR_VECTOR_H
#define STUDY_VECTOR_VECTOR_H

#include <algorithm>
#include <memory>
#include <type_traits>


namespace study {

template <class T>
class Vector
{
public:
    using value_type = T;
private:
    using StorageType = std::aligned_storage_t<sizeof(value_type), std::alignment_of_v<value_type>>;
public:

    Vector()
        : capacity_(0),
          size_(0)
    {}

    explicit Vector(size_t size)
        : capacity_(size),
          size_(size),
          data_(makeStorage(size))
    {
        for (auto it = data_.get(); it != data_.get() + size; ++it) {
            new (std::launder(reinterpret_cast<value_type*>(it))) value_type;
        }
    }

    Vector(const Vector &other)
        : capacity_(other.capacity_),
          size_(other.size_),
          data_(makeStorage(capacity_))
    {
        copyValues(other.data_.get(), data_.get(), size_);
    }

    Vector& operator=(const Vector &other)
    {
        swap(Vector(other));
        return *this;
    }

    Vector(Vector&& other) noexcept
    {
        swap(other);
    }

    Vector& operator=(Vector&& other) noexcept
    {
        swap(other);
        return *this;
    }

    [[nodiscard]]
    size_t capacity() const
    {
        return capacity_;
    }

    [[nodiscard]]
    size_t size() const
    {
        return size_;
    }

    const value_type& operator[](size_t i) const
    {
        return *std::launder(reinterpret_cast<value_type*>(data_.get() + i));
    }

    value_type& operator[](size_t i)
    {
        return *std::launder(reinterpret_cast<value_type*>(data_.get() + i));
    }

    void push_back(value_type&& obj)
    {
        if (size_ == capacity_) {
            reallocate();
        }
        pushToEnd(std::forward<value_type>(obj));
    }

    void swap(Vector &other) noexcept
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    void resize(size_t count)
    {
        // TODO
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
        explicit Iterator(StorageType* ptr)
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

        pointer operator->()
        {
            return std::launder(reinterpret_cast<pointer>(ptr_));
        }

        reference operator*()
        {
            return *operator->();
        }

    private:
        StorageType* ptr_;
    };

    Iterator<value_type> begin()
    {
        return Iterator<value_type>(data_.get());
    }

    Iterator<value_type> end()
    {
        return Iterator<value_type>(data_.get() + size_);
    }

    Iterator<const value_type> cbegin() const
    {
        return Iterator<const value_type>(data_.get());
    }

    Iterator<const value_type> cend() const
    {
        return Iterator<const value_type>(data_.get() + size_);
    }

private:
    std::unique_ptr<StorageType[]> makeStorage(size_t size) const
    {
        return std::unique_ptr<StorageType[]>(new StorageType[size]);
    }

    void copyValues(StorageType* source, StorageType* target, size_t size)
    {
        StorageType* otherStorage = source;
        StorageType* storage = target;
        for (; otherStorage != source + size; ++otherStorage, ++storage) {
            value_type* otherValue = std::launder(reinterpret_cast<value_type*>(otherStorage));
            value_type* value = std::launder(reinterpret_cast<value_type*>(storage));
            new (value) value_type(*otherValue);
        }
    }

    void reallocate(size_t count=0)
    {
        size_t newCapacity;
        if (count == 0) {
            newCapacity = capacity_ == 0 ? 10 : capacity_ * 2;
        } else {
            newCapacity = count;
        }
        auto newData = makeStorage(newCapacity);
        copyValues(data_.get(), newData.get(), size_);
        data_.swap(newData);
        capacity_ = newCapacity;
    }

    void pushToEnd(value_type&& obj)
    {
        new (std::launder(reinterpret_cast<value_type*>(data_.get() + size_))) value_type(std::forward<value_type>(obj));
        ++size_;
    }

    size_t capacity_;
    size_t size_;
    std::unique_ptr<StorageType[]> data_;
};

}

#endif //STUDY_VECTOR_VECTOR_H
