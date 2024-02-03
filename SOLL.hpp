#ifndef SOLL_HPP
#define SOLL_HPP

#include <iostream>

template <typename T>
struct Node {
    Node(const T& data)
        : data{data}
        , next{nullptr}
        , prev{nullptr}
        , asc{nullptr}
        , desc{nullptr} {}

    T data;
    Node* next;
    Node* prev;
    Node* asc;
    Node* desc;
};

template <typename T>
class SOLL {
public:
    SOLL();
    SOLL(std::size_t size);
    SOLL(const SOLL& rhs);
    SOLL& operator=(const SOLL& rhs);
    SOLL(SOLL&& rhs);
    SOLL& operator=(SOLL&& rhs);
    ~SOLL();
    void push_back(const T& val);
    void push_front(const T& val);
    void insert(const T& val, std::size_t index);
    void erase(const T& val);
    void printInSortedOrder() const;
    void print() const;
    bool find(const T& val);

private:
    void get(Node<T>* node);
    Node<T>* putInSortedOrder(Node<T>* node);
    void clear();
private:
    Node<T>* m_head;
    Node<T>* m_tail;
    Node<T>* m_asc;
    Node<T>* m_desc;
    std::size_t m_size;
};

#include "SOLL.impl.cpp"

#endif