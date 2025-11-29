#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <stdexcept>

template <typename T>
class Queue;

/**********************************************************
 * @Struct      Node
 * @Description Node của Queue: gồm dữ liệu và con trỏ next.
 **********************************************************/
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

/**********************************************************
 * @Class       Queue
 * @Description Hàng đợi kiểu liên kết đơn template.
 *              Hỗ trợ push, pop, front, back, clear.
 **********************************************************/
template <typename T>
class Queue {
    Node<T>* m_front;  // phan tu dau hang doi
    Node<T>* m_back;   // phan tu cuoi hang doi
    size_t m_size;     // so luong phan tu hien co

public:
    /**********************************************************
     * @Description Constructor mặc định
     **********************************************************/
    Queue() : m_front(nullptr), m_back(nullptr), m_size(0) {}

    /**********************************************************
     * @Description Copy constructor – deep copy
     **********************************************************/
    Queue(const Queue& other) : m_front(nullptr), m_back(nullptr), m_size(0) {
        Node<T>* cur = other.m_front;
        while (cur) {
            push(cur->m_data);
            cur = cur->m_next;
        }
    }

    /**********************************************************
       * @Description Operator= – deep copy, tránh self-assign
       **********************************************************/
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

    /**********************************************************
     * @Description Destructor – giải phóng toàn bộ node
     **********************************************************/
    ~Queue() {
        clear();
    }

    // ================== Core Operations ==================

    /**********************************************************
     * @return Dữ liệu phần tử đầu hàng đợi
     * @attention Ném exception nếu queue rỗng
     **********************************************************/
    T& front() const {
        if (!m_front) throw std::out_of_range("Queue is empty");
        return m_front->m_data;
    }

    /**********************************************************
     * @return Dữ liệu phần tử cuối queue
     **********************************************************/
    T& back() const {
        if (!m_back) throw std::out_of_range("Queue is empty");
        return m_back->m_data;
    }

    /**********************************************************
     * @Description Thêm phần tử vào cuối queue
     **********************************************************/
    void push(const T &item) {
        auto* newNode = new Node<T>(item);

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

    /**********************************************************
     * @Description Xóa phần tử đầu queue
     * @attention   Ném exception nếu queue rỗng
     **********************************************************/
    void pop() {
        if (!m_front) throw std::out_of_range("Queue is empty");

        const Node<T>* temp = m_front;
        m_front = m_front->m_next;

        // neu xoa xong Queue rong thi back cung phai null
        if (!m_front)
            m_back = nullptr;

        delete temp;
        m_size--;
    }

    /**********************************************************
     * @return true nếu queue rỗng
     **********************************************************/
    [[nodiscard]] bool empty() const {
        return m_size == 0;
    }

    /**********************************************************
     * @return Số lượng phần tử trong queue
     **********************************************************/
    [[nodiscard]] size_t size() const {
        return m_size;
    }

    /**********************************************************
     * @Description Xóa toàn bộ phần tử trong queue
     **********************************************************/
    void clear() {
        while (m_front) {
            const Node<T>* temp = m_front;
            m_front = m_front->m_next;
            delete temp;
        }
        m_back = nullptr;
        m_size = 0;
    }
};

#endif
