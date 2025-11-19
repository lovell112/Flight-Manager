#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
using namespace std;

template <typename T>
class List {
    T* m_pArray;
    size_t m_iSize;
    size_t m_iCapacity;

    void copy();
public:
    List();
    ~List();
    void add(T item);
    void remove(size_t index);
    bool contains(T key) const;
    void insert(size_t index, const T& value);
    size_t size() const;
    size_t capacity() const;
    void clear();
    void reserve(size_t newCapacity);
    void resize(size_t newSize);
    T& operator[](size_t) const;
    class iterator {
        T* m_pointer;
    public:
        iterator();
        ~iterator();
        T& operator*() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
        bool empty() const;
    };
    iterator begin();
    iterator end();
};

#endif
