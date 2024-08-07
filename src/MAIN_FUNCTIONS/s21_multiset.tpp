// Copyright 2024 Dmitrii Khramtsov

/**
 * @file multiset.tpp
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

namespace s21 {

/**
 * @brief Default constructor.
 */
template <typename Key> MultiSet<Key>::MultiSet() : tree_() {}

/**
 * @brief Constructor with initializer list.
 * @param items Initializer list of value_type.
 */
template <typename Key>
MultiSet<Key>::MultiSet(std::initializer_list<value_type> const &items)
    : tree_() {
  for (auto item : items) {
    this->tree_.insert(item);
  }
}

/**
 * @brief Copy constructor.
 * @param s MultiSet to copy.
 */
template <typename Key>
MultiSet<Key>::MultiSet(const MultiSet &s) : tree_(s.tree_) {}

/**
 * @brief Move constructor.
 * @param s MultiSet to move.
 */
template <typename Key>
MultiSet<Key>::MultiSet(MultiSet &&s) noexcept : tree_(std::move(s.tree_)) {}

/**
 * @brief Destructor.
 */
template <typename Key>
MultiSet<Key>::~MultiSet() =
    default; // tree_ сам себя очистит, у него есть свой деструктор

/**
 * @brief Copy assignment operator.
 * @param s MultiSet to copy.
 * @return Reference to this MultiSet.
 */
template <typename Key>
MultiSet<Key> &MultiSet<Key>::operator=(const MultiSet &s) {
  this->tree_ = s.tree_;
  return *this;
}

/**
 * @brief Move assignment operator.
 * @param s MultiSet to move.
 * @return Reference to this MultiSet.
 */
template <typename Key>
MultiSet<Key> &MultiSet<Key>::operator=(MultiSet &&s) noexcept {
  this->tree_ = std::move(s.tree_);
  return *this;
}

/******************************************************************************
 * MAIN METHODS
 ******************************************************************************/

// MultiSet Iterators
/**
 * @brief Returns an iterator to the beginning.
 * @return Iterator to the beginning.
 */
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::begin() noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns an iterator to the end.
 * @return Iterator to the end.
 */
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::end() noexcept {
  return this->tree_.end();
}

/**
 * @brief Returns a const iterator to the beginning.
 * @return Const iterator to the beginning.
 */
template <typename Key>
typename MultiSet<Key>::const_iterator MultiSet<Key>::begin() const noexcept {
  return this->tree_.begin();
}

/**
 * @brief Returns a const iterator to the end.
 * @return Const iterator to the end.
 */
template <typename Key>
typename MultiSet<Key>::const_iterator MultiSet<Key>::end() const noexcept {
  return this->tree_.end();
}

// MultiSet Capacity
/**
 * @brief Checks whether the container is empty.
 * @return True if the container is empty, false otherwise.
 */
template <typename Key> bool MultiSet<Key>::empty() const noexcept {
  return this->tree_.empty();
}

/**
 * @brief Returns the number of elements.
 * @return The number of elements.
 */
template <typename Key> size_t MultiSet<Key>::size() const noexcept {
  return this->tree_.size();
}

/**
 * @brief Returns the maximum possible number of elements.
 * @return The maximum possible number of elements.
 */
template <typename Key> size_t MultiSet<Key>::max_size() const noexcept {
  return this->tree_.max_size();
}

// MultiSet Modifiers
/**
 * @brief Clears the contents.
 */
template <typename Key> void MultiSet<Key>::clear() noexcept {
  this->tree_.clear();
}

/**
 * @brief Inserts elements.
 * @param value Value to insert.
 * @return Iterator to the inserted element.
 */
template <typename Key>
typename MultiSet<Key>::iterator
MultiSet<Key>::insert(const value_type &value) {
  return this->tree_.insert(value).first;
}

/**
 * @brief Inserts multiple elements into the multiset.
 * @tparam Args The types of the elements to insert.
 * @param args The elements to insert.
 * @return A vector of iterators to the inserted elements.
 */
template <typename Key>
template <typename... Args>
std::vector<typename MultiSet<Key>::iterator>
MultiSet<Key>::insert_many(Args &&...args) {
  std::vector<iterator> results;
  (results.push_back(this->insert(std::forward<Args>(args))), ...);
  return results;
}

/**
 * @brief Erases an element.
 * @param pos Iterator to the element to erase.
 */
template <typename Key> void MultiSet<Key>::erase(iterator pos) noexcept {
  this->tree_.erase(pos);
}

/**
 * @brief Swaps the contents.
 * @param other MultiSet to swap with.
 */
template <typename Key> void MultiSet<Key>::swap(MultiSet &other) noexcept {
  std::swap(this->tree_, other.tree_);
}

/**
 * @brief Merges elements from another multiset.
 * @param other MultiSet to merge from.
 */
template <typename Key> void MultiSet<Key>::merge(MultiSet &other) {
  this->tree_.merge(other.tree_);
}

/**
 * @brief Returns the number of elements with a specific key.
 * @param key Key of the element to count.
 * @return The number of elements with the key.
 */
template <typename Key>
size_t MultiSet<Key>::count(const Key &key) const noexcept {
  return this->tree_.count(key);
}

/**
 * @brief Inserts a new element constructed in-place.
 * @param key Key of the element to insert.
 * @return Iterator to the inserted element.
 */
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::emplace(Key &&key) {
  value_type new_value(std::forward<Key>(key));
  return tree_.insert(new_value).first;
}

/**
 * @brief Returns a range containing all elements with the given key.
 * @param key Key of the elements to find.
 * @return Pair of iterators to the lower and upper bounds of the range.
 */
template <typename Key>
std::pair<typename MultiSet<Key>::iterator, typename MultiSet<Key>::iterator>
MultiSet<Key>::equal_range(const key_type &key) {
  return {lower_bound(key), upper_bound(key)};
}

/**
 * @brief Returns a range containing all elements with the given key.
 * @param key Key of the elements to find.
 * @return Pair of const iterators to the lower and upper bounds of the range.
 */
template <typename Key>
std::pair<typename MultiSet<Key>::const_iterator,
          typename MultiSet<Key>::const_iterator>
MultiSet<Key>::equal_range(const key_type &key) const {
  return {lower_bound(key), upper_bound(key)};
}

/**
 * @brief Returns an iterator to the first element not less than the given key.
 * @param key Key to compare.
 * @return Iterator to the first element not less than the key.
 */
template <typename Key>
typename MultiSet<Key>::iterator
MultiSet<Key>::lower_bound(const Key &key) noexcept {
  return this->tree_.lower_bound(key);
}

/**
 * @brief Returns an iterator to the first element greater than the given key.
 * @param key Key to compare.
 * @return Iterator to the first element greater than the key.
 */
template <typename Key>
typename MultiSet<Key>::iterator
MultiSet<Key>::upper_bound(const Key &key) noexcept {
  return this->tree_.upper_bound(key);
}

/**
 * @brief Returns a const iterator to the first element not less than the given
 * key.
 * @param key Key to compare.
 * @return Const iterator to the first element not less than the key.
 */
template <typename Key>
typename MultiSet<Key>::const_iterator
MultiSet<Key>::lower_bound(const Key &key) const noexcept {
  return this->tree_.lower_bound(key);
}

/**
 * @brief Returns a const iterator to the first element greater than the given
 * key.
 * @param key Key to compare.
 * @return Const iterator to the first element greater than the key.
 */
template <typename Key>
typename MultiSet<Key>::const_iterator
MultiSet<Key>::upper_bound(const Key &key) const noexcept {
  return this->tree_.upper_bound(key);
}

/**
 * @brief Checks if the container contains an element with a specific key.
 * @param key Key of the element to search for.
 * @return True if the container contains an element with the key, false
 * otherwise.
 */
template <typename Key> bool MultiSet<Key>::contains(const Key &key) const {
  return this->tree_.contains(key);
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Iterator to the element if found, otherwise end().
 */
template <typename Key>
typename MultiSet<Key>::iterator MultiSet<Key>::find(const Key &key) {
  return this->tree_.find(key);
}

/**
 * @brief Finds an element with a specific key.
 * @param key Key of the element to find.
 * @return Const iterator to the element if found, otherwise end().
 */
template <typename Key>
typename MultiSet<Key>::const_iterator
MultiSet<Key>::find(const Key &key) const {
  return this->tree_.find(key);
}

/******************************************************************************
 * DEBUGGING METHODS
 ******************************************************************************/

/**
 * @brief Prints the multiset structure for debugging purposes.
 */
template <typename Key> void MultiSet<Key>::drawMultiSet() { tree_.drawTree(); }

} // namespace s21
