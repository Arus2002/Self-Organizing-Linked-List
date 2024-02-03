#include "SOLL.hpp"

template <typename T>
SOLL<T>::SOLL() 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr}
    , m_size{0} {}

template <typename T>
SOLL<T>::SOLL(std::size_t size)
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr}
    , m_size{size} 
{
    if (size <= 0) {
        return;
    }

    Node<T>* newNode = new Node<T>(0);
    m_head = newNode;
    m_asc = newNode;
    m_desc = newNode;
    m_tail = newNode;
    Node<T>* curr = m_head;
    for (int i = 1; i < m_size; ++i) {
        Node<T>* newNode = new Node<T>(0);
        curr -> asc = newNode;
        newNode -> desc = curr;
        curr -> next = newNode;
        newNode -> prev = curr;
        m_tail = newNode;
        m_desc = newNode;

        curr = curr -> next;
    }
}

template <typename T>
SOLL<T>::SOLL(const SOLL<T>& rhs)
{
    m_size = 0;
    Node<T>* curr = rhs.m_head;
    while (curr != nullptr) {
        push_back(curr -> data);
        curr = curr -> next;
    }
    m_size = rhs.m_size;
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(const SOLL<T>& rhs) {
    clear();
    m_size = 0;
    Node<T>* curr = rhs.m_head;
    while (curr != nullptr) {
        push_back(curr -> data);
        curr = curr -> next;
    }
    m_size = rhs.m_size;
    return *this;
}

template <typename T>
SOLL<T>::SOLL(SOLL&& rhs) 
    : m_head{rhs.m_head}
    , m_tail{rhs.m_tail}
    , m_asc{rhs.m_asc}
    , m_desc{rhs.m_desc}
    , m_size{rhs.m_size}
{
    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_asc = nullptr;
    rhs.m_desc = nullptr;
    rhs.m_size = 0;
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(SOLL<T>&& rhs) {
    clear();
    m_head = rhs.m_head;
    m_tail = rhs.m_tail;
    m_asc = rhs.m_asc;
    m_desc = rhs.m_desc;
    m_size = rhs.m_size;

    rhs.m_head = nullptr;
    rhs.m_tail = nullptr;
    rhs.m_asc = nullptr;
    rhs.m_desc = nullptr;
    rhs.m_size = 0;
}

template <typename T>
void SOLL<T>::clear() {
    Node<T>* tmp = m_head;
    while (tmp != nullptr) {
        Node<T>* tmp2 = tmp;
        tmp = tmp->next;
        delete tmp2;
    }
}

template <typename T>
SOLL<T>::~SOLL() {
    clear();
}

template <typename T>
void SOLL<T>::printInSortedOrder() const {
    Node<T>* curr = m_asc;
    std::cout << "[ ";
    while (curr != nullptr) {
        std::cout << curr -> data << " ";
        curr = curr -> asc;
    }
    std::cout << " ]" << std::endl;
}

template <typename T>
void SOLL<T>::print() const {
    Node<T>* curr = m_head;
    std::cout << "[ ";
    while (curr != nullptr) {
        std::cout << curr -> data << " ";
        curr = curr -> next;
    }
    std::cout << " ]" << std::endl;
}

template <typename T>
Node<T>* SOLL<T>::putInSortedOrder(Node<T>* node) {
    bool flag = false;
    Node<T>* curr = m_asc;
    if (node -> data < m_asc -> data) {
        node -> asc = curr;
        curr -> desc = node;
        m_asc = node;
        return node;
    }
    while (curr != nullptr) {
        if (curr -> data > node -> data) {
            node -> asc = curr;
            node -> desc = curr -> desc;
            curr -> desc -> asc = node;
            curr -> desc = node;
            return node;
        }
        curr = curr -> asc;
    }
    m_desc -> asc = node;
    node -> desc = m_desc;
    m_desc = node;
    return node;
}

template <typename T>
void SOLL<T>::push_back(const T& val) {
    Node<T>* newNode = new Node<T>(val);
    if (m_size == 0) {
        m_head = m_tail = newNode;
        m_asc = m_desc = newNode;
        ++m_size;
        return;
    }
    newNode -> prev = m_tail;
    m_tail -> next  = newNode;
    m_tail = newNode;
    newNode = putInSortedOrder(newNode);
    ++m_size;
}

template <typename T>
void SOLL<T>::push_front(const T& val) {
    if (m_size == 0) {
        push_back(val);
    }
    Node<T>* newNode = new Node<T>(val);
    newNode -> next = m_head;
    m_head -> prev = newNode;
    m_head = newNode;
    newNode = putInSortedOrder(newNode);
    ++m_size;
}

template <typename T>
void SOLL<T>::insert(const T& val, std::size_t index) {
    if (index < 0 || index > m_size) {
        throw std::out_of_range("Out of range!");
    }
    if (index == 0) {
        push_front(val);
        return;
    }
    if (index == m_size - 1) {
        push_back(val);
        return;
    }

    Node<T>* newNode = new Node<T>(val);
    
    Node<T>* tmp = m_head;
    while (index != 0) {
        tmp = tmp -> next;
        --index;
    }

    newNode -> prev = tmp -> prev;
    tmp -> prev -> next = newNode;
    newNode -> next = tmp;
    tmp -> prev = newNode;

    newNode = putInSortedOrder(newNode);
    ++m_size;
}

template <typename T>
void SOLL<T>::erase(const T& val) {
    Node<T>* curr = m_head;
    while (curr != nullptr) {
        if (curr -> data == val) {
            if (m_asc == curr) {
                m_asc = curr -> asc;
            }
            else if (m_desc == curr) {
                m_desc = curr -> desc;
                m_desc -> asc = nullptr;
            }
            else {
                curr -> desc -> asc = curr -> asc;
                curr -> asc -> desc = curr -> desc;
            }

            if (m_head == curr) {
                m_head = curr -> next;
                m_head -> prev = nullptr;
                delete curr;
            }
            else if (m_tail == curr) {
                m_tail -> prev -> next = nullptr;
                m_tail = curr -> prev;
                delete curr;
            }
            else {
                curr -> prev -> next = curr -> next;
                curr -> next -> prev  = curr -> prev;
                curr -> prev = nullptr;
                curr -> next = nullptr;
                delete curr;
            }
            return;
        }
        curr = curr -> next;
    }
}

template <typename T>
bool SOLL<T>::find(const T& val) {
    Node<T>* curr = m_head;
    while (curr != nullptr) {
        if (curr -> data == val) {
            get(curr);
            return true;
        }
        curr = curr -> next;
    }
    return false;
}

template <typename T>
void SOLL<T>::get(Node<T>* node) {
    if (node == m_head) {
        return;
    }
    Node<T>* curr = m_head;
    while (curr -> next != node) {
        curr = curr -> next;
    }

    if (curr -> prev == nullptr) {
        m_head = node;
        node -> next -> prev = curr;
        curr -> next = node -> next;
        node -> next = curr;
        node -> prev = curr -> prev;
        curr -> prev = node;
    }
    else if (node -> next == nullptr) {
        m_tail = node;
        curr -> prev -> next = node;
        node -> prev = curr -> prev;
        curr -> prev = node;
        node -> next = curr;
        curr -> next = nullptr;
    }
    else {
        curr -> prev -> next = node;
        node -> prev = curr -> prev;
        node -> next -> prev = curr;
        curr -> next = node -> next;
        node -> next = curr;
        curr -> prev = node;
    }
}