#include "headers/deque.h"


template<class type>
inline deque<type>::deque():size(0), head(nullptr), tail(nullptr){}


template<class type>
inline deque<type>::deque(const deque &a) {
    size = a.size;
    item* iterA = a.head;
    item* iter;
    if (iterA) {
        head = new item;
        head->element = a.head->element;
        iter = head;
    }
    iterA = iterA->next;
    while (iterA){
        iter->next = new item;
        iter->next->previous = iter;
        iter = iter->next;
        iter->element = iterA->element;
        iterA = iterA->next;
    }
}

template<class type>
deque<type>::deque(deque &&a) {
    size = a.size;
    head = a.head;
    tail = a.tail;
    a.head = nullptr;
    a.tail = nullptr;
}

//template<class type>
//type &deque<type>::operator[](size_t index){
//    if (index >= size) throw std::out_of_range("Wrong index\n");
//    return elements[index];
//}
//
//template<class type>
//type deque<type>::operator[](size_t index) const {
//    if (index >= size) throw std::out_of_range("Wrong index\n");
//    return elements[index];
//}

template<class type>
deque<type>& deque<type>::operator=(const deque &a) {
    if (this != &a){
        size = a.size;
        item* iterA = a.head;
        item* iter;
        if (iterA) {
            head = new item;
            head->element = a.head->element;
            iter = head;
        }
        iterA = iterA->next;
        while (iterA){
            iter->next = new item;
            iter->next->previous = iter;
            iter = iter->next;
            iter->element = iterA->element;
            iterA = iterA->next;
        }
    }
    return *this;
}

template<class type>
deque<type>& deque<type>::operator=(deque &&a) {
    if (this != &a){
        size_t buf = a.size;
        a.size = size;
        size = buf;
        item* bufItem = a.head;
        a.head = head;
        head = bufItem;
        bufItem = a.tail;
        a.tail = tail;
        tail = bufItem;
    }
    return *this;
}

template<class type>
deque<type>::~deque() {
    if (head){
        item* buf1 = head;
        item* buf2;
        while (buf1) {
            buf2 = buf1->next;
            delete buf1;
            buf1 = buf2;
        }
    }
}

template<class type>
void deque<type>::push_back(const type &element) {
    item* it = new item;
    it->element = element;
    tail->next = it;
    tail = tail->next;
}

template<class type>
void deque<type>::push_front(const type &element) {
    item* it = new item;
    it->next = head;
    it->element = element;
}

template<class type>
void deque<type>::pop_back() {
    if (head){
        item* buf = tail;
        tail = tail->previous;
        delete buf;
    }
}

template <class type>
void deque<type>::pop_front(){
    if (head){
        item* buf = head;
        head = head->next;
        delete buf;
    }
}

template<class type>
type &deque<type>::front() {
    if (!head) throw std::runtime_error("Deque is empty\n");
    return head->element;
}

template<class type>
type &deque<type>::back() {
    if (!head) throw std::runtime_error("Deque is empty\n");
    return tail->element;
}


template<class type>
typename deque<type>::iterator &deque<type>::iterator::operator++() {
    el = el->next;
    return *this;
}

template<class type>
typename deque<type>::iterator &deque<type>::iterator::operator++(int) {
    el = el->next;
    return *this;
}

template<class type>
typename deque<type>::iterator &deque<type>::iterator::operator--() {
    el = el->previous;
    return *this;
}

template<class type>
typename deque<type>::iterator &deque<type>::iterator::operator--(int) {
    el = el->previous;
    return *this;
}

template<class type>
bool deque<type>::iterator::operator==(iterator& it) {
    return el == it->el;
}

