// Copyright 2024 Dmitrii Khramtsov

/**
 * @file s21_map.h
 *
 * @author Dmitrii Khramtsov (lonmouth@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-25
 *
 * @copyright School-21 (c) 2024
 */

#ifndef CPP2_S21_CONTAINERS_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_H_

#include <iostream>

#include "../SUPPORT_FUNCTIONS/rb_tree.h"
#include "../s21_common.h" // на случай, если будем собирать только этот контейнер без остальных

namespace s21 {

template <typename Key, typename Value> class Map {
public:
  // Map Member type:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  class MapComparator {
  public:
    bool operator()(const_reference key_1,
                    const_reference key_2) const noexcept {
      return key_1.first < key_2.first;
    }
  };

  using rb_tree = s21::RBTree<value_type, MapComparator>;
  using iterator = typename rb_tree::iterator;
  using const_iterator = typename rb_tree::const_iterator;

  // Map Member functions:
  Map();
  Map(std::initializer_list<value_type> const &items);
  Map(const Map &m);
  Map(Map &&m) noexcept;
  ~Map();
  Map &operator=(const Map &m);
  Map &operator=(Map &&m) noexcept;

  // Map Element access:
  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  // Map Iterators:
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Map Capacity:
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers:
  void clear() noexcept;
  std::pair<iterator, bool> insert(
      const value_type &value); // вставляет узел и возвращает итератор
                                // до места расположения элемента в контейнере
                                // и bool обозначающий, произошла ли вставка

  std::pair<iterator, bool>
  insert(const key_type &key,
         const mapped_type
             &obj); // вставляет значение по ключу и возвращает итератор
                    // по месту расположения элемента в контейнере и bool,
                    // обозначающий, произошла ли вставка

  std::pair<iterator, bool> insert_or_assign(
      const key_type &key,
      const mapped_type &obj); // вставляет элемент или присваивает
                               // текущему элементу, если ключ уже существует

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  void erase(iterator pos) noexcept;
  void swap(Map &other) noexcept;
  void merge(Map &other);
  std::pair<iterator, bool>
  emplace(Key &&key,
          Value &&value); // метод emplace предназначен для вставки элемента
                          // в контейнер, используя перемещение (move semantics)
                          // вместо копирования

  // Map Lookup:
  bool
  contains(const key_type &key) const; // проверяет, есть ли в контейнере
                                       // элемент с ключом, эквивалентным ключу
  iterator find(const Key &key);
  const_iterator find(const Key &key) const;

  // Debugging methods:
  void drawMap() const;

private:
  rb_tree tree_;
};

} // namespace s21

#include "s21_map.tpp"

#endif // CPP2_S21_CONTAINERS_MAP_H_
