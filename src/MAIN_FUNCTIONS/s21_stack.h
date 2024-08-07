// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_stack.h
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


#ifndef S21_STACK_H_
#define S21_STACK_H_


#include "s21_vector.h"


/**
 * @brief
 * Stack(стек) - это контейнер с элементами,
   организованными по принцнипу LIFO(Last - In, First - Out).
   Объект контейнерного класса стека содержит в себе указатели на
   "голову" стека,
   удаление и добавление элементов производится строго из "головы".Стек удобно
   представлять как стакан или трубу с одним запаянным концом
   : для того чтобы добраться до элемента,
   помещенного в контейнер первым, требуется сначала вынуть все элементы,
   находящиеся сверху.

 */


namespace s21 {

template <typename T>
class stack : private vector<T> {

public:
using value_type = T; // the template parameter T
using reference = value_type&; // defines the type of the reference to an element
using const_reference = const value_type&; // defines the type of the constant reference
using size_type = size_t; // defines the type of the container size (standard type is size_t)


/******************************************************
 *                                                    *
 *                   КОНСТРУКТОРЫ                     *
 *                                                    *
 ******************************************************/



stack() : vector<value_type>() {}; // default constructor, creates empty stack
stack(std::initializer_list<value_type> const &items) : vector<value_type>(items) {}; // initializer stack constructor
stack(const stack &other) : vector<value_type>(other) {};// copy constructor
stack(stack &&other) noexcept : vector<value_type>(std::move(other)) {}; //	move constructor


    // Оператор присваивания копированием
    stack& operator=(const stack& other) {
        if (this != &other) {
            vector<value_type>::operator=(other);
        }
        return *this;
    }

    // Оператор присваивания перемещением
    stack& operator=(stack&& other) noexcept {
            if (this != &other) {
                vector<value_type>::operator=(std::move(other));
            }
    return *this;
        }


/******************************************************
 *                                                    *
 *                      МЕТОДЫ                        *
 *                                                    *
 ******************************************************/




const_reference top() {
    return vector<value_type>::back();
} // accesses the top element


void push(const_reference value) {
    vector<value_type>::push_back(value);
} // inserts element at the top

void pop() {
    vector<value_type>::pop_back();
} // removes the top element


bool empty(){
    return vector<value_type>::empty();
} // checks whether the container is empty

size_type size() {
    return vector<value_type>::size();
} // returns the number of elements

void swap(stack& other){
    vector<value_type>::swap(other);
} // swaps the contents


template <typename... Args>
void insert_many_back(Args &&...args) {
    vector<value_type>::insert_many(vector<value_type>::end(), args...);
} // вставка списка элементов



};

}



#endif // S21_STACK_H_

