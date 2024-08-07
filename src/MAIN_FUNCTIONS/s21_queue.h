// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_queue.h
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

#ifndef S21_QUEUE_H_
#define S21_QUEUE_H_

#include "s21_list.h"

/**
 * @brief
 * Queue (очередь) - это контейнер с элементами, организованными
 * по принцнипу FIFO (First-In, First-Out). Так же как список,
 * объект контейнерного класса очереди содержит в себе указатели
 * на "хвост" и "голову" очереди, однако удаление производится
 * строго из "головы", а запись, то есть добавление новых элементов,
 * строго в "хвост". Очередь удобно представлять как своего рода
 * трубу, в один конец которой попадают элементы,
 * и убывают с другого конца.
 */



namespace s21 {

template <typename T>
class queue {

public:
using value_type = T; // the template parameter T
using reference	= value_type&; // defines the type of the reference to an element
using const_reference	= const value_type&; // defines the type of the constant reference
using size_type	= size_t; // defines the type of the container size (standard type is size_t)

private:
list<value_type> list_; // Используем контейнер s21::list<T> для эмуляции работы очереди (queue).
                        // Это нам позволит использовать конструкторы, операторы и методы list для queue
                        // Такой вид наследования в ООП называется "композиция"

public:


/******************************************************
 *                                                    *
 *                   КОНСТРУКТОРЫ                     *
 *                                                    *
 ******************************************************/


queue() : list_() {}; //	default constructor, creates empty queue
queue(std::initializer_list<value_type> const &items) : list_(items) {}; //	initializer list constructor, creates queue initizialized using std::initializer_list
queue(const queue &other) : list_(other.list_) {}; //	copy constructor
queue(queue &&other) noexcept : list_(std::move(other.list_)) {}; //	move constructor

queue& operator=(queue&& other) noexcept {
        if (this != &other) {
            list_ = std::move(other.list_);
        }
return *this;
    } // оператор присвоения перемещением


/******************************************************
 *                                                    *
 *                      МЕТОДЫ                        *
 *                                                    *
 ******************************************************/

const_reference front() {
    return list_.front();
} // значение первого элемента

const_reference back() {
    return list_.back();
} // значение последнего

void push(const_reference value) {
    list_.push_back(value);
} // вставка в конец

void pop() {
    list_.pop_front();
} // удаление первого

bool empty(){
    return size() == 0;
} // проверка на пустой контейнер

size_type size() const {
    return list_.size();
} // количество элементов в контейнере

void swap(queue& other){
    list_.swap(other.list_);
}	// swaps the contents

template <typename... Args>
void insert_many_back(Args &&...args) {
    list_.insert_many_back(args...);
}; // Appends new elements to the end of the container.


};

}



#endif // S21_QUEUE_H_