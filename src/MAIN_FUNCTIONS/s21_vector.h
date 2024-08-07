// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_vector.h
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


#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_


#include "../s21_common.h" // на случай, если будем собирать только этот контейнер или его наследник без остальных
#include <memory> // нужно для умных указателей


namespace s21 {

template <typename T> // любой тип входных данных
class vector{

public:

    // Внутриклассовые переопределения типов (типичные для стандартной библиотеки STL), 
    // принятые для удобства восприятия кода класса:

    using value_type =	T;                     // defines the type of an element (T is template parameter)
    using reference	= value_type&;             // defines the type of the reference to an element
    using const_reference = const value_type&; // defines the type of the constant reference
    using iterator = value_type*;              // defines the type for iterating through the container
    using const_iterator = const value_type*;  // defines the constant type for iterating through the container
    using size_type	= size_t;                  // defines the type of the container size (standard type is size_t)

    //В этой таблице перечислены основные публичные методы для взаимодействия с классом:
    vector() = default;                                      //default constructor, creates empty vector
    vector(size_type n);                                     //parameterized constructor, creates the vector of size n
    vector(std::initializer_list<value_type> const &items);  //initializer list constructor

    // Шаблонный конструктор для незаданного в <> типа , например s21::vector num{1,2,3};
    template <typename NoTypeIn>
    vector(NoTypeIn first, NoTypeIn last);

    vector(const vector &v);       //copy constructor
    vector(vector &&v) noexcept;   //move constructor

    // ~vector() noexcept;  //destructor для случая обычного указателя
    ~vector() = default;    // при использовании умных указателей они очищаются самостоятельно

    vector& operator=(const vector &v);      // оператор присвоения копированием
    vector& operator=(vector &&v) noexcept;  //assignment operator overload for moving object

    // В этой таблице перечислены публичные методы для доступа к элементам класса:
    reference at(size_type pos);          //access specified element with bounds checking
    reference operator[](size_type pos);  //access specified element


    const_reference front();    //access the first element
    const_reference back();     //access the last element
    iterator data();            //direct access to the underlying arrayVector Iterators

    // В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):
    iterator begin();   //returns an iterator to the beginning
    iterator end();     //returns an iterator to the end

    // В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:
    bool empty();                         //checks whether the container is empty
    size_type size();                     //returns the number of elements
    size_type max_size() const noexcept;  //returns the maximum possible number of elements
    void reserve(size_type size);         //allocate storage of size elements and copies current array elements to a newly allocated array
    size_type capacity();                 //returns the number of elements that can be held in currently allocated storage
    void shrink_to_fit();                 //reduces memory usage by freeing unused memory

    // В этой таблице перечислены публичные методы для изменения контейнера:
    void clear();                                           //clears the contents
    iterator insert(iterator pos, const_reference value);	//inserts elements into concrete pos and returns the iterator that points to the new element НЕТ В СТАНДАРТНОМ ВЕКТОРЕ
    void erase(iterator pos);                               //erases element at pos НЕТ В СТАНДАРТНОМ ВЕКТОРЕ
    void push_back(const_reference value);                  //adds an element to the end
    void pop_back();                                        //removes the last element
    void swap(vector& other);                               //swaps the contents

    template <typename... Args>
    vector<iterator> insert_many(iterator pos, Args &&...args); // Inserts new elements into the container directly before pos.

    template <typename... Args>
    void insert_many_back(Args &&...args);  // Appends new elements to the end of the container.

private:
    size_type size_ = 0;                           // размер вектора
    size_type capacity_ = 0;                       // ёмкость вектора
    // value_type* data_ = nullptr;                   // обычный опасный указатель на массив элементов
    std::unique_ptr<value_type[]> data_ = nullptr; // умный указатель на массив (не нужно писать деструктор. Очищается сам)



}; // vector

} // s21 namespace


#include "s21_vector.tpp" // Подключаем файл с определениями шаблонов

#endif //S21_VECTOR_H_