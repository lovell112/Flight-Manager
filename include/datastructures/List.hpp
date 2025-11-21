#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class List {
    T* m_pArray;
    size_t m_iSize;
    size_t m_iCapacity;

    // Tăng dung lượng khi cần
    void reserve(size_t newCapacity) {
        if (newCapacity <= m_iCapacity) return;

        T* newArr = new T[newCapacity];
        for (size_t i = 0; i < m_iSize; i++)
            newArr[i] = m_pArray[i];

        delete[] m_pArray;
        m_pArray = newArr;
        m_iCapacity = newCapacity;
    }

public:
    List() : m_pArray(nullptr), m_iSize(0), m_iCapacity(0) {}
    ~List() {
        delete[] m_pArray;
    }
    void add(T item) {
        if (m_iSize == m_iCapacity)
            reserve(m_iCapacity == 0 ? 2 : m_iCapacity * 2);
        m_pArray[m_iSize++] = item;
    }

    void remove(size_t index) {
        if (index >= m_iSize) throw std::out_of_range("Index out of range");
        for (size_t i = index; i < m_iSize - 1; i++)
            m_pArray[i] = m_pArray[i + 1];
        m_iSize--;
    }

    bool contains(T key) const {
        for (size_t i = 0; i < m_iSize; i++)
            if (m_pArray[i] == key)
                return true;
        return false;
    }

    void insert(size_t index, const T& value) {
        if (index > m_iSize) throw std::out_of_range("Index out of range");

        if (m_iSize == m_iCapacity)
            reserve(m_iCapacity == 0 ? 2 : m_iCapacity * 2);

        for (size_t i = m_iSize; i > index; i--)
            m_pArray[i] = m_pArray[i - 1];

        m_pArray[index] = value;
        m_iSize++;
    }
    size_t size() const { return m_iSize; }
    size_t capacity() const { return m_iCapacity; }
    void clear() { m_iSize = 0; }

   
    void resize(size_t newSize) {
        if (newSize > m_iCapacity)
            reserve(newSize * 2);
        m_iSize = newSize;
    }


    T& operator[](size_t index) const {
        if (index >= m_iSize) throw std::out_of_range("Index out of range");
        return m_pArray[index];
    }

   
    class iterator {
        T* m_pointer;
    public:
        iterator(T* ptr = nullptr) : m_pointer(ptr) {}
        ~iterator() {}

        T& operator*() const { return *m_pointer; }

        iterator& operator++() {  // prefix ++i
            m_pointer++;
            return *this;
        }

        iterator operator++(int) {  // postfix i++
            iterator temp = *this;
            m_pointer++;
            return temp;
        }

        iterator& operator--() {
            m_pointer--;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            m_pointer--;
            return temp;
        }

        bool operator==(const iterator& other) const {
            return m_pointer == other.m_pointer;
        }

        bool operator!=(const iterator& other) const {
            return m_pointer != other.m_pointer;
        }

        bool empty() const {
            return m_pointer == nullptr;
        }
    };

    iterator begin() {
        return iterator(m_pArray);
    }

    iterator end() {
        return iterator(m_pArray + m_iSize);
    }
};

#endif
