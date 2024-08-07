// Copyright 2024 Dmitrii Khramtsov

/**
 * @file set.tpp
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

namespace s21 {

/******************************************************************************
 * CONSTRUCTOR & DESTRUCTOR
 ******************************************************************************/

/**
 * @brief Default constructor.
 */
template <typename Key> Set<Key>::Set() : tree_() {}

/**
 * @brief Constructor with initializer list.
 * @param items Initializer list of value_type.
 */
template <typename Key>
Set<Key>::Set(std::initializer_list<value_type> const &items) : tree_() {
  for (auto item : items) {
    this->tree_.insertUnique(item);
  }
}

/**
 * @brief Copy constructor.
 * @param s Set to copy.
 */
template <typename Key> Set<Key>::Set(const Set &s) : tree_(s.tree_) {}

/**
 * @brief Move constructor.
 * @param s Set to move.
 */
template <typename Key>
Set<Key>::Set(Set &&s) noexcept : tree_(std::move(s.tree_)) {}

/**
 * @brief Destructor.
 */
template <typename Key>
Set<Key>::~Set() =
    default; // tree_ сам себя очистит, у него есть свой деструктор

/**
 * @brief Copy assignment operator.
 * @param s Set to copy.
 * @return Reference to this Set.
 */
template <typename Key> Set<Key> &Set<Key>::operator=(const Set &s) {
  this->tree_ = s.tree_;
  return *this;
}

/**
 * @brief Move assignment operator.
 * @param s Set to move.
 * @return Reference to this Set.
 */
template <typename Key> Set<Key> &Set<Key>::operator=(Set &&s) noexcept {
  this->tree_ = std::move(s.tree_);
  return *this;
}

/******************************************************************************
 * MAIN METHODS
 ******************************************************************************/

// Set Iterators
/**
 * @brief Returns an iterator to the beginning.
 * @return Iterator to the beginning.
 */
template <typename Key> typename Set<Key>::iterator Set<Key>::begin() noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns an iterator to the end.
 * @return Iterator to the end.
 */
template <typename Key> typename Set<Key>::iterator Set<Key>::end() noexcept {
  return this->tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning.
 * @return Const iterator to the beginning.
 */
template <typename Key>
typename Set<Key>::const_iterator Set<Key>::begin() const noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns a const iterator to the end.
 * @return Const iterator to the end.
 */
template <typename Key>
typename Set<Key>::const_iterator Set<Key>::end() const noexcept {
  return this->tree_.end();
}

// Set Capacity
/**
 * @brief Checks whether the container is empty.
 * @return True if the container is empty, false otherwise.
 */
template <typename Key> bool Set<Key>::empty() const noexcept {
  return this->tree_.empty();
}

/**
 * @brief Returns the number of elements.
 * @return The number of elements.
 */
template <typename Key> size_t Set<Key>::size() const noexcept {
  return this->tree_.size();
}

/**
 * @brief Returns the maximum possible number of elements.
 * @return The maximum possible number of elements.
 */
template <typename Key> size_t Set<Key>::max_size() const noexcept {
  return this->tree_.max_size();
}

// Set Modifiers
/**
 * @brief Clears the contents.
 */
template <typename Key> void Set<Key>::clear() noexcept { this->tree_.clear(); }

/**
 * @brief Inserts elements.
 * @param value Value to insert.
 * @return Pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename Key>
std::pair<typename Set<Key>::iterator, bool>
Set<Key>::insert(const value_type &value) {
  return this->tree_.insertUnique(value);
}

/**
 * @brief Inserts multiple elements into the set.
 * @tparam Args The types of the elements to insert.
 * @param args The elements to insert.
 * @return A vector of pairs, where each pair contains an iterator to the
 * inserted element and a boolean indicating success.
 */
template <typename Key>
template <typename... Args>
std::vector<std::pair<typename Set<Key>::iterator, bool>>
Set<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

/**
 * @brief Erases an element.
 * @param pos Iterator to the element to erase.
 */
template <typename Key> void Set<Key>::erase(iterator pos) noexcept {
  this->tree_.erase(pos);
}

/**
 * @brief Swaps the contents.
 * @param other Set to swap with.
 */
template <typename Key> void Set<Key>::swap(Set &other) noexcept {
  std::swap(this->tree_, other.tree_);
}

/**
 * @brief Merges elements from another set.
 * @param other Set to merge from.
 */
template <typename Key> void Set<Key>::merge(Set &other) {
  this->tree_.mergeUnique(other.tree_);
}

/**
 * @brief Checks if the container contains an element with a specific key.
 * @param key Key of the element to search for.
 * @return True if the container contains an element with the key, false
 * otherwise.
 */
template <typename Key> bool Set<Key>::contains(const Key &key) const {
  return this->tree_.contains(key);
}

/**
 * @brief Inserts a new element constructed in-place.
 * @param key Key of the element to insert.
 * @return Pair consisting of an iterator to the inserted element (or to the
 * element that prevented the insertion) and a bool denoting whether the
 * insertion took place.
 */
template <typename Key>
std::pair<typename Set<Key>::iterator, bool> Set<Key>::emplace(Key &&key) {
  value_type new_value(std::forward<Key>(key));
  return tree_.insertUnique(new_value);
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Iterator to the element if found, otherwise end().
 */
template <typename Key>
typename Set<Key>::iterator Set<Key>::find(const Key &key) {
  return this->tree_.find(key);
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Const iterator to the element if found, otherwise end().
 */
template <typename Key>
typename Set<Key>::const_iterator Set<Key>::find(const Key &key) const {
  return this->tree_.find(key);
}

/******************************************************************************
 * DEBUGGING METHODS
 ******************************************************************************/

/**
 * @brief Prints the set structure for debugging purposes.
 */
template <typename Key> void Set<Key>::drawSet() { tree_.drawTree(); }

} // namespace s21
