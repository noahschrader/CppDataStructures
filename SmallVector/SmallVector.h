#include <array>

template <class T, size_t InlineSize = 1>
class SmallVector
{
    static_assert(InlineSize > 0, "InlineSize must be greater than 0");
public:
    ~SmallVector()
    {
        for(size_t i = 0; i < m_size; ++i)
        {
            data()[i].~T();
        }

        if(m_dynamic)
        {
            free(m_dynamic);
        }
    }

    void push_back(const T& t)
    {
        if(m_capacity == m_size)
        {
            grow();
        }

        new (data() + m_size) T(t);
        ++m_size;
    }

    void pop_back()
    {
        if(m_size)
        {
            --m_size;
            data()[m_size].~T();
        }
    }

    T& operator[](size_t i)
    {
        return data()[i];
    }

    T* data()
    {
        return m_dynamic ? reinterpret_cast<T*>(m_dynamic) : reinterpret_cast<T*>(m_static.data());
    }

    size_t size()
    {
        return m_size;
    }

    size_t capacity()
    {
        return m_capacity;
    }

private:
    void grow()
    {
        m_capacity *= 2;
        std::byte* newData = reinterpret_cast<std::byte*>(malloc(m_capacity * sizeof(T)));

        T* oldTData = data();
        T* newTData = reinterpret_cast<T*>(newData);
        for(size_t i = 0; i < m_size; ++i)
        {
            new (newTData + i) T(oldTData[i]);
            oldTData[i].~T();
        }

        if(m_dynamic)
        {
            free(m_dynamic);
        }

        m_dynamic = newData;
    }

    std::byte* m_dynamic = nullptr;
    std::array<std::byte, InlineSize * sizeof(T)> m_static;
    size_t m_size = 0;
    size_t m_capacity = InlineSize;
};