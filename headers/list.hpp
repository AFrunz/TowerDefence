#ifndef TOWERDEFENCE_LIST
#define TOWERDEFENCE_LIST
#include <functional>


/// Шаблонный класс список
template <class type>
class list {
protected:
/// Элемент списка
    struct item{
        item* next;                                                 ///< Следующий эл-т
        item* previous;                                             ///< Предыдущий эл-т
        type element;                                               ///< Информация
        item():next(nullptr), previous(nullptr), element(){};
    };
public:
/// Итератор для класса list
    class iterator{
    private:
        item* el;                                                    ///< Элемент
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
        friend class list;
    };

private:
    size_t size;                                    ///< Количество элементов в списке
    item* head;                                     ///< Начало списка
    item* tail;                                     ///< Конец списка
public:
    list<type>();
    list(const list&);
    list(list&&);

    bool empty() const;                                                     ///< Показывает отсутствие эл-в
    void push_back(const type& element);                                    ///< Добавление эл-та в конец
    void push_front(const type& element);                                   ///< добавление эл-та в начало
    void pop_back();                                                        ///< Удаление последнего эл-та
    void pop_front();                                                       ///< Удаление первого элемента
    type& front();                                                          ///< Получение первого эл-та
    type& back();                                                           ///< Получение последнего эл-та
    void sort(const std::function<bool(type& a, type& b)> compareFunc);     ///< Сортировка списка
    friend class iterator;
    iterator begin();                                                       ///< Получение итератора на начало
    iterator end();                                                         ///< Получение итератора на конец


    list<type>& operator= (const list&);
    list<type>& operator= (list&&);
    virtual ~list();

};


#include "list.inl"

#endif
