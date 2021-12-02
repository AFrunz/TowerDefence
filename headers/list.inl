

template<class type>
list<type>::list():size(0), head(nullptr), tail(nullptr){}


template<class type>
list<type>::list(const list &a) {
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
list<type>::list(list &&a) {
    size = a.size;
    head = a.head;
    tail = a.tail;
    a.head = nullptr;
    a.tail = nullptr;
    a.size = 0;
}

//template<class type>
//type &list<type>::operator[](size_t index){
//    if (index >= size) throw std::out_of_range("Wrong index\n");
//    return elements[index];
//}
//
//template<class type>
//type list<type>::operator[](size_t index) const {
//    if (index >= size) throw std::out_of_range("Wrong index\n");
//    return elements[index];
//}

template<class type>
list<type>& list<type>::operator=(const list &a) {
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
list<type>& list<type>::operator=(list &&a) {
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
list<type>::~list() {
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
void list<type>::push_back(const type &element) {
    size++;
    if (!head){
        head = new item;
        head->element = element;
        tail = head;
        return;
    }
    item* it = new item;
    it->element = element;
    tail->next = it;
    it->previous = tail;
    tail = tail->next;
}

template<class type>
void list<type>::push_front(const type &element) {
    size++;
    if (!head){
        head = new item;
        head->element = element;
        tail = head;
        return;
    }
    item* it = new item;
    it->next = head;
    it->element = element;
    head = it;
    head->next->previous = head;
}

template<class type>
void list<type>::pop_back() {

    if (head){
        size--;
        if (head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        item* buf = tail;
        tail = tail->previous;
        tail->next = nullptr;
        if (head == tail){
            head->next = nullptr;
            tail->next = nullptr;
        }
        delete buf;
    }
}

template <class type>
void list<type>::pop_front(){

    if (head){
        size--;
        if (head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        item* buf = head;
        head = head->next;
        head->previous = nullptr;
        delete buf;
        if (head == tail){
            head->previous = nullptr;
            tail->previous = nullptr;
        }
    }
}

template<class type>
type &list<type>::front() {
    if (!head) throw std::runtime_error("Deque is empty\n");
    return head->element;
}

template<class type>
type &list<type>::back() {
    if (!head) throw std::runtime_error("Deque is empty\n");
    return tail->element;
}

template<class type>
bool list<type>::empty() const{
    return (head == nullptr);
}

template<class type>
typename list<type>::iterator list<type>::begin() {
    iterator it;
    it.el = head;
    return it;
}

template<class type>
typename list<type>::iterator list<type>::end(){
    iterator it;
    return it;
}

template<class type>
void list<type>::sort(const std::function<bool(type& a, type& b)> compareFunc) {
    if (!head) return;
    for (int i = 0; i < size; i++){
        item *ptr2;
        item *ptr1;
        ptr1 = head;
        while (ptr1){
            ptr2 = ptr1->next;
            if (ptr2 && !compareFunc(ptr1->element, ptr2->element)) {
                ptr1->next = ptr2->next;
                if (ptr1->next){
                    ptr1->next->previous = ptr1;
                }
                ptr2->previous = ptr1->previous;
                if (ptr2->previous){
                    ptr2->previous->next = ptr2;
                }
                ptr2->next = ptr1;
                ptr1->previous = ptr2;
                if (ptr1 == head){
                    head = ptr2;
                }
                if (ptr2 == tail){
                    tail = ptr1;
                }
                ptr2 = ptr1;
            }
            else {
                ptr1 = ptr2;
            }
        }
    }
}

template<class type>
typename list<type>::iterator &list<type>::iterator::operator++() {
    el = el->next;
    return *this;
}

template<class type>
typename list<type>::iterator &list<type>::iterator::operator++(int) {
    el = el->next;
    return *this;
}

template<class type>
typename list<type>::iterator &list<type>::iterator::operator--() {
    el = el->previous;
    return *this;
}

template<class type>
typename list<type>::iterator &list<type>::iterator::operator--(int) {
    el = el->previous;
    return *this;
}

template<class type>
bool list<type>::iterator::operator==(const iterator& it)  const{
    return el == it->el;
}

template<class type>
const type& list<type>::iterator::operator*() const{
    if (!el) throw std::runtime_error("Wrong iterator\n");
    return el->element;
}

template<class type>
type& list<type>::iterator::operator*(){
    if (!el) throw std::runtime_error("Wrong iterator\n");
    return el->element;
}

template<class type>
bool list<type>::iterator::operator!=(const list::iterator &it) const {
    return el != it->el;
}




