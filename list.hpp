#include <iostream>
#include "node.hpp"
template <typename T>
class sorted_list
{
private:
    node<T> *first;
    node<T> *last;
    size_t size_ = 0;

public:
    sorted_list();
    ~sorted_list();
    sorted_list(const sorted_list &);
    sorted_list(sorted_list &&);
    sorted_list &operator=(const sorted_list &);
    sorted_list &operator=(sorted_list &&);
    sorted_list(const std::initializer_list<T> &);

    void push_back(const T &);
    void push_front(const T &);
    void pop_back();
    void pop_front();

    size_t size();
    bool empty();
    void clear();

    sorted_list &add(const T &);
    sorted_list &add(T &&);

    class iterator;
    iterator begin() { return iterator(first); }
    iterator end() { return iterator(last); }

    void print();
    iterator find(const T &);
    template <typename U>
    iterator find_if(U);
    sorted_list &remove(iterator);
};
template <typename T>
bool sorted_list<T>::empty() { return size_ == 0; }

template <typename T>
void sorted_list<T>::clear()
{
    while (first)
    {
        auto tmp = first;
        tmp = tmp->next;
        delete[] first;
        first = tmp;
    }
    size_ = 0;
}

template <typename T>
size_t sorted_list<T>::size() { return size_; }

template <typename T>
sorted_list<T>::sorted_list(const std::initializer_list<T> &other)
{
    size_ = 0;
    for (auto i = other.begin(); i != other.begin() + other.size(); i++)
    {
        node<T> *newnode = new node<T>(*i);
        if (size_ < 1)
        {
            first = last = newnode;
            size_++;
        }
        else
        {
            last->next = newnode;
            newnode->previous = last;
            last = newnode;
            size_++;
        }
    }
}
template <typename T>
sorted_list<T>::sorted_list() : first{nullptr}, last{nullptr}, size_{0} {}

template <typename T>
sorted_list<T>::~sorted_list()
{
    node<T> *tmp = first;
    while (first)
    {
        tmp = tmp->next;
        delete first;
        first = tmp;
    }
    first = nullptr;
    last = nullptr;
    size_ = 0;
}

template <typename T>
sorted_list<T>::sorted_list(const sorted_list &other) : size_{other.size_}, first{nullptr}, last{nullptr}
{
    if (size_ == 0)
        return;

    node<T> *tmp = other.first;
    while (tmp)
    {
        node<T> *newnode = new node<T>(tmp->element);
        if (!first)
        {
            first = newnode;
            last = newnode;
        }
        else
        {
            last->next = newnode;
            newnode->previous = last;
            last = newnode;
        }
        tmp = tmp->next;
    }
}

template <typename T>
sorted_list<T>::sorted_list(sorted_list &&other) : first{other.first}, last{other.last}, size_{other.size_}
{
    other.first = nullptr;
    other.last = nullptr;
    other.size_ = 0;
}

template <typename T>
sorted_list<T> &sorted_list<T>::operator=(const sorted_list<T> &other)
{
    size_ = other.size_;

    auto tmp = other.first;
    while (tmp)
    {
        node<T> *newnode = new node<T>(tmp->element);
        if (!first)
        {
            first = newnode;
            last = newnode;
        }
        else
        {
            last->next = newnode;
            newnode->previous = last;
            last = newnode;
        }
        tmp = tmp->next;
    }
    return *this;
}

template <typename T>
sorted_list<T> &sorted_list<T>::operator=(sorted_list<T> &&other)
{
    first = other.first;
    last = other.last;
    size_ = other.size_;
    other.first = nullptr;
    other.last = nullptr;
    other.size_ = 0;
    return *this;
}
template <typename T>
void sorted_list<T>::print()
{
    for (auto i = first; i != nullptr; i = i->next)
        std::cout << i->element << " ";
    std::cout << std::endl;
}

template <typename T>
void sorted_list<T>::push_back(const T &value)
{
    node<T> *newnode = new node<T>(value);
    if (!first)
    {
        first = newnode;
        last = newnode;
    }
    else
    {
        last->next = newnode;
        newnode->previous = last;
        last = newnode;
    }
    size_++;
}

template <typename T>
void sorted_list<T>::push_front(const T &value)
{
    node<T> *newnode = new node<T>(value);
    if (!first)
    {
        first = newnode;
        last = newnode;
    }
    else
    {
        newnode->next = first;
        first->previous = newnode;
        first = newnode;
    }
    size_++;
}

template <typename T>
void sorted_list<T>::pop_front()
{
    if (!first)
        return;

    node<T> *tmp = first->next;
    if (!tmp)
    {
        delete first;
        first = nullptr;
        last = nullptr;
        size_--;
        return;
    }
    delete first;
    first = tmp;
    size_--;
}

template <typename T>
void sorted_list<T>::pop_back()
{
    if (!first)
        return;
    auto tmp = last->previous;
    if (!tmp)
    {
        delete[] first;
        first = nullptr;
        last = nullptr;
        size_--;
        return;
    }
    delete[] last;
    last = tmp;
    last->next = nullptr;
    size_--;
}

template <typename T>
class sorted_list<T>::iterator
{
public:
    node<T> *pel;
    iterator(node<T> *x) { pel = x; }

    T &operator*() { return pel->element; };
    const T &operator*() const { return pel->element; };

    bool operator==(const iterator &other) { return other.pel == pel; }
    bool operator!=(const iterator &other) { return other.pel != pel; }
    bool operator<(const iterator &other) { return other.pel < pel; }
    bool operator>(const iterator &other) { return other.pel > pel; }
    bool operator<=(const iterator &other) { return other.pel <= pel; }

    iterator &operator++()
    {
        pel = pel->next;
        return *this;
    }

    iterator operator++(int)
    {
        auto tmp = *this;
        pel = pel->next;
        return tmp;
    }

    iterator &operator--()
    {
        pel = pel->previous;
        return *this;
    }

    iterator operator--(int)
    {
        auto x = *this;
        pel = pel->previous;
        return x;
    }
};

template <typename T>

typename sorted_list<T>::iterator sorted_list<T>::find(const T &value)
{
    for (auto i = first; i != nullptr; i = i->next)
    {
        if (i->element == value)
        {
            return iterator(i);
        }
    }
    return iterator(last);
}
