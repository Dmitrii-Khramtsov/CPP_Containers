// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_array.h
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

// MAIN_FUNCTIONS/s21_array.h

#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_


#include "s21_vector.h"


namespace s21 {

template <typename T, std::size_t N> // любой тип входных данных
class array : public vector<T> {

public:

using value_type =	T;  //defines the type of an element (T is template parameter)
using const_reference = const value_type&; // defines the type of the constant reference
using size_type	= size_t; //defines the type of the container size (standard type is size_t)

array() : vector<value_type>(N){} //	default constructor, creates empty array
array(std::initializer_list<value_type> const &items) : array() {
    if (items.size() != N) std::cerr <<
    "\narray(std::initializer_list ..) : Количество элементов в "
    "Initializer list не совпадает с размером N массива!\n\n";

     auto it = vector<value_type>::begin();
     for (const value_type& item : items)
         *it++ = item;
}	// initializer list constructor

array(const array &other) : vector<value_type>(other) {} //	copy constructor
array(array &&other) noexcept : vector<value_type>(std::move(other)) {} //	move constructor


// Оператор перемещения
array& operator=(array&& other) noexcept {
        if (this != &other) {
            vector<value_type>::operator=(std::move(other));
        }
return *this;
    }

void fill(const_reference value) {
    for (size_type i = 0; i < vector<value_type>::size() ; ++i) vector<value_type>::at(i) = value;
} //	assigns the given value to all elements in the container.

// возвращает максимальное теоретическое количество элементов, которые могут быть записаны в вектор для этого типа данных
size_type max_size() noexcept {
        return vector<value_type>::size();
}


private:

    using s21::vector<value_type>::reserve;	//allocate storage of size elements and copies current array elements to a newly allocated array
    using s21::vector<value_type>::capacity;	//returns the number of elements that can be held in currently allocated storage
    using s21::vector<value_type>::shrink_to_fit;	//reduces memory usage by freeing unused memory
    using s21::vector<value_type>::clear;	//clears the contents
    using s21::vector<value_type>::insert;	//inserts elements into concrete pos and returns the iterator that points to the new element НЕТ В СТАНДАРТНОМ ВЕКТОРЕ
    using s21::vector<value_type>::erase;	//erases element at pos НЕТ В СТАНДАРТНОМ ВЕКТОРЕ
    using s21::vector<value_type>::push_back;	//adds an element to the end
    using s21::vector<value_type>::pop_back;	//removes the last element
    using s21::vector<value_type>::insert_many; //inserts new elements into the container directly before pos.
    using s21::vector<value_type>::insert_many_back; //Appends new elements to the end of the container.

}; // array


// Руководство по выводу шаблонных аргументов
// (если не хотим указывать тип и размер объекта
//  в случае списка инициализации)
template <typename T, typename... Args>
array(T, Args...) -> array<T, sizeof...(Args) + 1>;


} // s21 namespace



#endif //S21_ARRAY_H_