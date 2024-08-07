// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_list.tpp
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


// MAIN_FUNCTIONS/s21_list.tpp

#ifndef S21_LIST_TPP_
#define S21_LIST_TPP_

#include "s21_vector.h"

namespace s21 {

/******************************************************
 *                                                    *
 *                 ОПРЕДЕЛЕНИЕ НОДЫ                   *
 *                                                    *
 ******************************************************/


                template <typename value_type>
struct          list<value_type>::
       BaseNode {
        BaseNode* prev_;
        BaseNode* next_;

        BaseNode(BaseNode* prev, BaseNode* next) : prev_(prev), next_(next) {}

    };


                    template <typename value_type>
struct              list<value_type>::
        Node : public BaseNode {

        value_type value_;

        Node(BaseNode* prev, BaseNode* next, const value_type& val)
            : BaseNode(prev, next), value_(val) {}
    };


/******************************************************
 *                                                    *
 *                   КОНСТРУКТОРЫ                     *
 *                                                    *
 ******************************************************/

            template <typename value_type>
            list<value_type>::
    list() : fakeNode_{&fakeNode_, &fakeNode_}, sz_(0) {}



            template <typename value_type>
            list<value_type>::
    list(size_type n) : list() {
        for (size_type i = 0; i < n; ++i) {
            push_back(value_type());
        }
    }


            template <typename value_type>
            list<value_type>::
    list(std::initializer_list<value_type> const& items) : list() {
        for (const auto& item : items) {
            push_back(item);
        }
    }


            template <typename value_type>
            list<value_type>::
    list(const list& other) : list() {

        const Node* from = other.get_begin();

        for (size_type i = 0; i<other.size(); ++i)
        {
            push_back(from->value_);
            from = other.get_next(from);
        }
    } // copy constructor


            template <typename value_type>
            list<value_type>::
    list(list&& other) noexcept : list() {

        // std::cout <<  RED_ALERT_COLOR <<  "\nВызван конструктор"
        // " перемещения\n" << NORMAL_COLOR <<std::endl;

        clear();
        swap(other);

    } // Реализация конструктора перемещения


            template <typename value_type>
            list<value_type>::
    ~list() {
        clear();
        } //	destructor


/******************************************************
 *                                                    *
 *                    ОПЕРАТОРЫ                       *
 *                                                    *
 ******************************************************/


                         template <typename value_type>
list<value_type>&        list<value_type>::
         operator=(list &&other) noexcept {

        // std::cout <<  RED_ALERT_COLOR <<  "\nВызван оператор "
        // "присваивания перемещением (=) \n" << NORMAL_COLOR <<std::endl;

        clear();
        swap(other);

        return *this;

    } // assignment operator overload for moving object


                        template <typename value_type>
bool                    list<value_type>::
     operator!=(const list& other) const {
            return &fakeNode_ != &other.fakeNode_;
        }



/******************************************************
 *                                                    *
 *                      МЕТОДЫ                        *
 *                                                    *
 ******************************************************/



                        template <typename value_type>
                        typename list<value_type>::
size_type               list<value_type>::
          size() const {
            return sz_;
    }



                                            template <typename value_type>
void                                        list<value_type>::
     push_back(const_reference value) {

        Node* newNode = new Node(fakeNode_.prev_, &fakeNode_, value);
        fakeNode_.prev_->next_ = newNode;
        fakeNode_.prev_ = newNode;
        ++sz_;
    }



                                            template <typename value_type>
void                                        list<value_type>::
     pop_back() {

        erase(fakeNode_.prev_);

    }



                                            template <typename value_type>
void                                        list<value_type>::
     push_front(const_reference value) {
        Node* newNode = new Node(&fakeNode_, fakeNode_.next_, value);
        fakeNode_.next_->prev_ = newNode;
        fakeNode_.next_ = newNode;
        ++sz_;
    } // adds an element to the head




                                            template <typename value_type>
void                                        list<value_type>::
     pop_front() {

        erase(fakeNode_.next_);

    } // removes the first element



                                            template <typename value_type>
void                                        list<value_type>::
     swap(list& other) noexcept {

        if (sz_ > 0 && other.sz_ > 0) {
        std::swap(fakeNode_.prev_->next_, other.fakeNode_.prev_->next_);
        std::swap(fakeNode_.next_->prev_, other.fakeNode_.next_->prev_);
        std::swap(fakeNode_.prev_, other.fakeNode_.prev_);
        std::swap(fakeNode_.next_, other.fakeNode_.next_);
        }
        else if (sz_ == 0 && other.sz_ > 0) {
        other.fakeNode_.prev_->next_ =  other.fakeNode_.next_->prev_ = &fakeNode_;

        fakeNode_.prev_ = exchange(other.fakeNode_.prev_, &other.fakeNode_);
        fakeNode_.next_ = exchange(other.fakeNode_.next_, &other.fakeNode_);

        } else if (sz_ > 0 && other.sz_ == 0)  {
        fakeNode_.prev_->next_ = fakeNode_.next_->prev_ = &other.fakeNode_;

        other.fakeNode_.prev_ = exchange(fakeNode_.prev_, &fakeNode_);
        other.fakeNode_.next_ = exchange(fakeNode_.next_, &fakeNode_);
        }

        std::swap(sz_, other.sz_);

    } // swaps the contents


                                            template <typename value_type>
void                                        list<value_type>::
     reverse() {

        BaseNode* current = fakeNode_.next_;

        for (size_type i = 0; i<size()+1; ++i) {
            std::swap(current->next_, current->prev_);
            current = current->prev_; // на самом деле здесь уже next_
        }

    } // reverses the order of the elements


                                            template <typename value_type>
void                                        list<value_type>::
     erase (iterator pos) {
        if (sz_ > 0) {
            pos.ptr_->prev_->next_ = pos.ptr_->next_;
            pos.ptr_->next_->prev_ = pos.ptr_->prev_;
            delete reinterpret_cast<Node*>(pos.ptr_);
            --sz_;
        }
    }


                                            template <typename value_type>
void                                        list<value_type>::
     unique() {

        if (size() >= 2) {

            BaseNode* current = fakeNode_.next_;

            while (current != &fakeNode_) {

                if (reinterpret_cast<Node*>(current)->value_ == reinterpret_cast<Node*>(current->next_)->value_)
                    erase(current->next_);
                else current = current->next_;
            }
        }

    } // removes consecutive duplicate elements



    // Функция сортировки s21::list
    // Создаётся вектор для указателей на адреса нод
    // Вектор передаётся в стандартную функцию std::sort, которая сортирует
    // указатели по принципу где меньше значение value_ в ноде
    // В соответствии с отсортированным вектором указателей меняются поля
    // prev_ и next_ уже непосредственно в самих нодах
                                            template <typename value_type>
void                                        list<value_type>::
     sort() {

        s21::vector<BaseNode*> nodes;
        nodes.reserve(size()+2); // Обрати внимание, что размер вектора для указателей нод
                                 // создаётся специально на 2 больше, чем количество нод.
                                 // Это нужно для удобства, чтоб в нулевой элемент и
                                 // в последний записать адрес фейковой ноды, а потом в цикле
                                 // после сортировки вектора указателей на ноды, потом будет
                                 // легче записать значения полей prev_ первой ноде и next_
                                 // последней на фейковую, и при этом не городить кучу условий

        nodes.push_back(&fakeNode_); // в нулевую ячейку сразу записываем адрес фейковой ноды

        for (iterator it = begin();
                       it != end();
                               ++it)  nodes.push_back(it.ptr_); // в вектор записываются указатели на ноды

        nodes.push_back(&fakeNode_);  // в последнюю ячейку записываем адрес фейковой ноды

        // В стандартную функцию сортировки передаются итераторы
        // на первый(за нулевым) и предпоследний элементы вектора указателей на ноды.
        // Нулевой и последний итераторы(у вектора это указатели) не передаются,
        // так как в них лежит адрес фейковой ноды.
        // Кроме того, в сортировку передаётся лямбда-функция(сравнивает значения между нодами) для
        // упорядочивания указателей в векторе.
        auto begin = nodes.begin()+1;
        auto end = nodes.end()-1;
        std::sort( begin, end,
                    [](const BaseNode* a, const BaseNode* b) {
                       return (reinterpret_cast<const Node*>(a)->value_ ) < (reinterpret_cast<const Node*>(b)->value_);
                      }
                 );

        // // печать значений по отсортированным указателям в векторе для проверки сортировки
        // for (size_type i=1; i < nodes.size()-1; ++i)
        //     {std::cout << reinterpret_cast<Node*>(nodes[i])->value_ << " ";}
        //     std::cout << std::endl;

        // цикл записывает новые значения адресов для каждой текущей ноды
        // и её полей prev_ и next_ в соответствии с отсортированными адресами нод в векторе
            BaseNode* current;
        for (size_type i=1; i < nodes.size()-1; ++i) {
            current = nodes[i];
            current->next_ = nodes[i+1];
            current->prev_ = nodes[i-1];
        }

        // В конце записываем новые значения в поля фейковой ноды
        fakeNode_.next_ = nodes[1];
        fakeNode_.prev_ = nodes[nodes.size()-2];

    } // sorts the elements


                                            template <typename value_type>
void                                        list<value_type>::
     clear() {

        while (sz_ > 0) pop_back();

    } // clears the contents



                                            template <typename value_type>
bool                                        list<value_type>::
     empty() const {

        return sz_ == 0;
    }



                                            template <typename value_type>
                                            typename list<value_type>::
const_reference                             list<value_type>::
                front() const {

        return reinterpret_cast<const Node*>(fakeNode_.next_)->value_;

    } //	access the first element




                                            template <typename value_type>
                                            typename list<value_type>::
const_reference                             list<value_type>::
                back() const {

        return reinterpret_cast<const Node*>(fakeNode_.prev_)->value_;

    } //	access the last element




                                            template <typename value_type>
                                            typename list<value_type>::
iterator                                    list<value_type>::
         insert(iterator pos, const_reference value) {

        Node* newNode = new Node(pos.ptr_->prev_, pos.ptr_, value);
        pos.ptr_->prev_->next_ = newNode;
        pos.ptr_->prev_ = newNode;
        ++sz_;

      return newNode;

    } // inserts element into concrete pos and returns the iterator that points to the new element



                                            template <typename value_type>
void                                        list<value_type>::
     merge(list& other) {

        if (*this != other) {
// Создайте два итератора it1 и it2, которые указывают на начало
// первой и второй отсортированных последовательностей соответственно.
    iterator it1 = begin();
    iterator it2 = other.begin();

// Создайте пустой список result, который будет содержать
// отсортированную последовательность.

    s21::list<value_type> result;


//    Пока it1 не достиг конца первой отсортированной последовательности и
//    it2 не достиг конца второй отсортированной последовательности,
//    выполняйте следующие действия:
//
// 1. Сравните значения, на которые указывают it1 и it2.
// 2. Если значение, на которое указывает it1, меньше или равно значению,
//    на которое указывает it2, добавьте значение, на которое указывает it1,
//    в конец списка result и увеличьте it1 на один шаг.
// 3. В противном случае добавьте значение, на которое указывает it2,
//    в конец списка result и увеличьте it2 на один шаг.

    while (it1 != end() && it2 != other.end()) {
        if (*it1 <= *it2)  {
            result.push_back(*it1);
            ++it1;
        }
        else {
            result.push_back(*it2);
            ++it2;
        }
    }


// После того, как один из итераторов it1 или it2 достигнет конца
// своей отсортированной последовательности, добавьте все оставшиеся
// элементы другой отсортированной последовательности в конец списка result.
    if (it1 == end())
         while (it2 != other.end()) result.push_back(*it2++);
    else
         while (it1 != end()) result.push_back(*it1++);

// Верните список result в качестве результата.
    *this = std::move(result);

    other.clear();
        }
    } // merges two sorted lists


// template <typename value_type>
// void list<value_type>::merge(list& other) {
//     if (this != &other) {
//         iterator it1 = begin();
//         iterator it2 = other.begin();

//         // Сначала обрабатываем элементы, пока ни один из списков не закончился
//         while (it1 != end() && it2 != other.end()) {
//             if (*it2 < *it1) {
//                 it1 = insert(it1, *it2);
//                 ++it2;
//             } else {
//                 ++it1;
//             }
//         }

//         // Если в 'other' остались элементы, добавляем их в текущий список
//         while (it2 != other.end()) {
//             push_back(*it2);
//             ++it2;
//         }

//         // Очищаем другой список
//         other.clear();
//     }
// }



                                            template <typename value_type>
const                                       typename list<value_type>::
      Node*         list<value_type>::
            get_end() const {
        return reinterpret_cast<const Node*>(&fakeNode_);
    }

                                            template <typename value_type>
const                                       typename list<value_type>::
      Node*         list<value_type>::
            get_begin() const {
        return reinterpret_cast<const Node*>(fakeNode_.next_);
    }

                                            template <typename value_type>
const                                       typename list<value_type>::
      Node*         list<value_type>::
            get_next(const BaseNode* node) const {
    return reinterpret_cast<const Node*>(node->next_);
}

                                            template <typename value_type>
                                            typename list<value_type>::
size_type                                   list<value_type>::
          max_size() const {

        return static_cast<size_type>(-1)/ (sizeof(list(1))); // Число (-1) преобразуется в size_t, что даёт
                                                              // максимальное значение для типа size_t
                                                              // это будет эквивалентно константе SIZE_MAX
                                                              // потом происходит деление на размер одной ноды,
                                                              // в итоге получаем максимальное количество нод в list
    } // returns the maximum possible number of elements


                                            template <typename value_type>
void                                        list<value_type>::
     splice(iterator pos, list& other) {

        auto previous_node = pos.ptr_->prev_; // обозначаем ноду, после которой будет вставка другого листа
        auto next_node = pos.ptr_; // обозначаем ноду, которая будет идти за вставкой другого листа

        auto first_insert_node = other.fakeNode_.next_; // обозначаем первую ноду из вставляемого листа
        auto last_insert_node = other.fakeNode_.prev_; // обозначаем последнюю ноду вставляемого листа

        previous_node->next_ = first_insert_node;
        next_node->prev_ = last_insert_node;

        first_insert_node->prev_ = previous_node;
        last_insert_node->next_ = next_node;

        sz_ += other.sz_;
        other.sz_ = 0;
        other.fakeNode_.prev_ = other.fakeNode_.next_ = &other.fakeNode_;

    } //transfers elements from list other starting from pos


                                            template <typename value_type>
                                            typename list<value_type>::
iterator                                    list<value_type>::
         begin() {
    return iterator(fakeNode_.next_);
}

                                            template <typename value_type>
                                            typename list<value_type>::
iterator                                    list<value_type>::
         begin() const {
    return iterator(fakeNode_.next_);
}

                                            template <typename value_type>
                                            typename list<value_type>::
iterator                                    list<value_type>::
         end() {
    return iterator(&fakeNode_);
}

                                            template <typename value_type>
                                            typename list<value_type>::
iterator                                    list<value_type>::
         end() const {
    return iterator(&fakeNode_);
}


                                            template <typename value_type>
                                            template <typename... Args>
s21::vector<typename list<value_type>::iterator>
                                            list<value_type>::
            insert_many(iterator pos, Args &&...args) {

                s21::vector<iterator> results; // создаём вектор с типом указателей на ноды листа (итераторы)

                (results.push_back(
                                    insert(pos, std::forward<Args>(args)) // вставляем в лист начиная с позиции pos друг за дружкой
                                  ), ...);                                // элементы args... используя функцию forward, и возвращаем
                                                                          // их адреса, которые записываем в вектор
            return results;  // возвращает вектор с указателями
}                            // на адреса вставленных нод

                                            template <typename value_type>
                                            template <typename... Args>
void
     list<value_type>::insert_many_back(Args &&...args) {
        insert_many(end(), args...);
}

                                            template <typename value_type>
                                            template <typename... Args>
void
     list<value_type>::insert_many_front(Args &&...args) {
        insert_many(begin(), args...);
}



}  // namespace s21

#endif  // S21_LIST_TPP_