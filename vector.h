#ifndef TOWERDEFENCE_VECTOR_H
#define TOWERDEFENCE_VECTOR_H
#include <iostream>

template <class type>
class vector {
private:
    size_t size;
    size_t capacity;
    type* elements;
public:
    vector<type>();
    vector<type>(size_t);
//    vector<type>(size_t, type);
    vector(const vector&);
    vector(vector&&);

    type& operator[](size_t);
    type operator[](size_t) const;
//    type& at(size_t);
//    type at(size_t) const;

    vector<type>& operator= (const vector&);
    vector<type>& operator= (vector&&);
    virtual ~vector();
};




#endif //TOWERDEFENCE_VECTOR_H
