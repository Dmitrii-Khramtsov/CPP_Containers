// Copyright 2024 Dmitrii Khramtsov

/**
 * @file s21_set.h
 *
 * @author Dmitrii Khramtsov (lonmouth@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-27
 *
 * @copyright School-21 (c) 2024
 */

#ifndef CPP2_S21_CONTAINERS_SAT_H_
#define CPP2_S21_CONTAINERS_SAT_H_

#include "../SUPPORT_FUNCTIONS/rb_tree.h"
#include "../s21_common.h" // на случай, если будем собирать только этот контейнер без остальных

namespace s21 {

template <typename Key> class Set {
public:
  // Set Member type:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using rb_tree = s21::RBTree<Key>;
  using iterator = typename rb_tree::iterator;
  using const_iterator = typename rb_tree::const_iterator;

  // Set Member functions:
  Set();
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &s);
  Set(Set &&s) noexcept;
  ~Set();
  Set &operator=(const Set &s);
  Set &operator=(Set &&s) noexcept;

  // Set Iterators:
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Set Capacity:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Set Modifiers:
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos) noexcept;
  void swap(Set &other) noexcept;
  void merge(Set &other);
  std::pair<iterator, bool>
  emplace(Key &&key); // метод emplace предназначен для вставки элемента
                      // в контейнер, используя перемещение (move semantics)
                      // вместо копирования

  // Set Lookup:
  bool
  contains(const key_type &key) const; // проверяет, есть ли в контейнере
                                       // элемент с ключом, эквивалентным ключу
  iterator find(const Key &key);
  const_iterator find(const Key &key) const;

  // Debugging methods:
  void drawSet();

private:
  rb_tree tree_;
};
} // namespace s21

#include "s21_set.tpp"

#endif // CPP2_S21_CONTAINERS_SAT_H_
