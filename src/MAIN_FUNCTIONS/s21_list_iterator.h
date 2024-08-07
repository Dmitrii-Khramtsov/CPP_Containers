// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_list_iterator.h
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

// MAIN_FUNCTIONS/s21_list_iterator.h

#ifndef S21_LIST_ITERATOR_H_
#define S21_LIST_ITERATOR_H_

#include <iterator>  // Для std::ptrdiff_t и std::bidirectional_iterator_tag

#include "s21_list.h" // нужно для компиляции, когда объектник итератора компилится быстрее родительского

namespace s21 {


    template <typename T>
        class list<T>::iterator {

    public:
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

    private:
        BaseNode* ptr_; // в переменной итератора хранится просто указатель на базовую ноду

        iterator (BaseNode* ptr): ptr_(reinterpret_cast<BaseNode*>(ptr)) {}

        friend class list<value_type>;

    public:
        iterator() : ptr_(nullptr) {} // Конструктор по умолчанию необходим для insert_many

        value_type& operator*() const {return reinterpret_cast<Node*>(ptr_)->value_;} // разыменование итератора возвращает значение value_

        iterator& operator++() {
            ptr_ = ptr_->next_;
            return *this;} // инкремент префиксный. Возвращает адрес следующей ноды

        iterator operator++(int) {
            iterator Copy = *this;
            ptr_ = ptr_->next_;
            return Copy;} // инкремент постфиксный

        iterator& operator--() {
            ptr_=ptr_->prev_;
            return *this;
        }
        iterator operator--(int) {
            iterator Copy = *this;
            ptr_ = ptr_->prev_;
            return Copy;
        }

        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }

        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        iterator& prev(const iterator&) {
            return --*this;
        }

        iterator& next(const iterator&) {
            return ++*this;
        }

        // BaseNode* get_node_address() {
        //     return ptr_;
        // }

    };


}  // namespace s21

#endif  // S21_LIST_ITERATOR_H_