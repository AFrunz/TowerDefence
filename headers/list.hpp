#ifndef TOWERDEFENCE_DEQUE_РЗЗ
#define TOWERDEFENCE_DEQUE_РЗЗ
//#include <iostream>

template <class type>
class list {
protected:
    struct item{
        item* next;
        item* previous;
        type element;
        item():next(nullptr), previous(nullptr), element(){};
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
        const type& operator* () const;
        type& operator*();
        bool operator== (const iterator&) const;
        bool operator!= (const iterator&) const;
        iterator operator- (const iterator&) const;
        friend class deque;
    };

private:
    size_t size;
    item* head;
    item* tail;
public:
    list<type>();
    list(const list&);
    list(list&&);

    bool empty() const;
    void push_back(const type& element);
    void push_front(const type& element);
    void pop_back();
    void pop_front();
    type& front();
    type& back();
    friend class iterator;
    iterator begin();
    iterator end();


    list<type>& operator= (const list&);
    list<type>& operator= (list&&);
    virtual ~list();
};


#include "list.inl"

#endif //TOWERDEFENCE_DEQUE_РЗЗ
