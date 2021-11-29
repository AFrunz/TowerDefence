#ifndef TOWERDEFENCE_DEQUE_H
#define TOWERDEFENCE_DEQUE_H
#include <iostream>

template <class type>
class deque {
protected:
    struct item{
        item* next;
        item* previous;
        type element;
    };
public:
    class iterator{
    private:
        item* el;
    public:
        iterator():el(nullptr){};
        iterator& operator++ ();
        iterator& operator++ (int);
        iterator& operator-- ();
        iterator& operator-- (int);
        bool operator== (iterator&);

    };

private:
    size_t size;
    item* head;
    item* tail;
public:
    deque<type>();
    deque(const deque&);
    deque(deque&&);

    void push_back(const type& element);
    void push_front(const type& element);
    void pop_back();
    void pop_front();
    type& front();
    type& back();
    friend class iterator;
    deque<type>& operator= (const deque&);
    deque<type>& operator= (deque&&);
    virtual ~deque();
};




#endif //TOWERDEFENCE_DEQUE_H
