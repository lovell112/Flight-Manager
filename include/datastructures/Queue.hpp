#ifdef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue;

template <typename T>
class Node {
    T m_data;          // du lieu cua node
    Node* m_next;      // con tro den node tiep theo

public:
    friend class Queue<T>;

    Node() : m_data(T()), m_next(nullptr) {}
    Node(T data) : m_data(data), m_next(nullptr) {}
    ~Node() {}
};

template <typename T>
class Queue {
    Node<T>* m_front;  // phan tu dau hang doi
    Node<T>* m_back;   // phan tu cuoi hang doi
    size_t m_size;     // so luong phan tu hien co

public:
    Queue() : m_front(nullptr), m_back(nullptr), m_size(0) {}

    // Copy constructor
Queue(const Queue& other) : m_front(nullptr), m_back(nullptr), m_size(0) {
    Node<T>* cur = other.m_front;
    while (cur) {
        push(cur->m_data);
        cur = cur->m_next;
    }
}

  // Operator=
Queue& operator=(const Queue& other) {
    if (this == &other)
        return *this;

    clear();

    Node<T>* cur = other.m_front;
    while (cur) {
        push(cur->m_data);
        cur = cur->m_next;
    }

    return *this;
}

    // giai phong toan bo node khi huy Queue
    ~Queue() {
        clear();
    }

    // tra ve phan tu o dau Queue
    T& front() const {
        if (!m_front) throw std::out_of_range("Queue is empty");
        return m_front->m_data;
    }

    // tra ve phan tu o cuoi Queue
    T& back() const {
        if (!m_back) throw std::out_of_range("Queue is empty");
        return m_back->m_data;
    }

    // them phan tu vao cuoi Queue
    void push(T item) {
        Node<T>* newNode = new Node<T>(item);

        // neu Queue da co phan tu
        if (m_back) {
            m_back->m_next = newNode;
            m_back = newNode;
        } 
        else {
            // Queue dang rong
            m_front = m_back = newNode;
        }

        m_size++;
    }

    // xoa phan tu o dau Queue
    void pop() {
        if (!m_front) throw std::out_of_range("Queue is empty");

        Node<T>* temp = m_front;
        m_front = m_front->m_next;

        // neu xoa xong Queue rong thi back cung phai null
        if (!m_front)
            m_back = nullptr;

        delete temp;
        m_size--;
    }

    // kiem tra Queue co rong hay khong
    bool empty() const {
        return m_size == 0;
    }

    // lay so luong phan tu
    size_t size() const {
        return m_size;
    }

    // xoa tat ca phan tu trong Queue
    void clear() {
        while (m_front) {
            Node<T>* temp = m_front;
            m_front = m_front->m_next;
            delete temp;
        }
        m_back = nullptr;
        m_size = 0;
    }
};

#endif
