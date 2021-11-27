#include "vector.h"

//size_t size;
//size_t capacity;
//type* elements;
template<class type>
vector<type>::vector():size(0), capacity(0), elements(nullptr){}

template<class type>
vector<type>::vector(size_t size_):size(size_), capacity(size_){
    elements = new type[capacity];
    if (elements == nullptr) throw std::bad_alloc();
}

template<class type>
vector<type>::vector(const vector &a) {
    size = a.size;
    capacity = a.capacity;
    elements = new type[capacity];
    if (elements == nullptr) throw std::bad_alloc();
    std::copy(a.elements, a.elements + size, elements);
}

template<class type>
vector<type>::vector(vector &&a) {
    size = a.size;
    capacity = a.capacity;
    elements = a.elements;
    a.elements = nullptr;
}

template<class type>
type &vector<type>::operator[](size_t index){
    if (index >= size) throw std::out_of_range("Wrong index\n");
    return elements[index];
}

template<class type>
type vector<type>::operator[](size_t index) const {
    if (index >= size) throw std::out_of_range("Wrong index\n");
    return elements[index];
}

template<class type>
vector<type>& vector<type>::operator=(const vector &a) {
    if (this != &a){
        size = a.size;
        capacity = a.capacity;
        delete [] elements;
        elements = new type[capacity];
        std::copy(a.elements, a.elements + size, elements);
    }
    return *this;
}

template<class type>
vector<type>& vector<type>::operator=(vector &&a) {
    if (this != &a){
        size_t buf = a.size;
        a.size = size;
        size = buf;
        buf = a.capacity;
        a.capacity = capacity;
        capacity = buf;
        type* bufType = a.elements;
        a.elements = elements;
        elements = bufType;
    }
    return *this;
}

template<class type>
vector<type>::~vector() {
    delete [] elements;
}







