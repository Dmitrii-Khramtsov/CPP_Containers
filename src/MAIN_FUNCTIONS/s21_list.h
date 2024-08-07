// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_list.h
 *
 * @author Mikhail Sokolskiy (jonellab@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-27
 *
 * @copyright School-21 (c) 2024
 */


// MAIN_FUNCTIONS/s21_list.h

#ifndef S21_LIST_H_
#define S21_LIST_H_


#include "../s21_common.h" // на случай, если будем собирать только этот контейнер без остальных

#include "s21_vector.h"

namespace s21 {

template <typename T> // любой тип входных данных
class list {


public:
    // Внутриклассовые переопределения типов (типичные для стандартной библиотеки STL),
    // принятые для удобства восприятия кода класса:

    using value_type = T; // defines the type of an element (T is template parameter)
    using reference = value_type&; // defines the type of the reference to an element
    using const_reference = const value_type&; // defines the type of the constant reference
    using size_type	= size_t; // defines the type of the container size (standard type is size_t)

private:

    struct BaseNode;
    struct Node;

    BaseNode fakeNode_;  // граничный узел для циклического двусвязного списка
    size_type sz_;  // количество узлов в списке

public:

    class iterator;

    // публичные методы для итерирования по элементам класса (доступ к итераторам):
    iterator begin();	// returns an iterator to the beginning
    iterator end();	// returns an iterator to the end
    iterator begin() const;
    iterator end() const;


    // перечислены основные публичные методы для взаимодействия с классом:
    list();	// default constructor, creates empty list
    list(size_type n);	// parameterized constructor, creates the list of size n
    list(std::initializer_list<value_type> const &items); // initializer list constructor
    list(const list &other); // copy constructor
    list(list &&other) noexcept; // move constructor
    ~list(); //	destructor


    list& operator=(list &&other) noexcept; // assignment operator overload for moving object
    bool operator!=(const list &other) const;

    void push_back(const_reference value); // adds an element to the end
    void pop_back(); // removes the last element
    void push_front(const_reference value); // adds an element to the head
    void pop_front(); // removes the first element


    // публичные методы для изменения контейнера:
    void clear(); // clears the contents

    iterator insert(iterator pos, const_reference value); // inserts element into concrete pos and returns the iterator that points to the new element

    template <typename... Args>
    vector<iterator> insert_many(iterator pos, Args &&...args); // Inserts new elements into the container directly before pos.

    template <typename... Args>
    void insert_many_back(Args &&...args); // Appends new elements to the end of the container.

    template <typename... Args>
    void insert_many_front(Args &&...args); // Appends new elements to the top of the container.

    void erase(iterator pos); // erases element at pos

    // публичные методы для доступа к информации о наполнении контейнера:
    bool empty() const;	// checks whether the container is empty
    size_type size() const; // returns the number of elements
    size_type max_size() const; // returns the maximum possible number of elements

    // публичные методы для доступа к элементам класса:
    const_reference front() const; //	access the first element
    const_reference back() const; //	access the last element

    void swap(list& other) noexcept; // swaps the contents
    void merge(list& other); //	merges two sorted lists
    void splice(iterator pos, list& other); //transfers elements from list other starting from pos
    void reverse(); // reverses the order of the elements
    void unique(); // removes consecutive duplicate elements
    void sort(); // sorts the elements

    const Node* get_end() const;
    const Node* get_begin() const;
    const Node* get_next(const BaseNode* node) const;


}; // list

} // s21 namespace

#include "s21_list_iterator.h"  // Включаем заголовок итератора
#include "s21_list.tpp" // Подключаем файл с определениями шаблонов

#endif //S21_LIST_H_