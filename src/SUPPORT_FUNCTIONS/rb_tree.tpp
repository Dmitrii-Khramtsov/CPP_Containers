// Copyright 2024 Dmitrii Khramtsov

/**
 * @file rb_tree.tpp
 *
 * @author Dmitrii Khramtsov (lonmouth@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-21
 *
 * @copyright School-21 (c) 2024
 */

namespace s21 {

/******************************************************************************
 * CONSTRUCTOR & DESTRUCTOR
 ******************************************************************************/

/**
 * The default constructor for the RBTree class.
 *
 * @param N/A
 *
 * @return N/A
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator>::RBTree()
    : root_(nullptr), size_(0), comparator_(Comparator()) {
  fake_node_.left_ = nullptr; // sentinel node
  fake_node_.right_ = nullptr;
  fake_node_.parent_ = nullptr;
  fake_node_.red_ = false;
}

/**
 * Initializer list constructor.
 *
 * @brief initializer list constructor,
 * creates the RBTree initialized using std::initializer_list
 *
 * @param items List of lists of value_type
 * for initializing the RBTree
 *
 * @throws None
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator>::RBTree(std::initializer_list<node_type> const &items)
    : RBTree() {
  for (const auto &item : items) {
    insert(item);
  }
}

/**
 * @brief Constructor for creating a copy of the RBTree object.
 *
 * @param other RBTree object to be copied
 *
 * @return N/A
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator>::RBTree(const RBTree &other) : RBTree() {
  for (const auto item : other) {
    insert(item);
  }
}

/**
 * @brief Constructor for moving RBTree object.
 *
 * @param other RBTree object to be moved
 *
 * @return N/A
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator>::RBTree(RBTree &&other) noexcept
    : root_(other.root_), fake_node_(), size_(other.size_),
      comparator_(other.comparator_) {
  other.root_ = nullptr;
  other.fake_node_ = BaseNode();
  other.size_ = 0;
  other.comparator_ = Comparator();
}

/**
 * @brief Destructor.
 *
 * @param N/A
 *
 * @return N/A
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator>::~RBTree() noexcept {
  clear();
}

/**
 * @brief Copy assignment operator.
 *
 * @param other RBTree object to be copy
 *
 * @return *this
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator> &
RBTree<Key, Comparator>::operator=(const RBTree<Key, Comparator> &other) {
  if (this != &other) {
    deleteSubtree(root_);
    root_ = CopyTree(other.root_, reinterpret_cast<Node &>(fake_node_));
    fake_node_.red_ = false;
    comparator_ = other.comparator_;
  }
  return *this;
}

/**
 * @brief Assignment operator overload for moving object.
 *
 * @param other RBTree object to be moved
 *
 * @return *this
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTree<Key, Comparator> &
RBTree<Key, Comparator>::operator=(RBTree<Key, Comparator> &&other) noexcept {
  if (this != &other) {
    deleteSubtree(root_);
    root_ = other.root_;
    fake_node_ = other.fake_node_;
    size_ = other.size_;
    comparator_ = other.comparator_;
    other.root_ = nullptr;
    other.fake_node_ = BaseNode();
    other.size_ = 0;
    other.comparator_ = Comparator();
  }
  return *this;
}

/******************************************************************************
 * MAIN METHODS
 ******************************************************************************/

/**
 * @brief Returns the number of elements in the RBTree.
 *
 * @return size_type The number of elements in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::size_type
RBTree<Key, Comparator>::size() const noexcept {
  return size_;
}

/**
 * @brief Returns the maximum possible number of elements.
 *
 * @return size_t The maximum possible number of elements.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
size_t RBTree<Key, Comparator>::max_size() const {
  return static_cast<size_type>(-1);
}

/**
 * @brief Counts the number of occurrences of a specific key in the Red-Black
 * Tree.
 *
 * This function iteratively traverses the Red-Black Tree to count the number of
 * nodes that have the specified key. It uses a stack to avoid recursion.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param key The key to search for in the tree.
 * @param node The root node of the tree or subtree to search.
 * @param count A reference to a variable that will store the count of
 * occurrences.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. If the tree is empty, the count will remain
 * unchanged.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::countUniqueKey(const Key &key, Node *node,
                                             size_type &count) const noexcept {
  if (!node) {
    return;
  }

  std::stack<Node *> stack;
  stack.push(node);

  while (!stack.empty()) {
    Node *current = stack.top();
    stack.pop();

    if (key == current->key_) {
      count++;
    }

    if (current->right_) {
      stack.push(reinterpret_cast<Node *>(current->right_));
    }

    if (current->left_) {
      stack.push(reinterpret_cast<Node *>(current->left_));
    }
  }
}

/**
 * @brief Returns the number of elements with the specified key.
 *
 * @param key The key to count.
 *
 * @return size_t The number of elements with the specified key.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
size_t RBTree<Key, Comparator>::count(
    const Key &key) const noexcept { // возвращает количество элементов,
                                     // соответствующих заданному ключу
  Node *current = root_;
  size_t count = 0;

  countUniqueKey(key, current, count);

  return count;
}

/**
 * @brief Clears all nodes in the tree and frees memory.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::clear() { // очищает все узлы дерева
                                        // и освобождает память
  deleteSubtree(root_);
  root_ = nullptr;
  size_ = 0;
}

/**
 * @brief Swaps the contents of two RBTree objects.
 *
 * @param other The RBTree object to swap with.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::swap(
    RBTree &other) noexcept { // метод обмена содержимым двух деревьев
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(this->fake_node_, other.fake_node_);
  std::swap(comparator_, other.comparator_);
}

/**
 * @brief Merges the contents of another RBTree into this RBTree.
 *
 * @param other The RBTree to merge into this RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::merge(RBTree &other) noexcept {
  if (!other.empty() && this != &other) {
    for (const auto &item : other) {
      insert(item);
    }
    other.clear();
  } // for (auto it = other.cbegin() : it != other.cend(); ++it) {insert(*it);}
}

/**
 * @brief Merges the contents of another RBTree into this RBTree, ensuring
 * unique keys.
 *
 * @param other The RBTree to merge into this RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::mergeUnique(RBTree &other) noexcept {
  if (!other.empty() && this != &other) {
    for (const auto &item : other) {
      insertUnique(item);
    }
    other.clear();
  }
}

/**
 * @brief Checks if the RBTree is empty.
 *
 * @return bool True if the RBTree is empty, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::empty() const {
  return size_ == 0;
}

/**
 * @brief Checks if the RBTree contains the specified key.
 *
 * @param key The key to check.
 *
 * @return bool True if the key is found, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::contains(
    const key_type &key) const { // проверка присутствия ключа в дереве
  return findNode(key) != nullptr;
}

/**
 * @brief Finds an iterator to the element with the specified key.
 *
 * @param key The key to find.
 *
 * @return iterator An iterator to the element with the specified key, or end()
 * if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::iterator
RBTree<Key, Comparator>::find(const_reference key) {
  Node *node = findNode(key);
  if (node == nullptr) {
    return end();
  }
  return iterator(*this, node);
}

template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::find(const_reference key) const {
  Node *node = findNode(key);
  if (node == nullptr) {
    return end();
  }
  return iterator(*this, node);
}

/**
 * @brief Finds an iterator to the first element with a key greater than or
 * equal to the specified key.
 *
 * @param key The key to find.
 *
 * @return iterator An iterator to the first element with a key greater than or
 * equal to the specified key.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::iterator RBTree<Key, Comparator>::lower_bound(
    const Key &key) { // используется для поиска первого элемента с ключом,
                      // большим или равным данному
  Node *current = root_;
  Node *result = nullptr;

  while (current != nullptr) {
    if (comparator_(current->key_, key)) {
      current = reinterpret_cast<Node *>(current->right_);
    } else {
      result = current;
      current = reinterpret_cast<Node *>(current->left_);
    }
  }

  return iterator(*this, result);
}

/**
 * @brief Finds a const_iterator to the first element with a key greater than or
 * equal to the specified key.
 *
 * @param key The key to find.
 *
 * @return const_iterator A const_iterator to the first element with a key
 * greater than or equal to the specified key.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::lower_bound(const Key &key) const {
  Node *current = root_;
  Node *result = nullptr;

  while (current != nullptr) {
    if (comparator_(current->key_, key)) {
      current = reinterpret_cast<Node *>(current->right_);
    } else {
      result = current;
      current = reinterpret_cast<Node *>(current->left_);
    }
  }

  return const_iterator(*this, result);
}

/**
 * @brief Finds an iterator to the first element with a key greater than the
 * specified key.
 *
 * @param key The key to find.
 *
 * @return iterator An iterator to the first element with a key greater than the
 * specified key.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::iterator
RBTree<Key, Comparator>::upper_bound(const Key &key) {
  Node *current = root_;
  Node *result = nullptr;

  while (current != nullptr) {
    if (comparator_(key, current->key_)) {
      current = reinterpret_cast<Node *>(current->left_);
    } else {
      result = current;
      current = reinterpret_cast<Node *>(current->right_);
    }
  }

  return iterator(*this, result);
}

/**
 * @brief Finds a const_iterator to the first element with a key greater than
 * the specified key.
 *
 * @param key The key to find.
 *
 * @return const_iterator A const_iterator to the first element with a key
 * greater than the specified key.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::upper_bound(const Key &key) const {
  Node *current = root_;
  Node *result = nullptr;

  while (current != nullptr) {
    if (comparator_(key, current->key_)) {
      current = reinterpret_cast<Node *>(current->left_);
    } else {
      result = current;
      current = reinterpret_cast<Node *>(current->right_);
    }
  }

  return const_iterator(*this, result);
}

/**
 * @brief Gets the node with the minimum key in the subtree rooted at the
 * specified node.
 *
 * @param node The root of the subtree.
 *
 * @return Node* The node with the minimum key in the subtree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::getMinNode(Node *node) const {
  return findMinNode(node);
}

/**
 * @brief Gets the node with the maximum key in the subtree rooted at the
 * specified node.
 *
 * @param node The root of the subtree.
 *
 * @return Node* The node with the maximum key in the subtree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::getMaxNode(Node *node) const {
  return findMaxNode(node);
}

/**
 * @brief Gets the root node of the RBTree.
 *
 * @return const Node* The root node of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
const typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::getRoot() const {
  return root_;
}

/**
 * @brief Gets an iterator to the first element in the RBTree.
 *
 * @return iterator An iterator to the first element in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTreeIterator<Key, Comparator> RBTree<Key, Comparator>::begin() noexcept {
  Node *min = findMinNode(root_);
  return iterator(*this, min);
}

/**
 * @brief Gets an iterator to the end of the RBTree.
 *
 * @return iterator An iterator to the end of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
RBTreeIterator<Key, Comparator> RBTree<Key, Comparator>::end() noexcept {
  return iterator(*this, nullptr);
}

/**
 * @brief Gets a const_iterator to the first element in the RBTree.
 *
 * @return const_iterator A const_iterator to the first element in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::begin() const noexcept {
  return const_iterator(*this, getMinNode(root_));
}

/**
 * @brief Gets a const_iterator to the end of the RBTree.
 *
 * @return const_iterator A const_iterator to the end of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::end() const noexcept {
  return const_iterator(*this, nullptr);
}

/**
 * @brief Gets a const_iterator to the first element in the RBTree.
 *
 * @return const_iterator A const_iterator to the first element in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::cbegin() const noexcept {
  return const_iterator(*this, findMinNode(root_));
}

/**
 * @brief Gets a const_iterator to the end of the RBTree.
 *
 * @return const_iterator A const_iterator to the end of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::const_iterator
RBTree<Key, Comparator>::cend() const noexcept {
  return const_iterator(*this, nullptr);
}

/**
 * @brief Inserts a new element with the specified key into the RBTree.
 *
 * @param key The key of the element to insert.
 *
 * @return std::pair<iterator, bool> A pair consisting of an iterator to the
 * inserted element (or to the element that prevented the insertion) and a bool
 * denoting whether the insertion took place.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
std::pair<typename RBTree<Key, Comparator>::iterator, bool>
RBTree<Key, Comparator>::insert(const key_type &key) {
  return insert(key, false);
}

/**
 * @brief Inserts a new element with the specified key into the RBTree, ensuring
 * unique keys.
 *
 * @param key The key of the element to insert.
 *
 * @return std::pair<iterator, bool> A pair consisting of an iterator to the
 * inserted element (or to the element that prevented the insertion) and a bool
 * denoting whether the insertion took place.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
std::pair<typename RBTree<Key, Comparator>::iterator, bool>
RBTree<Key, Comparator>::insertUnique(const key_type &key) {
  return insert(key, true);
}

/**
 * @brief Erases a node from the Red-Black Tree.
 *
 * This function erases the node pointed to by the given iterator from the
 * Red-Black Tree. It handles the rebalancing of the tree after the node is
 * removed and ensures that the Red-Black Tree properties are maintained.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param pos An iterator pointing to the node to be erased.
 *
 * @note This function assumes that the tree is not empty and that the
 *       iterator is valid. The caller is responsible for ensuring that
 *       the iterator is valid.
 *
 * @warning This function does not handle the case where the tree is empty or
 * the iterator is invalid. The caller is responsible for ensuring that the tree
 * is not empty and the iterator is valid.
 *
 * @see RBTree
 * @see eraseNode
 * @see eraseFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::erase(iterator pos) {
  Node *eraised_node = pos.getCurrentNode();
  if (!eraised_node) {
    return;
  }

  Node *to_fix = nullptr;
  bool original_color = eraised_node->red_;

  eraseNode(eraised_node, to_fix, &original_color);

  if (!original_color && to_fix) {
    eraseFixup(to_fix);
  }

  delete eraised_node;
  --size_;
}

/******************************************************************************
 * AUXILIARY PRIVATE BASIC METHODS
 ******************************************************************************/

/**
 * @brief Inserts a new node with the given key into the Red-Black Tree.
 *
 * This function inserts a new node with the given key into the Red-Black Tree.
 * If the tree is empty, the new node becomes the root. If the key already
 * exists in the tree and the `unique` flag is set to true, the insertion is
 * aborted. Otherwise, the new node is inserted and the tree is rebalanced.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param key The key to be inserted.
 * @param unique A flag indicating whether the keys should be unique. If set to
 * true, the insertion will be aborted if the key already exists.
 * @return A pair consisting of an iterator to the inserted node and a boolean
 * indicating whether the insertion was successful.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see insertNode
 * @see insertFixup
 */
template <typename Key, typename Comparator>
std::pair<typename RBTree<Key, Comparator>::iterator, bool>
RBTree<Key, Comparator>::insert(const key_type &key, bool unique) {
  Node *new_node = new Node(key);
  if (!root_) {
    root_ = new_node;
    root_->red_ = false; // корень должен быть чёрный
    size_ = 1;
    return {iterator(*this, new_node), true};
  }

  if (findNode(new_node->key_) &&
      unique) { // unique - даёт возможность отключить
                // проверку на уникальный ключ
    delete new_node;
    return {iterator(*this, new_node), false};
  }

  insertNode(root_, new_node);

  insertFixup(new_node);

  // увеличиваем размер дерева
  ++size_;

  return {iterator(*this, new_node), true};
}

/**
 * @brief Deletes all nodes in the subtree starting from the given node.
 *
 * This function iteratively deletes all nodes in the subtree starting from the
 * given node. It uses a stack to avoid recursion and ensures that all nodes are
 * properly deleted and memory is freed.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The root node of the subtree to be deleted.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::deleteSubtree(Node *node) {
  // Итеративно удаляет все узлы в поддереве,
  // начиная с заданного узла.
  // Очищает все узлы дерева и освобождает память.

  if (!node) {
    // Если узел равен nullptr, нет необходимости в удалении
    return;
  }

  std::stack<Node *> stack;
  stack.push(node);

  while (!stack.empty()) {
    Node *current = stack.top();
    stack.pop();

    // Если у текущего узла есть левый потомок, добавляем его в стек
    if (current->left_) {
      stack.push(reinterpret_cast<Node *>(current->left_));
    }

    // Если у текущего узла есть правый потомок, добавляем его в стек
    if (current->right_) {
      stack.push(reinterpret_cast<Node *>(current->right_));
    }

    // Удаляем текущий узел и освобождаем память
    delete current;
  }
}

/**
 * @brief Finds the node with the specified key in the RBTree.
 *
 * @param key The key to find.
 *
 * @return Node* The node with the specified key, or nullptr if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *RBTree<Key, Comparator>::findNode(
    const Key &key) const { // вспомогательный метод для нахождения узла
  Node *current = root_;
  bool flag = false;

  while (current != nullptr) {
    if (comparator_(key, current->key_)) {
      current = reinterpret_cast<Node *>(current->left_);
    } else if (comparator_(current->key_, key)) {
      current = reinterpret_cast<Node *>(current->right_);
    } else {
      flag = true; // ключ найден, прекращаем цикл.
      break;
    }
  }

  return flag ? current : nullptr;
}

/**
 * @brief Finds the node with the minimum key in the subtree rooted at the
 * specified node.
 *
 * @param node The root of the subtree.
 *
 * @return Node* The node with the minimum key in the subtree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *RBTree<Key, Comparator>::findMinNode(
    Node *node) const { // метод находит узел с минимальным значением ключа
                        // в заданном поддереве
  while (node->left_ != nullptr) {
    node = reinterpret_cast<Node *>(node->left_);
  }
  return node;
}

/**
 * @brief Finds the node with the maximum key in the subtree rooted at the
 * specified node.
 *
 * @param node The root of the subtree.
 *
 * @return Node* The node with the maximum key in the subtree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *RBTree<Key, Comparator>::findMaxNode(
    Node *node) const { // метод находит узел с максимальным значением ключа
                        // в заданном поддереве
  while (node->right_ != nullptr) {
    node = reinterpret_cast<Node *>(node->right_);
  }
  return node;
}

/**
 * @brief Copies the subtree rooted at the specified node.
 *
 * @param node The root of the subtree to copy.
 * @param fake_node The fake node to use as the parent of the copied subtree.
 *
 * @return Node* The root of the copied subtree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::CopyTree(Node *node, Node &fake_node) {
  if (node == nullptr) {
    return nullptr;
  }
  Node *new_node = new Node(node->key_);
  new_node->left_ = CopyTree(reinterpret_cast<Node *>(node->left_), fake_node);
  new_node->right_ =
      CopyTree(reinterpret_cast<Node *>(node->right_), fake_node);
  new_node->parent_ = &fake_node;
  new_node->red_ = node->red_;
  return new_node;
}

/******************************************************************************
 * INSERTION & BALANCING
 ******************************************************************************/

/**
 * @brief Inserts a new node into the Red-Black Tree.
 *
 * This function inserts a new node into the Red-Black Tree iteratively,
 * avoiding recursion. It traverses the tree to find the appropriate
 * location for the new node and then inserts it.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param root The root node of the tree.
 * @param new_node The new node to be inserted.
 * @param unique A flag indicating whether the keys should be unique.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. If the tree is empty, the root node should
 *       be set to the new node outside of this function.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for setting the root node to the new
 *          node if the tree is empty.
 *
 * @see RBTree
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::insertNode(Node *root, Node *new_node) {
  Node *current = root;
  Node *parent = nullptr;

  while (current != nullptr) {
    parent = current;
    if (comparator_(new_node->key_, current->key_)) {
      current = reinterpret_cast<Node *>(current->left_);
    } else {
      current = reinterpret_cast<Node *>(current->right_);
    }
  }

  new_node->parent_ = parent;
  if (parent == nullptr) {
    // Если дерево пустое, новый узел становится корнем
    root = new_node;
  } else if (comparator_(new_node->key_, parent->key_)) {
    parent->left_ = new_node;
  } else {
    parent->right_ = new_node;
  }
}

/**
 * @brief Fixes the Red-Black Tree after a node is inserted.
 *
 * This function handles the rebalancing of the Red-Black Tree after a new node
 * is inserted. It checks various conditions and calls the appropriate helper
 * functions to maintain the Red-Black Tree properties.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The node that was inserted.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see redUncleChangeColors
 * @see blackUncleFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::insertFixup(Node *node) {
  if (node == root_)
    return;
  if (node->parent_ == root_)
    return;
  if (!node->parent_->red_)
    return;

  if (redUncle(node)) {
    redUncleChangeColors(node);
  } else {
    blackUncleFixup(node);
  }
}

/**
 * @brief Checks if the left child of the grandparent is the parent and the
 * right child of the parent is the node.
 *
 * @param node The node to check.
 *
 * @return bool True if the condition is met, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::leftDadRightSon(
    Node *node) { // относительно деда папа слева, сын справа
  return node != nullptr && node->parent_ != nullptr &&
                 node->parent_->parent_ != nullptr
             ? node->parent_->right_ == node &&
                   node->parent_->parent_->left_ == node->parent_
             : false;
}

/**
 * @brief Checks if the right child of the grandparent is the parent and the
 * left child of the parent is the node.
 *
 * @param node The node to check.
 *
 * @return bool True if the condition is met, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::rightDadLeftSon(
    Node *node) { // относительно деда папа справа, сын слева
  return node != nullptr && node->parent_ != nullptr &&
                 node->parent_->parent_ != nullptr
             ? node->parent_->left_ == node &&
                   node->parent_->parent_->right_ == node->parent_
             : false;
}

/**
 * @brief Checks if the left child of the grandparent is the parent and the left
 * child of the parent is the node.
 *
 * @param node The node to check.
 *
 * @return bool True if the condition is met, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::leftDadLeftSon(
    Node *node) { // относительно деда папа слева, сын слева
  return node != nullptr && node->parent_ != nullptr &&
                 node->parent_->parent_ != nullptr
             ? node->parent_->left_ == node &&
                   node->parent_->parent_->left_->left_ == node
             : false;
}

/**
 * @brief Checks if the right child of the grandparent is the parent and the
 * right child of the parent is the node.
 *
 * @param node The node to check.
 *
 * @return bool True if the condition is met, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::rightDadRightSon(
    Node *node) { // относительно деда папа справа, сын справа
  return node != nullptr && node->parent_ != nullptr &&
                 node->parent_->parent_ != nullptr
             ? node->parent_->right_ == node &&
                   node->parent_->parent_->right_->right_ == node
             : false;
}

/**
 * @brief Checks if the uncle of the node is red.
 *
 * @param node The node to check.
 *
 * @return bool True if the uncle is red, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::redUncle(
    Node *node) { // метод возвращает цвет дяди
                  // (метод используется если node != root_)
  if (node->parent_->parent_->right_ == nullptr ||
      node->parent_->parent_->left_ == nullptr) {
    return false;
  }

  // если существует дедушка, вызываем цвет узла дяди
  return node->parent_->parent_->right_->right_ == node
             ? node->parent_->parent_->left_->red_
             : node->parent_->parent_->right_->red_;
}

/**
 * @brief Checks if both the node and its parent are red.
 *
 * @param node The node to check.
 *
 * @return bool True if both the node and its parent are red, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::doubleRed(Node *node) {
  return node->red_ && node->parent_->red_;
}

/**
 * @brief Fixes double red violations in the Red-Black Tree.
 *
 * This function iteratively traverses up the tree from the given node to the
 * root, checking for double red violations (two consecutive red nodes). If a
 * double red violation is found, it calls the `insertFixup` method to correct
 * the violation.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The starting node from which to begin the traversal.
 *
 * @note This function uses an iterative approach to avoid recursion, which can
 * be more efficient in terms of stack usage, especially for deep trees.
 *
 * @warning This function assumes that the tree is not empty and that the
 *          root node is not null. The caller is responsible for ensuring that
 *          the tree is not empty.
 *
 * @see RBTree
 * @see insertFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::doubleRedFixup(Node *node) {
  // Итерируемся вверх к родителю, к деду, к прадеду до nullptr,
  // если встречаем две красные подряд,
  // тогда относительно первой красной вызываем insertFixup

  Node *current = node;
  while (current && current->parent_) {
    // Проверяем наличие двух красных узлов подряд
    if (doubleRed(current)) {
      // Вызываем insertFixup для исправления ситуации
      insertFixup(current);
    }
    // Переходим к родительскому узлу
    current = reinterpret_cast<Node *>(current->parent_);
  }
}

/**
 * @brief Handles the case where the uncle node is red during insertion in the
 * Red-Black Tree.
 *
 * This function adjusts the colors of the parent, grandparent, and uncle nodes
 * when the uncle node is red during the insertion of a new node. It also
 * handles the case where the grandparent is the root node. If the grandparent
 * is not the root, it calls `doubleRedFixup` to fix any double red violations.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The node being inserted.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see doubleRedFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::redUncleChangeColors(Node *node) {
  /* * * * * * * * * * * * * * * * * *
   *     (B)G              (R)G      *
   *       / \               / \     *
   *   (R)P   U(R)  ==>  (B)P   U(B) *
   *     /                 /         *
   * (R)L              (R)L          *
   * * * * * * * * * * * * * * * * * */

  node->parent_->red_ = false;
  node->parent_->parent_->red_ = true;

  // если дядя слева - перекрашиваем его в чёрный
  if (rightDadRightSon(node) || rightDadLeftSon(node)) {
    node->parent_->parent_->left_->red_ = false;
  }
  // если дядя справа - перекрашиваем его в чёрный
  if (leftDadLeftSon(node) || leftDadRightSon(node)) {
    node->parent_->parent_->right_->red_ = false;
  }

  // если дедушка является корнем, перекрашиваем его в чёрный
  if (root_ == node->parent_->parent_) {
    node->parent_->parent_->red_ = false;
  } else {
    doubleRedFixup(node);
  }
}

/**
 * @brief Fixes the Red-Black Tree when the uncle node is black during
 * insertion.
 *
 * This function handles the case where the uncle node is black during the
 * insertion of a new node. It adjusts the structure of the tree by calling the
 * appropriate helper functions to maintain the Red-Black Tree properties.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The node being inserted.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see oppositeDadAndGrandpa
 * @see sameSideDadAndGrandpa
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::blackUncleFixup(Node *node) {
  Node *parent = reinterpret_cast<Node *>(node->parent_);
  Node *grandparent = reinterpret_cast<Node *>(node->parent_->parent_);

  oppositeDadAndGrandpa(node, parent, grandparent);

  sameSideDadAndGrandpa(node, parent, grandparent);

  root_->red_ = false;
}

/**
 * @brief Performs a left rotation at the specified node.
 *
 * @param node The node to rotate.
 *
 * @throws N/A
 */

template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::leftRotate(Node *node) {
  Node *rightSun = reinterpret_cast<Node *>(node->right_);

  // устанавливаем правого ребенка parent на левого ребенка rightSun
  node->right_ = rightSun->left_;
  if (rightSun->left_) {
    // устанавливаем родителя левого ребенка rightSun на parent.
    rightSun->left_->parent_ = node;
  }
  // устанавливаем родителя rightSun на дедушку (родителя parent)
  rightSun->parent_ = node->parent_;

  if (node->parent_ == nullptr) {
    root_ = rightSun;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = rightSun;
  } else {
    node->parent_->right_ = rightSun;
  }

  // устанавливаем левого ребенка rightSun на parent
  rightSun->left_ = node;
  // устанавливаем родителя parent на rightSun
  node->parent_ = rightSun;
}

/**
 * @brief Performs a right rotation at the specified node.
 *
 * @param node The node to rotate.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::rightRotate(Node *node) { // аналогично leftRotate
  Node *leftSun = reinterpret_cast<Node *>(node->left_);

  node->left_ = leftSun->right_;
  if (leftSun->right_) {
    leftSun->right_->parent_ = node;
  }

  leftSun->parent_ = node->parent_;

  if (node->parent_ == nullptr) {
    root_ = leftSun;
  } else if (node == node->parent_->right_) {
    node->parent_->right_ = leftSun;
  } else {
    node->parent_->left_ = leftSun;
  }

  leftSun->right_ = node;
  node->parent_ = leftSun;
}

/**
 * @brief Handles the case where the parent and grandparent nodes are on
 * opposite sides in the Red-Black Tree.
 *
 * This function adjusts the structure of the tree when the parent and
 * grandparent nodes are on opposite sides. It performs the appropriate
 * rotations to maintain the Red-Black Tree properties during the insertion
 * fix-up process.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node A reference to the node being inserted.
 * @param parent A reference to the parent node of the inserted node.
 * @param grandparent A reference to the grandparent node of the inserted node.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see leftRotate
 * @see rightRotate
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::oppositeDadAndGrandpa(
    Node *&node, Node *&parent,
    Node *&grandparent) { // папа и дед в разных сторонах
  /* * * * * * * * * * * * * * * *
   *   (B)G                 (B)G *
   *     /                    /  *
   * (R)P        ==>      (R)R   *
   *     \                  /    *
   *   (R)R             (R)P     *
   * * * * * * * * * * * * * * * */

  if (leftDadRightSon(node)) {
    node = parent;
    leftRotate(node);
    parent = reinterpret_cast<Node *>(node->parent_);
    grandparent = reinterpret_cast<Node *>(node->parent_->parent_);
  }

  /* * * * * * * * * * * * * * * *
   * (B)G               (B)G     *
   *     \                  \    *
   *   (R)P      ==>      (R)L   *
   *     /                    \  *
   * (R)L                   (R)P *
   * * * * * * * * * * * * * * * */

  if (rightDadLeftSon(node)) {
    node = parent;
    rightRotate(node);
    parent = reinterpret_cast<Node *>(node->parent_);
    grandparent = reinterpret_cast<Node *>(node->parent_->parent_);
  }
}

/**
 * @brief Handles the case where the parent and grandparent nodes are on the
 * same side in the Red-Black Tree.
 *
 * This function adjusts the colors of the parent and grandparent nodes and
 * performs the appropriate rotations when the parent and grandparent nodes are
 * on the same side. This is part of the insertion fix-up process.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node A reference to the node being inserted.
 * @param parent A reference to the parent node of the inserted node.
 * @param grandparent A reference to the grandparent node of the inserted node.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see rightRotate
 * @see leftRotate
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::sameSideDadAndGrandpa(
    Node *&node, Node *&parent,
    Node *&grandparent) { // папа и дед в одной стороне
  /* * * * * * * * * * * * * * * * * * *
   *     (B)G                (R)G      *
   *       /                   / \     *
   *   (R)P       ==>      (B)L   G(B) *
   *     /                             *
   * (R)L                              *
   * * * * * * * * * * * * * * * * * * */

  if (leftDadLeftSon(node)) {
    parent->red_ = false;
    grandparent->red_ = true;
    rightRotate(grandparent);
  }

  /* * * * * * * * * * * * * * * * * * *
   * (B)G                    (R)P      *
   *     \                     / \     *
   *   (R)P       ==>      (B)G   R(B) *
   *       \                           *
   *     (R)R                          *
   * * * * * * * * * * * * * * * * * * */

  if (rightDadRightSon(node)) {
    parent->red_ = false;
    grandparent->red_ = true;
    leftRotate(grandparent);
  }
}

/******************************************************************************
 * ERASE & BALANCE
 ******************************************************************************/

/**
 * @brief Gets the right nephew of the right sibling of the specified node.
 *
 * @param node The node to get the nephew for.
 *
 * @return Node* The right nephew of the right sibling of the specified node, or
 * nullptr if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::rNephewsRS(Node *node) {
  return reinterpret_cast<Node *>(node->right_->right_)
             ? reinterpret_cast<Node *>(node->right_->right_)
             : nullptr;
}

/**
 * @brief Gets the left nephew of the right sibling of the specified node.
 *
 * @param node The node to get the nephew for.
 *
 * @return Node* The left nephew of the right sibling of the specified node, or
 * nullptr if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::lNephewsRS(Node *node) {
  return reinterpret_cast<Node *>(node->right_->left_)
             ? reinterpret_cast<Node *>(node->right_->left_)
             : nullptr;
}

/**
 * @brief Gets the right nephew of the left sibling of the specified node.
 *
 * @param node The node to get the nephew for.
 *
 * @return Node* The right nephew of the left sibling of the specified node, or
 * nullptr if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::rNephewsLS(Node *node) {
  return reinterpret_cast<Node *>(node->left_->right_)
             ? reinterpret_cast<Node *>(node->left_->right_)
             : nullptr;
}

/**
 * @brief Gets the left nephew of the left sibling of the specified node.
 *
 * @param node The node to get the nephew for.
 *
 * @return Node* The left nephew of the left sibling of the specified node, or
 * nullptr if not found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::lNephewsLS(Node *node) {
  return reinterpret_cast<Node *>(node->left_->left_)
             ? reinterpret_cast<Node *>(node->left_->left_)
             : nullptr;
}

/**
 * @brief Gets the right sibling of the specified node.
 *
 * @param node The node to get the sibling for.
 *
 * @return Node* The right sibling of the specified node, or nullptr if not
 * found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::rSibling(Node *node) {
  return reinterpret_cast<Node *>(node->right_)
             ? reinterpret_cast<Node *>(node->right_)
             : nullptr;
}

/**
 * @brief Gets the left sibling of the specified node.
 *
 * @param node The node to get the sibling for.
 *
 * @return Node* The left sibling of the specified node, or nullptr if not
 * found.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTree<Key, Comparator>::Node *
RBTree<Key, Comparator>::lSibling(Node *node) {
  return reinterpret_cast<Node *>(node->left_)
             ? reinterpret_cast<Node *>(node->left_)
             : nullptr;
}

/**
 * @brief Handles the case where the sibling node is red in the Red-Black Tree.
 *
 * This function adjusts the colors of the parent and sibling nodes when the
 * sibling node is red. It then performs a left rotation on the parent node and
 * calls the `eraseFixup` method to continue the rebalancing process.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The parent node where the deletion occurred.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see leftRotate
 * @see eraseFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::redSibling(Node *node) {
  // красный брат (case_4a)
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *    (b)P                    (b)S       *  (P)Parent, (S)sibling,   *
   *      / \                     / \      *  (R)(L) - Nephews,        *
   *    (x)  S(r)      ==>    (r)P   R(b)  *  (any) - любой цвет,      *
   *        / \                 / \        *  (x) - удалённый узел,    *
   *    (b)L   R(b)           (x)  L(b)    *  (b)(r) - цвета           *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  std::swap(rSibling(node)->red_, node->red_);
  leftRotate(node);
  eraseFixup(node);
}

/**
 * @brief Fixes the red-black tree properties when the sibling is red (mirror
 * case).
 *
 * @param node The node to fix.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::mirrorRedSibling(Node *node) {
  // (case_4b)
  std::swap(lSibling(node)->red_, node->red_);
  rightRotate(node);
  eraseFixup(node);
}

/**
 * @brief Handles the case where the right nephew is red and the left nephew is
 * any color in the Red-Black Tree.
 *
 * This function adjusts the colors of the parent, sibling, and right nephew
 * nodes when the right nephew is red and the left nephew is any color. It then
 * performs a left rotation on the parent node.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The parent node where the deletion occurred.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see leftRotate
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::rNephewsRedLNephewsAny(Node *node) {
  // входящая node == Parent (case_3a)
  // правый племянник красный (левый - любой)
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  (any)P                  (any)S       *  (P)Parent, (S)sibling,   *
   *      / \                     / \      *  (R)(L) - Nephews,        *
   *    (x)  S(b)      ==>    (b)P   R(b)  *  (any) - любой цвет,      *
   *        / \                 / \        *  (x) - удалённый узел,    *
   *  (any)L   R(r)           (x)  L(any)  *  (b)(r) - цвета           *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  rSibling(node)->red_ = node->red_;
  rNephewsRS(node)->red_ = false;
  node->red_ = false;
  leftRotate(node);
}

/**
 * @brief Fixes the red-black tree properties when the right nephew is red and
 * the left nephew is any color (mirror case).
 *
 * @param node The node to fix.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::mirrorRNephewsRedLNephewsAny(Node *node) {
  // (case_3b)
  lSibling(node)->red_ = node->red_;
  lNephewsLS(node)->red_ = false;
  node->red_ = false;
  rightRotate(node);
}

/**
 * @brief Handles the case where both nephews are black in the Red-Black Tree.
 *
 * This function adjusts the colors of the parent and sibling nodes when both
 * nephews are black. It then performs an iterative rebalancing starting from
 * the parent node if the deleted node and its parent were both black.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The node where the deletion occurred.
 *
 * @note This function uses an iterative approach to avoid recursion, which can
 * be more efficient in terms of stack usage, especially for deep trees.
 *
 * @warning This function assumes that the tree is not empty and that the
 *          root node is not null. The caller is responsible for ensuring that
 *          the tree is not empty.
 *
 * @see RBTree
 * @see eraseFixup
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::lNephewsBlackRNephewsBlack(Node *node) {
  // оба племянника черные (case_2a)
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  (any)P                    (b)P         *  (P)Parent, (S)sibling,   *
   *      / \                     / \        *  (R)(L) - Nephews,        *
   *    (x)  S(b)      ==>      (x)  S(r)    *  (any) - любой цвет,      *
   *        / \                     / \      *  (x) - удалённый узел,    *
   *    (b)L   R(b)             (b)L   R(b)  *  (b)(r) - цвета           *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  // цвет родителя
  bool color = node->red_;

  // родительскую в черный
  node->red_ = false;

  // брата в красный
  rSibling(node)->red_ = true;

  // если удалённая вершина была чёрной и её родитель также чёрный,
  // начинается итеративная ребалансировка, начиная с родительского узла,
  // как если бы он был изначально удалён (рекурсия медленнее)
  if (!color && node->parent_) {
    Node *parent = reinterpret_cast<Node *>(node->parent_);
    while (parent) {
      eraseFixup(parent);
      parent = reinterpret_cast<Node *>(parent->parent_);
    }
  }
}

/**
 * @brief Fixes the red-black tree properties when both nephews are black
 * (mirror case).
 *
 * @param node The node to fix.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::mirrorLNephewsBlackRNephewsBlack(Node *node) {
  // (case_2b)
  bool color = node->red_;

  node->red_ = false;
  lSibling(node)->red_ = true;

  if (!color && node->parent_) {
    eraseFixup(reinterpret_cast<Node *>(node->parent_));
  }
}

/**
 * @brief Handles the case where the left nephew is red and the right nephew is
 * black in the Red-Black Tree.
 *
 * This function adjusts the colors of the left nephew and sibling nodes when
 * the left nephew is red and the right nephew is black. It then performs a
 * right rotation on the sibling node and continues the rebalancing process by
 * calling the appropriate case handling functions.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The parent node where the deletion occurred.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see rightRotate
 * @see rNephewsRedLNephewsAny
 * @see mirrorRNephewsRedLNephewsAny
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::lNephewsRedRNephewsBlack(Node *node) {
  // левый племянник красный, правый черный (case_1a)
  /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
   *  (any)P                  (any)P           *                           *
   *      / \                     / \          *  (P)Parent, (S)sibling,   *
   *    (x)  S(b)      ==>      (x)  L(b)      *  (R)(L) - Nephews,        *
   *        / \                       \        *  (any) - любой цвет,      *
   *    (r)L   R(b)                    S(r)    *  (x) - удалённый узел,    *
   *                                    \      *  (b)(r) - цвета           *
   *                                     R(b)  *                           *
   * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

  std::swap(lNephewsRS(node)->red_, rSibling(node)->red_);
  rightRotate(rSibling(node));

  // продолжаем балансировку: брат чёрный, племянник красный.
  // Переходим к шагу case_3.
  if (rNRlNA(node)) {
    rNephewsRedLNephewsAny(node);
  } else {
    mirrorRNephewsRedLNephewsAny(node);
  }
}

/**
 * @brief Fixes the red-black tree properties when the left nephew is red and
 * the right nephew is black (mirror case).
 *
 * @param node The node to fix.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::mirrorLNephewsRedRNephewsBlack(Node *node) {
  // зеркальный случай (case_1b)
  std::swap(rNephewsLS(node)->red_, lSibling(node)->red_);
  leftRotate(lSibling(node));

  if (rNRlNA(node)) {
    rNephewsRedLNephewsAny(node);
  } else {
    mirrorRNephewsRedLNephewsAny(node);
  }
}

/**
 * @brief Checks if the sibling is red.
 *
 * @param node The node to check.
 *
 * @return bool True if the sibling is red, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::sR(Node *node) {
  // redSibling (case_4a)
  return node && rSibling(node) && rSibling(node)->red_;
}

/**
 * @brief Checks if the sibling is red (mirror case).
 *
 * @param node The node to check.
 *
 * @return bool True if the sibling is red, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::mirrorSR(Node *node) {
  // redSibling (case_4b)
  return node && lSibling(node) && lSibling(node)->red_;
}

/**
 * @brief Checks if the right nephew is red and the left nephew is any color.
 *
 * @param node The node to check.
 *
 * @return bool True if the right nephew is red and the left nephew is any
 * color, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::rNRlNA(Node *node) {
  // rNephewsRedLNephewsAny (case_3a)
  return node && rSibling(node) && !rSibling(node)->red_ && rNephewsRS(node) &&
         rNephewsRS(node)->red_;
}

/**
 * @brief Checks if the right nephew is red and the left nephew is any color
 * (mirror case).
 *
 * @param node The node to check.
 *
 * @return bool True if the right nephew is red and the left nephew is any
 * color, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::mirrorRNRlNA(Node *node) {
  // rNephewsRedLNephewsAny (case_3b) зеркальный вариант
  return node && lSibling(node) && !lSibling(node)->red_ && lNephewsLS(node) &&
         lNephewsLS(node)->red_;
}

/**
 * @brief Checks if both nephews are black.
 *
 * @param node The node to check.
 *
 * @return bool True if both nephews are black, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::lNBrNB(Node *node) {
  // lNephewsBlackRNephewsBlack (case_2a)
  return node && rSibling(node) && !rSibling(node)->red_ &&
         ((lNephewsRS(node) && !lNephewsRS(node)->red_) || !lNephewsRS(node)) &&
         ((rNephewsRS(node) && !rNephewsRS(node)->red_) || !rNephewsRS(node));
}

/**
 * @brief Checks if both nephews are black (mirror case).
 *
 * @param node The node to check.
 *
 * @return bool True if both nephews are black, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::mirrorLNBrNB(Node *node) {
  // lNephewsBlackRNephewsBlack (case_2b)
  return node && lSibling(node) && !lSibling(node)->red_ &&
         ((lNephewsLS(node) && !lNephewsLS(node)->red_) || !lNephewsLS(node)) &&
         ((rNephewsLS(node) && !rNephewsLS(node)->red_) || !rNephewsLS(node));
}

/**
 * @brief Checks if the left nephew is red and the right nephew is black.
 *
 * @param node The node to check.
 *
 * @return bool True if the left nephew is red and the right nephew is black,
 * false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::lNRrNB(Node *node) {
  // lNephewsRedRNephewsBlack (case_1a)
  return node && rSibling(node) && !rSibling(node)->red_ && lNephewsRS(node) &&
         lNephewsRS(node)->red_ &&
         (!rNephewsRS(node) || (rNephewsRS(node) && !rNephewsRS(node)->red_));
}

/**
 * @brief Checks if the left nephew is red and the right nephew is black (mirror
 * case).
 *
 * @param node The node to check.
 *
 * @return bool True if the left nephew is red and the right nephew is black,
 * false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
bool RBTree<Key, Comparator>::mirrorLNRrNB(Node *node) {
  // lNephewsRedRNephewsBlack (case_1b)
  return node && lSibling(node) && !lSibling(node)->red_ && rNephewsLS(node) &&
         rNephewsLS(node)->red_ &&
         (!lNephewsLS(node) || (lNephewsLS(node) && !lNephewsLS(node)->red_));
}

/**
 * @brief Fixes the Red-Black Tree after a node is deleted.
 *
 * This function handles various cases that can occur after a node is deleted
 * from the Red-Black Tree. It calls the appropriate case handling functions
 * based on the configuration of the sibling and nephew nodes.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param node The node where the deletion occurred.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see lNephewsRedRNephewsBlack
 * @see mirrorLNephewsRedRNephewsBlack
 * @see lNephewsBlackRNephewsBlack
 * @see mirrorLNephewsBlackRNephewsBlack
 * @see rNephewsRedLNephewsAny
 * @see mirrorRNephewsRedLNephewsAny
 * @see redSibling
 * @see mirrorRedSibling
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::eraseFixup(Node *node) {
  if (lNRrNB(node)) {
    lNephewsRedRNephewsBlack(node); // (case_1a)
  } else if (mirrorLNRrNB(node)) {
    mirrorLNephewsRedRNephewsBlack(node); // (case_1b)
  } else if (lNBrNB(node)) {
    lNephewsBlackRNephewsBlack(node); // (case_2a)
  } else if (mirrorLNBrNB(node)) {
    mirrorLNephewsBlackRNephewsBlack(node); // (case_2b)
  } else if (rNRlNA(node)) {
    rNephewsRedLNephewsAny(node); // (case_3a)
  } else if (mirrorRNRlNA(node)) {
    mirrorRNephewsRedLNephewsAny(node); // (case_3b)
  } else if (sR(node)) {
    redSibling(node); // (case_4a)
  } else if (mirrorSR(node)) {
    mirrorRedSibling(node); // (case_4b)
  }
}

/**
 * @brief Swaps the contents of two nodes.
 *
 * @param node_1 The first node to swap.
 * @param node_2 The second node to swap.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::swapNodes(Node *node_1,
                                        Node *node_2) { // меняем местами узлы
  // Если оба узла одинаковые, ничего не делаем
  if (node_1 == node_2)
    return;

  // Обменяем родительские указатели
  Node *tempParent = reinterpret_cast<Node *>(node_1->parent_);
  node_1->parent_ = node_2->parent_;
  node_2->parent_ = reinterpret_cast<Node *>(tempParent);

  // Обновим ссылки у родителей
  if (node_1->parent_) {
    if (node_1->parent_->left_ == reinterpret_cast<Node *>(node_2)) {
      node_1->parent_->left_ = reinterpret_cast<Node *>(node_1);
    } else {
      node_1->parent_->right_ = reinterpret_cast<Node *>(node_1);
    }
  }
  if (node_2->parent_) {
    if (node_2->parent_->left_ == reinterpret_cast<Node *>(node_1)) {
      node_2->parent_->left_ = reinterpret_cast<Node *>(node_2);
    } else {
      node_2->parent_->right_ = reinterpret_cast<Node *>(node_2);
    }
  }

  // Обменяем указатели левого и правого ребенка
  Node *tempLeft = reinterpret_cast<Node *>(node_1->left_);
  node_1->left_ = node_2->left_;
  node_2->left_ = tempLeft;

  Node *tempRight = reinterpret_cast<Node *>(node_1->right_);
  node_1->right_ = node_2->right_;
  node_2->right_ = reinterpret_cast<Node *>(tempRight);

  // Обновим родителей у детей
  if (node_1->left_)
    node_1->left_->parent_ = reinterpret_cast<Node *>(node_1);
  if (node_1->right_)
    node_1->right_->parent_ = reinterpret_cast<Node *>(node_1);
  if (node_2->left_)
    node_2->left_->parent_ = reinterpret_cast<Node *>(node_2);
  if (node_2->right_)
    node_2->right_->parent_ = reinterpret_cast<Node *>(node_2);

  // Обменяем цвета узлов
  bool tempColor = reinterpret_cast<Node *>(node_1->red_);
  node_1->red_ = node_2->red_;
  node_2->red_ = reinterpret_cast<Node *>(tempColor);

  // Если один из узлов был корнем, нужно обновить указатель на корень
  if (root_ == node_1) {
    root_ = node_2;
  } else if (root_ == node_2) {
    root_ = node_1;
  }
}

/**
 * @brief Transplants a node with another node.
 *
 * @param eraised_node The node to be transplanted.
 * @param successor The node to transplant with.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::transplant(
    Node *eraised_node, Node *successor) { // меняем местами родителей
  // если родитель удаляемого узла - корень, предок становится корнем
  if (!eraised_node->parent_) {
    root_ = successor;
    // родитель удаляемого узла будет указывать на предка
  } else if (eraised_node->parent_->right_ == eraised_node) {
    eraised_node->parent_->right_ = successor;
  } else {
    eraised_node->parent_->left_ = successor;
  }
  // предок будет указывать на родителя удаляемого узла
  if (successor) {
    std::swap(eraised_node->parent_, successor->parent_);
  }
}

/**
 * @brief Gets the number of children of the specified node.
 *
 * @param node The node to check.
 *
 * @return char The number of children of the specified node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
char RBTree<Key, Comparator>::howManyChildren(Node *node) {
  char how_many_children = 0;
  if (node->right_ && node->left_) {
    how_many_children = two_children;
  } else if (!node->right_ && !node->left_) {
    how_many_children = no_children;
  } else {
    how_many_children = one_child;
  }

  return how_many_children;
}

/**
 * @brief Handles the case where the node to be erased has no children.
 *
 * @param eraised_node The node to be erased.
 * @param to_fix The node to fix after erasing.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::noChildren(Node *eraised_node, Node *&to_fix) {
  to_fix = eraised_node->red_ ? nullptr
                              : reinterpret_cast<Node *>(eraised_node->parent_);
  transplant(eraised_node, nullptr);
}

/**
 * @brief Handles the case where the node to be erased has one child.
 *
 * @param eraised_node The node to be erased.
 * @param to_fix The node to fix after erasing.
 * @param color The original color of the erased node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::oneChildren(Node *eraised_node, Node *&to_fix,
                                          bool *color) {
  // eraised_node - чёрный, а сын красный
  // (другие варианты не возможны в сбалансированном дереве)
  if (eraised_node->left_ == nullptr) {
    to_fix = reinterpret_cast<Node *>(eraised_node->right_);
    transplant(eraised_node, to_fix);
  } else if (eraised_node->right_ == nullptr) {
    to_fix = reinterpret_cast<Node *>(eraised_node->left_);
    transplant(eraised_node, to_fix);
  }

  // меняем original_color_red на красный, т.к. балансировка не нужна
  *color = to_fix->red_;

  // меняем на чёрный
  to_fix->red_ = eraised_node->red_;
}

/**
 * @brief Handles the case where the node to be erased has two children.
 *
 * @param eraised_node The node to be erased.
 * @param to_fix The node to fix after erasing.
 * @param color The original color of the erased node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::twoChildren(Node *eraised_node, Node *&to_fix,
                                          bool *color) {
  Node *successor = findMinNode(reinterpret_cast<Node *>(eraised_node->right_));
  to_fix = reinterpret_cast<Node *>(successor->right_);
  // цвет удаляемого узла
  *color = to_fix ? to_fix->red_ : successor->red_;

  swapNodes(eraised_node, successor);

  // eraised_node теперь на позиции successor
  // либо 1 ребёнок, либо нет детей
  eraseNode(eraised_node, to_fix, color);
}

/**
 * @brief Erases a node from the Red-Black Tree and fixes the tree properties.
 *
 * This function handles the deletion of a node from the Red-Black Tree based on
 * the number of children the node has. It calls the appropriate helper
 * functions to handle the deletion and fix the tree properties.
 *
 * @tparam Key The type of the keys in the tree.
 * @tparam Comparator The type of the comparator used to compare keys.
 * @param eraised_node The node to be erased.
 * @param to_fix A reference to a pointer to the node that needs to be fixed
 * after the deletion.
 * @param color A pointer to a boolean that indicates the color of the node to
 * be fixed.
 *
 * @note This function assumes that the tree is not empty and that the
 *       root node is not null. The caller is responsible for ensuring that
 *       the tree is not empty.
 *
 * @warning This function does not handle the case where the tree is empty.
 *          The caller is responsible for ensuring that the tree is not empty.
 *
 * @see RBTree
 * @see noChildren
 * @see oneChildren
 * @see twoChildren
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::eraseNode(Node *eraised_node, Node *&to_fix,
                                        bool *color) {
  switch (howManyChildren(eraised_node)) {
  case no_children:
    noChildren(eraised_node, to_fix);
    break;
  case one_child:
    oneChildren(eraised_node, to_fix, color);
    break;
  case two_children:
    twoChildren(eraised_node, to_fix, color);
    break;
  }
}

/******************************************************************************
 * RED BLACK TREE ITERATOR
 ******************************************************************************/

// RBTreeBaseIterator

/**
 * @brief Increments the iterator to the next node in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
void RBTreeBaseIterator<Key, Comparator, IsConst>::increment() {
  if (current_->right_ != nullptr) {
    current_ = tree_.getMinNode(reinterpret_cast<Node *>(current_->right_));
  } else {
    Node *parent = reinterpret_cast<Node *>(current_->parent_);
    while (parent != nullptr && current_ == parent->right_) {
      current_ = parent;
      parent = reinterpret_cast<Node *>(parent->parent_);
    }
    current_ = parent;
  }
}

/**
 * @brief Decrements the iterator to the previous node in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
void RBTreeBaseIterator<Key, Comparator, IsConst>::decrement() {
  if (current_ == nullptr) {
    current_ = tree_.getMaxNode(const_cast<Node *>(tree_.getRoot()));
  } else if (current_->left_ != nullptr) {
    current_ = tree_.getMaxNode(reinterpret_cast<Node *>(current_->left_));
  } else {
    Node *parent = reinterpret_cast<Node *>(current_->parent_);
    while (parent != nullptr && current_ == parent->left_) {
      current_ = parent;
      parent = reinterpret_cast<Node *>(parent->parent_);
    }
    current_ = parent;
  }
}

/**
 * @brief Dereferences the iterator to get the value of the current node.
 *
 * @return reference The value of the current node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
typename RBTreeBaseIterator<Key, Comparator, IsConst>::reference
RBTreeBaseIterator<Key, Comparator, IsConst>::operator*() const {
  return this->getCurrentNode()->key_;
}

/**
 * @brief Dereferences the iterator to get a pointer to the value of the current
 * node.
 *
 * @return pointer A pointer to the value of the current node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
typename RBTreeBaseIterator<Key, Comparator, IsConst>::pointer
RBTreeBaseIterator<Key, Comparator, IsConst>::operator->() const {
  return &(this->getCurrentNode()->key_);
}

/**
 * @brief Checks if two iterators are not equal.
 *
 * @param other The other iterator to compare with.
 *
 * @return bool True if the iterators are not equal, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
bool RBTreeBaseIterator<Key, Comparator, IsConst>::operator!=(
    const RBTreeBaseIterator &other)
    const noexcept { // если указатели разные, итераторы считаются неравными
  return this->current_ != other.current_;
}

/**
 * @brief Checks if two iterators are equal.
 *
 * @param other The other iterator to compare with.
 *
 * @return bool True if the iterators are equal, false otherwise.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator, bool IsConst>
bool RBTreeBaseIterator<Key, Comparator, IsConst>::operator==(
    const RBTreeBaseIterator &other) const noexcept {
  return this->current_ == other.current_;
}

// RBTreeIterator

/**
 * @brief Pre-increments the iterator to the next node in the RBTree.
 *
 * @return iterator& A reference to the incremented iterator.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTreeIterator<Key, Comparator>::iterator &
RBTreeIterator<Key, Comparator>::operator++() { // префиксный инкремент
  this->increment();
  return *this;
}

/**
 * @brief Post-increments the iterator to the next node in the RBTree.
 *
 * @return iterator A copy of the iterator before the increment.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTreeIterator<Key, Comparator>::iterator
RBTreeIterator<Key, Comparator>::operator++(int) { // постфиксный инкремент
  iterator tmp(*this);
  this->increment();
  return tmp;
}

/**
 * @brief Pre-decrements the iterator to the previous node in the RBTree.
 *
 * @return iterator& A reference to the decremented iterator.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTreeIterator<Key, Comparator>::iterator &
RBTreeIterator<Key, Comparator>::operator--() { // префиксный декремент
  this->decrement();
  return *this;
}

/**
 * @brief Post-decrements the iterator to the previous node in the RBTree.
 *
 * @return iterator A copy of the iterator before the decrement.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename RBTreeIterator<Key, Comparator>::iterator
RBTreeIterator<Key, Comparator>::operator--(int) { // постфиксный декремент
  iterator tmp(*this);
  this->decrement();
  return tmp;
}

// ConstRBTreeIterator

/**
 * @brief Pre-increments the const_iterator to the next node in the RBTree.
 *
 * @return iterator& A reference to the incremented const_iterator.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename ConstRBTreeIterator<Key, Comparator>::iterator &
ConstRBTreeIterator<Key, Comparator>::operator++() {
  this->increment();
  return *this;
}

/**
 * @brief Post-increments the const_iterator to the next node in the RBTree.
 *
 * @return iterator A copy of the const_iterator before the increment.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename ConstRBTreeIterator<Key, Comparator>::iterator
ConstRBTreeIterator<Key, Comparator>::operator++(int) {
  iterator tmp(*this);
  this->increment();
  return tmp;
}

/**
 * @brief Pre-decrements the const_iterator to the previous node in the RBTree.
 *
 * @return iterator& A reference to the decremented const_iterator.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename ConstRBTreeIterator<Key, Comparator>::iterator &
ConstRBTreeIterator<Key, Comparator>::operator--() {
  this->decrement();
  return *this;
}

/**
 * @brief Post-decrements the const_iterator to the previous node in the RBTree.
 *
 * @return iterator A copy of the const_iterator before the decrement.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
typename ConstRBTreeIterator<Key, Comparator>::iterator
ConstRBTreeIterator<Key, Comparator>::operator--(int) {
  iterator tmp(*this);
  this->decrement();
  return tmp;
}

/******************************************************************************
 * DEBUGGING METHODS
 ******************************************************************************/

/**
 * @brief Prints the nodes of the RBTree with their pointers.
 *
 * @param node The root node of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::printNode(
    Node *node) const { // Метод для печати узолов подряд с указателями
  if (node) {
    std::cout << (node->red_ ? "[R]" : "[B]") << "  " << node->key_
              << (root_ == node ? "      <ROOT>" : "") << std::endl;

    std::cout << "parent:" << node->parent_ << " ("
              << (node->parent_ ? reinterpret_cast<Node *>(node->parent_)->key_
                                : -1)
              << ")" << std::endl;
    std::cout << "  "
              << "node:" << node << " ("
              << (node->parent_ && node->parent_->left_ == node ? "left"
                                                                : "right")
              << ")" << std::endl;
    std::cout << "  "
              << "left:" << node->left_ << " "
              << "right:" << node->right_ << std::endl
              << std::endl;
    printNode(reinterpret_cast<Node *>(node->left_));
    printNode(reinterpret_cast<Node *>(node->right_));
  }
}

/**
 * @brief Calculates the black height of the RBTree.
 *
 * @param node The root node of the RBTree.
 *
 * @return int The black height of the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
int RBTree<Key, Comparator>::blackHeight(
    const Node *node) const { // Метод для подсчёта чёрной высоты
  if (node == nullptr) {
    return 0;
  }
  int height = 0;
  const Node *current = node;
  while (current != nullptr) {
    if (!current->red_) {
      height++;
    }
    current = reinterpret_cast<Node *>(current->left_);
  }
  return height;
}

/**
 * @brief Prints a single node of the RBTree.
 *
 * @param node The node to print.
 * @param depth The depth of the node in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::printRBNode(
    const Node *node, int depth) { // Метод для печати одного узла
  std::string color = (node->red_) ? "R" : "B";
  int black_height = blackHeight(node);
  std::cout << std::string(depth * 4, ' ') << "[" << color
            << (!node->red_ ? std::to_string(black_height + 1) : "") << "]"
            << node->key_ << std::endl;
}

/**
 * @brief Prints a NIL node of the RBTree.
 *
 * @param depth The depth of the NIL node in the RBTree.
 * @param blackHeight The black height of the NIL node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::printNILNode(
    int depth, int blackHeight) { // Метод для печати NIL узла
  std::cout << std::string(depth * 4, ' ') << "NIL["
            << "B" << blackHeight + (blackHeight == 0 ? 1 : 0) << "]"
            << std::endl;
}

/**
 * @brief Prints the RBTree.
 *
 * @param node The root node of the RBTree.
 * @param depth The depth of the root node in the RBTree.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::printRBTree(
    const Node *node, int depth) { // Метод для печати дерева
  if (node != nullptr) {
    printRBTree(reinterpret_cast<Node *>(node->right_), depth + 1);
    printRBNode(node, depth);
    printRBTree(reinterpret_cast<Node *>(node->left_), depth + 1);
  } else {
    // printNILNode(depth, blackHeight(node)); // печать NIL узлов
  }
}

/**
 * @brief Prints the map of the RBTree.
 *
 * @param node The root node of the RBTree.
 * @param depth The depth of the root node in the RBTree.
 * @param printNodeFunc The function to print a single node.
 *
 * @throws N/A
 */
template <typename Key, typename Comparator>
void RBTree<Key, Comparator>::printMap(
    const Node *node, int depth,
    std::function<void(const Node *, int)> printNodeFunc)
    const { // Метод для печати map
  if (node != nullptr) {
    printMap(reinterpret_cast<Node *>(node->right_), depth + 1, printNodeFunc);
    printNodeFunc(node, depth);
    printMap(reinterpret_cast<Node *>(node->left_), depth + 1, printNodeFunc);
  }
}

} // namespace s21
