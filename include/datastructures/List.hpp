#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class List {
private:
    T* m_pArray;
    size_t m_iSize;
    size_t m_iCapacity;

    // Tăng dung lượng khi cần
    void reserve(const size_t newCapacity) {
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
    List(const size_t size, const T value = T()) : m_iSize(size), m_iCapacity(2*size) {
        if (size == 0)
            return;

        m_pArray = new T[m_iCapacity];
        for (size_t i = 0; i < m_iSize; i++)
            m_pArray[i] = value;
    }

    ~List() {
        delete[] m_pArray;
    }

    // Copy Constructor
    List(const List& other) : m_pArray(nullptr), m_iSize(0), m_iCapacity(0) {
        if (other.m_iSize == 0) return;
        reserve(other.m_iCapacity);
        for (size_t i = 0; i < other.m_iSize; i++)
            m_pArray[i] = other.m_pArray[i];
        m_iSize = other.m_iSize;
    }

    // Copy Assignment
    List& operator=(const List& other) {
        if (this == &other) return *this;
        delete[] m_pArray;
        m_pArray = nullptr;
        m_iSize = 0;
        m_iCapacity = 0;
        if (other.m_iSize == 0) return *this;
        reserve(other.m_iCapacity);
        for (size_t i = 0; i < other.m_iSize; i++)
            m_pArray[i] = other.m_pArray[i];
        m_iSize = other.m_iSize;
        return *this;
    }

    void add(const T& item) {
        if (m_iSize == m_iCapacity)
            reserve(m_iCapacity == 0 ? 2 : m_iCapacity * 2);
        m_pArray[m_iSize++] = item;
    }

    // ✓ Xóa theo index - trả về con trỏ tới phần tử tiếp theo
    T* remove(size_t index) {
        if (index >= m_iSize)
            throw std::out_of_range("Index out of range");

        for (size_t i = index; i < m_iSize - 1; i++)
            m_pArray[i] = m_pArray[i + 1];
        m_iSize--;

        return (index < m_iSize) ? (m_pArray + index) : end();
    }

    // ✓ Xóa theo con trỏ - trả về con trỏ tiếp theo
    T* remove(T* ptr) {
        if (ptr == nullptr || ptr < m_pArray || ptr >= m_pArray + m_iSize)
            throw std::invalid_argument("Invalid pointer");

        const size_t index = ptr - m_pArray;
        return remove(index);
    }

    bool contains(const T& key) const {
        for (size_t i = 0; i < m_iSize; i++) {
            auto j = m_pArray[i];
            if (*m_pArray[i] == *key)
                return true;
        }
        return false;
    }

    void insert(size_t index, const T& value) {
        if (index > m_iSize)
            throw std::out_of_range("Index out of range");

        if (m_iSize == m_iCapacity)
            reserve(m_iCapacity == 0 ? 2 : m_iCapacity * 2);

        for (size_t i = m_iSize; i > index; i--)
            m_pArray[i] = m_pArray[i - 1];

        m_pArray[index] = value;
        m_iSize++;
    }

    [[nodiscard]] size_t size() const {
        return m_iSize;
    }

    [[nodiscard]] size_t capacity() const {
        return m_iCapacity;
    }

    [[nodiscard]] bool empty() const {
        return m_iSize == 0;
    }

    void clear() {
        m_iSize = 0;
    }

    void resize(const size_t newSize) {
        if (newSize > m_iCapacity)
            reserve(newSize * 2);
        m_iSize = newSize;
    }

    void resize(const size_t newSize, const T value) {
        if (newSize == 0)
            return;

        m_iSize = newSize;
        if (newSize <= m_iCapacity) {
            for (size_t i = 0; i < m_iSize; i++)
                m_pArray[i] = value;
        } else {
            delete m_pArray;
            m_iCapacity *= 2;
            m_pArray = new T[m_iCapacity];
            for (size_t i = 0; i < m_iSize; i++)
                m_pArray[i] = value;
        }
    }

    T& operator[](size_t index) const {
        if (index >= m_iSize)
            throw std::out_of_range("Index out of range");
        return m_pArray[index];
    }

    T& front() {
        if (m_iSize == 0)
            throw std::out_of_range("List is empty");
        return m_pArray[0];
    }

    T& back() {
        if (m_iSize == 0)
            throw std::out_of_range("List is empty");
        return m_pArray[m_iSize - 1];
    }

    void pop_back() {
        if (m_iSize == 0)
            throw std::out_of_range("List is empty");
        m_iSize--;
    }

    // ✓ Tìm phần tử - trả về con trỏ
    T* find(const T& key) {
        for (size_t i = 0; i < m_iSize; i++) {
            if (m_pArray[i] == key)
                return m_pArray + i;
        }
        return end();
    }

    const T* find(const T& key) const {
        for (size_t i = 0; i < m_iSize; i++) {
            if (m_pArray[i] == key)
                return m_pArray + i;
        }
        return end();
    }

    // ✓ Trả về con trỏ đầu và cuối
    T* begin() {
        return m_pArray;
    }

    T* end() {
        return m_pArray + m_iSize;
    }

    // Const versions
    const T* begin() const {
        return m_pArray;
    }

    const T* end() const {
        return m_pArray + m_iSize;
    }
};

#endif