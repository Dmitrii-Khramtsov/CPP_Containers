// s21_containers.h

#ifndef S21_CONTAINERS_H_
#define S21_CONTAINERS_H_

#include "s21_common.h"


#include "MAIN_FUNCTIONS/s21_vector.h"
#include "MAIN_FUNCTIONS/s21_array.h"
#include "MAIN_FUNCTIONS/s21_stack.h"
#include "MAIN_FUNCTIONS/s21_list.h"
#include "MAIN_FUNCTIONS/s21_map.h"
#include "MAIN_FUNCTIONS/s21_multiset.h"
#include "MAIN_FUNCTIONS/s21_set.h"
#include "MAIN_FUNCTIONS/s21_queue.h"


namespace s21 {

template <typename T>
class vector;

template <typename T, std::size_t N>
class array;

template <typename T>
class stack;

template <typename T>
class list;

template <typename T>
class queue;

template <typename Key, typename Value> class Map;

template <typename Key>
class Set;

template <typename Key>
class MultiSet;

}


#endif  // S21_CONTAINERS_H_