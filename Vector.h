#ifndef STUDY_VECTOR_VECTOR_H
#define STUDY_VECTOR_VECTOR_H

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
            new (storageToValueType(it)) value_type;
        }
    }

    Vector(const Vector &other)
        : capacity_(other.capacity_),
          size_(other.size_),
          data_(makeStorage(capacity_))
    {
        copyValues(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    Vector(Vector&& other) noexcept
        : capacity_(other.capacity_),
          size_(other.size_),
          data_(std::move(other.data_))
    {}

    Vector(const std::initializer_list<value_type>& initList)
        : capacity_(initList.size()),
          size_(initList.size()),
          data_(makeStorage(initList.size()))
    {
        StorageType* storageIt = data_.get();
        auto initListIt = std::begin(initList);
        for (; initListIt != std::end(initList); ++initListIt, ++storageIt) {
            value_type* value = storageToValueType(storageIt);
            new (value) value_type(*initListIt);
        }
    }

    Vector& operator=(const Vector& other)
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = makeStorage(size_);
        copyValues(other.data_.get(), other.data_.get() + size_, data_.get());
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = std::move(other.data_);
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

    [[nodiscard]]
    const value_type& operator[](size_t i) const
    {
        return *storageToValueType(data_.get() + i);
    }

    [[nodiscard]]
    value_type& operator[](size_t i)
    {
        return *storageToValueType(data_.get() + i);
    }

    template <class ...Args>
    void emplace_back(Args&& ...args)
    {
        if (size_ == capacity_) {
            reallocate();
        }
        emplaceToEnd(std::forward<Args>(args)...);
    }

    void push_back(value_type&& obj)
    {
        emplace_back(std::forward<value_type>(obj));
    }

    void swap(Vector &other) noexcept
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
    }

    void resize(size_t count)
    {
        if (count < size_) {
            destructValues(data_.get() + count, data_.get() + size_);
        }
        if (count > capacity_) {
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
        [[nodiscard]]
        bool operator==(const Iterator& other)
        {
            return ptr_ == other.ptr_;
        }

        [[nodiscard]]
        bool operator!=(const Iterator& other)
        {
            return !(*this == other);
        }

        Iterator& operator++()
        {
            ++ptr_;
            return *this;
        }

        [[nodiscard]]
        pointer operator->()
        {
            return Vector::storageToValueType(ptr_);
        }

        [[nodiscard]]
        reference operator*()
        {
            return *operator->();
        }

    private:
        StorageType* ptr_;
    };

    [[nodiscard]]
    Iterator<value_type> begin()
    {
        return Iterator<value_type>(data_.get());
    }

    [[nodiscard]]
    Iterator<value_type> end()
    {
        return Iterator<value_type>(data_.get() + size_);
    }

    [[nodiscard]]
    Iterator<const value_type> cbegin() const
    {
        return Iterator<const value_type>(data_.get());
    }

    [[nodiscard]]
    Iterator<const value_type> cend() const
    {
        return Iterator<const value_type>(data_.get() + size_);
    }

private:
    [[nodiscard]]
    static value_type* storageToValueType(StorageType* p)
    {
        return std::launder(reinterpret_cast<value_type*>(p));
    }

    [[nodiscard]]
    std::unique_ptr<StorageType[]> makeStorage(size_t size) const
    {
        return std::unique_ptr<StorageType[]>(new StorageType[size]);
    }

    void copyValues(StorageType* sourceBegin, StorageType* sourceEnd, StorageType* targetBegin)
    {
        StorageType* sourceIt = sourceBegin;
        StorageType* targetIt = targetBegin;
        for (; sourceIt != sourceEnd; ++sourceIt, ++targetIt) {
            value_type* sourceValue = storageToValueType(sourceIt);
            value_type* targetValue = storageToValueType(targetIt);
            new (targetValue) value_type(*sourceValue);
        }
    }

    void moveValues(StorageType* sourceBegin, StorageType* sourceEnd, StorageType* targetBegin)
    {
        StorageType* sourceIt = sourceBegin;
        StorageType* targetIt = targetBegin;
        for (; sourceIt != sourceEnd; ++sourceIt, ++targetIt) {
            value_type* sourceValue = storageToValueType(sourceIt);
            value_type* targetValue = storageToValueType(targetIt);
            new (targetValue) value_type(std::move(*sourceValue));
        }
    }

    void destructValues(StorageType* begin, StorageType* end)
    {
        if constexpr (std::is_destructible_v<value_type>) {
            for (auto it = begin; it != end; ++it) {
                storageToValueType(it)->~value_type();
            }
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
        if constexpr (std::is_nothrow_move_constructible_v<value_type>) {
            moveValues(data_.get(), data_.get() + size_, newData.get());
        } else {
            copyValues(data_.get(), data_.get() + size_, newData.get());
            destructValues(data_.get(), data_.get() + size_);
        }
        data_.swap(newData);
        capacity_ = newCapacity;
    }

    template <class ...Args>
    void emplaceToEnd(Args&& ...args)
    {
        new (storageToValueType(data_.get() + size_)) value_type(std::forward<Args>(args)...);
        ++size_;
    }

    size_t capacity_;
    size_t size_;
    std::unique_ptr<StorageType[]> data_;
};

}

#endif //STUDY_VECTOR_VECTOR_H
