// Copyright 2024 Dmitrii Khramtsov

/**
 * @file s21_multiset.h
 *
 * @author Dmitrii Khramtsov (lonmouth@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-26
 *
 * @copyright School-21 (c) 2024
 */

#ifndef CPP2_S21_CONTAINERS_MULTISAT_H_
#define CPP2_S21_CONTAINERS_MULTISAT_H_

#include <iostream>

#include "../SUPPORT_FUNCTIONS/rb_tree.h"
#include "../s21_common.h" // на случай, если будем собирать только этот контейнер без остальных

namespace s21 {

template <typename Key> class MultiSet {
public:
  // MultiSet Member type:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using rb_tree = s21::RBTree<Key>;
  using iterator = typename rb_tree::iterator;
  using const_iterator = typename rb_tree::const_iterator;

  // MultiSet Member functions:
  MultiSet();
  MultiSet(std::initializer_list<value_type> const &items);
  MultiSet(const MultiSet &s);
  MultiSet(MultiSet &&s) noexcept;
  ~MultiSet();
  MultiSet &operator=(const MultiSet &s);
  MultiSet &operator=(MultiSet &&s) noexcept;

  // MultiSet Iterators:
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // MultiSet Capacity:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // MultiSet Modifiers:
  void clear() noexcept;
  iterator insert(const value_type &value);
  template <typename... Args> std::vector<iterator> insert_many(Args &&...args);
  void erase(iterator pos) noexcept;
  void swap(MultiSet &other) noexcept;
  void merge(MultiSet &other);
  size_type
  count(const Key &key) const noexcept; // Возвращает количество элементов,
                                        // соответствующих заданному ключу.
  iterator emplace(Key &&key); // метод emplace предназначен для вставки
                               // элемента в контейнер, используя перемещение
                               // (move semantics) вместо копирования
  std::pair<iterator, iterator> equal_range(const Key &key);
  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const;
  iterator lower_bound(
      const Key &key) noexcept; // используется для поиска первого элемента с
                                // ключом, большим или равным данному
  const_iterator lower_bound(const Key &key) const noexcept;
  iterator upper_bound(
      const Key &key) noexcept; // используется для поиска первого элемента с
                                // ключом, меньшим или равным данному
  const_iterator upper_bound(const Key &key) const noexcept;

  // MultiSet Lookup:
  bool
  contains(const key_type &key) const; // проверяет, есть ли в контейнере
                                       // элемент с ключом, эквивалентным ключу
  iterator find(const Key &key);
  const_iterator find(const Key &key) const;

  // Debugging methods:
  void drawMultiSet();

private:
  rb_tree tree_;
};

} // namespace s21

#include "s21_multiset.tpp"

#endif // CPP2_S21_CONTAINERS_MULTISAT_H_
