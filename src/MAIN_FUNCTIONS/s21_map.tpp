// Copyright 2024 Dmitrii Khramtsov

/**
 * @file s21_map.tpp
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

namespace s21 {

/******************************************************************************
 * CONSTRUCTOR & DESTRUCTOR
 ******************************************************************************/

/**
 * @brief Default constructor.
 */
template <typename Key, typename Value> Map<Key, Value>::Map() : tree_() {}

/**
 * @brief Constructor with initializer list.
 * @param items Initializer list of value_type.
 */
template <typename Key, typename Value>
Map<Key, Value>::Map(std::initializer_list<value_type> const &items) : tree_() {
  for (auto item : items) {
    this->tree_.insertUnique(item);
  }
}

/**
 * @brief Copy constructor.
 * @param m Map to copy.
 */
template <typename Key, typename Value>
Map<Key, Value>::Map(const Map &m) : tree_(m.tree_) {}

/**
 * @brief Move constructor.
 * @param m Map to move.
 */
template <typename Key, typename Value>
Map<Key, Value>::Map(Map &&m) noexcept : tree_(std::move(m.tree_)) {}

/**
 * @brief Destructor.
 */
template <typename Key, typename Value> Map<Key, Value>::~Map() = default;

/**
 * @brief Copy assignment operator.
 * @param m Map to copy.
 * @return Reference to this Map.
 */
template <typename Key, typename Value>
Map<Key, Value> &Map<Key, Value>::operator=(const Map &m) {
  this->tree_ = m.tree_;
  return *this;
}

/**
 * @brief Move assignment operator.
 * @param m Map to move.
 * @return Reference to this Map.
 */
template <typename Key, typename Value>
Map<Key, Value> &Map<Key, Value>::operator=(Map &&m) noexcept {
  this->tree_ = std::move(m.tree_);
  return *this;
}

/******************************************************************************
 * MAIN METHODS
 ******************************************************************************/

// Map Element access
/**
 * @brief Access specified element with bounds checking.
 * @param key Key of the element to access.
 * @return Reference to the mapped value.
 * @throws std::out_of_range if key not found.
 */
template <typename Key, typename Value>
typename Map<Key, Value>::mapped_type &
Map<Key, Value>::at(const key_type &key) {
  auto it = this->find(key);
  if (it == this->end()) {
    throw std::out_of_range("Key not found");
  }
  return it->second;
}

/**
 * @brief Access or insert value.
 * @param key Key of the element to access.
 * @return Reference to the mapped value.
 */
template <typename Key, typename T>
typename Map<Key, T>::mapped_type &
Map<Key, T>::operator[](const key_type &key) {
  auto it = this->find(key);

  // если элемент найден, вернуть его значение
  if (it != this->end()) {
    return it->second;
  }

  // если элемент не найден,
  // вставить новый элемент с ключом `key` и значением по умолчанию
  auto [new_it, inserted] = this->tree_.insertUnique({key, mapped_type{}});
  return new_it->second;
}

// Map Iterators
/**
 * @brief Returns an iterator to the beginning.
 * @return Iterator to the beginning.
 */
template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::begin() noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns an iterator to the end.
 * @return Iterator to the end.
 */
template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::end() noexcept {
  return this->tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning.
 * @return Const iterator to the beginning.
 */
template <typename Key, typename Value>
typename Map<Key, Value>::const_iterator
Map<Key, Value>::begin() const noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns a const iterator to the end.
 * @return Const iterator to the end.
 */
template <typename Key, typename Value>
typename Map<Key, Value>::const_iterator Map<Key, Value>::end() const noexcept {
  return this->tree_.end();
}

// Map Capacity
/**
 * @brief Checks whether the container is empty.
 * @return True if the container is empty, false otherwise.
 */
template <typename Key, typename Value>
bool Map<Key, Value>::empty() const noexcept {
  return this->tree_.empty();
}

/**
 * @brief Returns the number of elements.
 * @return The number of elements.
 */
template <typename Key, typename Value>
size_t Map<Key, Value>::size() const noexcept {
  return this->tree_.size();
}

/**
 * @brief Returns the maximum possible number of elements.
 * @return The maximum possible number of elements.
 */
template <typename Key, typename Value>
size_t Map<Key, Value>::max_size() const noexcept {
  return this->tree_.max_size();
}

// Map Modifiers
/**
 * @brief Clears the contents.
 */
template <typename Key, typename Value> void Map<Key, Value>::clear() noexcept {
  return this->tree_.clear();
}

/**
 * @brief Inserts elements.
 * @param value Value to insert.
 * @return Pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool>
Map<Key, Value>::insert(const value_type &value) {
  return this->tree_.insertUnique(value);
}

/**
 * @brief Inserts elements or assigns if the key already exists.
 * @param key Key of the element to insert.
 * @param obj Value to insert or assign.
 * @return Pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool>
Map<Key, Value>::insert_or_assign(const key_type &key, const mapped_type &obj) {
  auto it = this->find(key);
  if (it != this->end()) {
    it->second = obj;
    return {it, false};
  } else {
    return this->tree_.insertUnique({key, obj});
  }
}

/**
 * @brief Inserts multiple elements into the map.
 * @tparam Args The types of the elements to insert.
 * @param args The elements to insert.
 * @return A vector of pairs, where each pair contains an iterator to the
 * inserted element and a boolean indicating success.
 */
template <typename Key, typename Value>
template <typename... Args>
std::vector<std::pair<typename Map<Key, Value>::iterator, bool>>
Map<Key, Value>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

/**
 * @brief Erases an element.
 * @param pos Iterator to the element to erase.
 */
template <typename Key, typename Value>
void Map<Key, Value>::erase(iterator pos) noexcept {
  this->tree_.erase(pos);
}

/**
 * @brief Swaps the contents.
 * @param other Map to swap with.
 */
template <typename Key, typename Value>
void Map<Key, Value>::swap(Map &other) noexcept {
  std::swap(this->tree_, other.tree_);
}

/**
 * @brief Merges elements from another map.
 * @param other Map to merge from.
 */
template <typename Key, typename Value>
void Map<Key, Value>::merge(Map &other) {
  this->tree_.mergeUnique(other.tree_);
}

/**
 * @brief Checks if the container contains an element with a specific key.
 * @param key Key of the element to search for.
 * @return True if the container contains an element with the key, false
 * otherwise.
 */
template <typename Key, typename Value>
bool Map<Key, Value>::contains(const Key &key) const {
  return find(key) != end();
  // return this->tree_.contains(key);
}

/**
 * @brief Inserts a new element constructed in-place.
 * @param key Key of the element to insert.
 * @param value Value of the element to insert.
 * @return Pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename Key, typename Value>
std::pair<typename Map<Key, Value>::iterator, bool>
Map<Key, Value>::emplace(Key &&key, Value &&value) {
  value_type new_value(std::forward<Key>(key), std::forward<Value>(value));
  return tree_.insertUnique(new_value);
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Iterator to the element if found, otherwise end().
 */
template <typename Key, typename Value>
typename Map<Key, Value>::iterator Map<Key, Value>::find(const Key &key) {
  return this->tree_.find({key, mapped_type{}});
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Const iterator to the element if found, otherwise end().
 */
template <typename Key, typename Value>
typename Map<Key, Value>::const_iterator
Map<Key, Value>::find(const Key &key) const {
  return this->tree_.find({key, mapped_type{}});
}

/******************************************************************************
 * DEBUGGING METHODS
 ******************************************************************************/

/**
 * @brief Prints the map structure for debugging purposes.
 */
template <typename Key, typename Value> void Map<Key, Value>::drawMap() const {
  auto printMapNode =
      [&](const typename s21::RBTree<value_type, MapComparator>::Node *node,
          int depth) {
        std::string color = (node->red_) ? "R" : "B";
        int black_height = tree_.blackHeight(node);
        std::cout << std::string(depth * 4, ' ') << "[" << color
                  << (!node->red_ ? std::to_string(black_height + 1) : "")
                  << "]"
                  << "{" << node->key_.first << ", " << node->key_.second << "}"
                  << std::endl;
      };

  tree_.printMap(tree_.getRoot(), 0, printMapNode);
}

} // namespace s21
