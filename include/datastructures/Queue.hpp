#ifdef QUEUE_HPP
#define QUEUE_HPP

template <typename T>
class Node {
    T m_data;
    Node* m_next;
public:
    friend class Queue;
    Node();
    Node(T data);
    ~Node();
};

template <typename T>
class Queue {
    Node<T>* m_front;
    Node<T>* m_back;
    size_t size;
public:
    T& front() const;
    T& back() const;
    void push(T item);
    void pop();
    bool empty() const;
    size_t size() const;
    void clear();
};

#endif
