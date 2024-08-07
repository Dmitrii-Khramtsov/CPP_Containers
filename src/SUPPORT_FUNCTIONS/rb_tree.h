// Copyright 2024 Dmitrii Khramtsov

/**
 * @file rb_tree.h
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

#ifndef CPP2_S21_CONTAINERS_RB_TREE_H_
#define CPP2_S21_CONTAINERS_RB_TREE_H_

#include <functional> // printMap
#include <initializer_list>
#include <iostream>
#include <stack> // (нужно подключить наш стек и исправить в коде std::) для реализации метода count, deleteSubtree
#include <utility> // std::pair

namespace s21 {

enum how_many_children { no_children, one_child, two_children };

template <typename Key, typename Comparator, bool IsConst>
class RBTreeBaseIterator;

template <typename Key, typename Comparator> class RBTreeIterator;

template <typename Key, typename Comparator> class ConstRBTreeIterator;

template <typename Key, typename Comparator> struct RBTBaseNode {
  RBTBaseNode *parent_;
  RBTBaseNode *left_;
  RBTBaseNode *right_;
  bool red_;

  RBTBaseNode()
      : parent_(nullptr), left_(nullptr), right_(nullptr), red_(false) {}

  RBTBaseNode(RBTBaseNode *parent, RBTBaseNode *left, RBTBaseNode *right)
      : parent_(parent), left_(left), right_(right), red_(false) {}
};

template <typename Key, typename Comparator>
struct RBTNode : public RBTBaseNode<Key, Comparator> {
  using key_type = Key;
  using reference = Key &;
  using const_reference = const Key &;
  Key key_;

  RBTNode(const_reference key) : key_(key) {
    this->red_ = true; // цвет узла красный
  }

  RBTNode(key_type &&key) noexcept : key_(std::move(key)) { this->red_ = true; }
};

template <typename Key, typename Comparator = std::less<Key>> class RBTree {
public:
  // RBTree Member type:
  using key_type = Key;
  using node_type = std::pair<const key_type, Comparator>;
  using reference = Key &;
  using const_reference = const key_type &;
  using size_type = std::size_t;
  using Node = RBTNode<Key, Comparator>;
  using BaseNode = RBTBaseNode<Key, Comparator>;
  using iterator = RBTreeIterator<Key, Comparator>;
  using const_iterator = ConstRBTreeIterator<Key, Comparator>;

  RBTree();
  RBTree(std::initializer_list<node_type> const &items);
  RBTree(const RBTree &other);
  RBTree(RBTree &&other) noexcept;
  ~RBTree() noexcept;
  RBTree &operator=(const RBTree<Key, Comparator> &other);
  RBTree &operator=(RBTree<Key, Comparator> &&other) noexcept;

  // Main methods:
  size_type size() const noexcept;
  size_type max_size() const;
  bool empty() const;
  size_type count(const Key &key) const noexcept;

  void clear();
  void swap(RBTree &other) noexcept;
  void merge(RBTree &other) noexcept;
  void mergeUnique(RBTree &other) noexcept;
  bool contains(const key_type &key) const;
  iterator find(const_reference key);
  const_iterator find(const_reference key) const;
  iterator lower_bound(const Key &key);
  const_iterator lower_bound(const Key &key) const;
  iterator upper_bound(const Key &key);
  const_iterator upper_bound(const Key &key) const;

  Node *getMinNode(Node *node) const;
  Node *getMaxNode(Node *node) const;
  const Node *getRoot() const;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  void erase(iterator pos);
  std::pair<iterator, bool> insert(const key_type &key);
  std::pair<iterator, bool> insertUnique(const key_type &key);

private:
  // Auxiliary methods:
  void countUniqueKey(const Key &key, Node *node,
                      size_type &count) const noexcept;
  std::pair<iterator, bool> insert(const key_type &key, bool unique);
  void deleteSubtree(Node *node);

  Node *findNode(const key_type &key) const;
  Node *findMinNode(Node *node) const;
  Node *findMaxNode(Node *node) const;
  Node *CopyTree(Node *node, Node &fake_node);

  // Auxiliary insertion and balancing methods:
  void insertNode(Node *root, Node *new_node);
  void insertFixup(Node *node);

  bool leftDadRightSon(Node *node);
  bool rightDadLeftSon(Node *node);
  bool leftDadLeftSon(Node *node);
  bool rightDadRightSon(Node *node);

  bool redUncle(Node *node);
  bool doubleRed(Node *node);
  void doubleRedFixup(Node *node);
  void redUncleChangeColors(Node *node);

  void blackUncleFixup(Node *node);

  void leftRotate(Node *node);
  void rightRotate(Node *node);

  void oppositeDadAndGrandpa(Node *&node, Node *&parent, Node *&grandparent);
  void sameSideDadAndGrandpa(Node *&node, Node *&parent, Node *&grandparent);

  // Auxiliary deletion and balancing methods:
  Node *rNephewsLS(Node *node);
  Node *lNephewsLS(Node *node);
  Node *rNephewsRS(Node *node);
  Node *lNephewsRS(Node *node);

  Node *rSibling(Node *node);
  Node *lSibling(Node *node);

  bool sR(Node *node);
  bool lNBrNB(Node *node);
  bool lNRrNB(Node *node);
  bool rNRlNA(Node *node);
  bool mirrorSR(Node *node);
  bool mirrorLNBrNB(Node *node);
  bool mirrorLNRrNB(Node *node);
  bool mirrorRNRlNA(Node *node);

  void lNephewsRedRNephewsBlack(Node *node);         // (case_1a)
  void lNephewsBlackRNephewsBlack(Node *node);       // (case_2a)
  void rNephewsRedLNephewsAny(Node *node);           // (case_3a)
  void redSibling(Node *node);                       // (case_4a)
  void mirrorLNephewsRedRNephewsBlack(Node *node);   // (case_1b)
  void mirrorLNephewsBlackRNephewsBlack(Node *node); // (case_2b)
  void mirrorRNephewsRedLNephewsAny(Node *node);     // (case_3b)
  void mirrorRedSibling(Node *node);                 // (case_4b)

  void eraseFixup(Node *node);

  void noChildren(Node *eraised_node, Node *&to_fix);
  void oneChildren(Node *eraised_node, Node *&to_fix, bool *color);
  void twoChildren(Node *eraised_node, Node *&to_fix, bool *color);
  char howManyChildren(Node *node);

  void swapNodes(Node *eraised_node, Node *successor);
  void transplant(Node *eraised_node, Node *successor);
  void eraseNode(Node *node, Node *&to_fix, bool *color);

  // Debugging methods:
public:
  void printTree() const { printNode(root_); }
  void drawTree() { printRBTree(root_, 0); }

  void printMap(const Node *node, int depth,
                std::function<void(const Node *, int)> printNodeFunc) const;

  int blackHeight(const Node *node) const;

private:
  void printRBTree(const Node *node, int depth);
  void printNode(Node *node) const;
  void printRBNode(const Node *node, int depth);
  void printNILNode(int depth, int blackHeight);

private:
  Node *root_;
  BaseNode fake_node_;
  size_type size_ = 0;
  Comparator comparator_;
};

// Base iterator:
template <typename Key, typename Comparator, bool IsConst>
class RBTreeBaseIterator {
public:
  using iterator_category =
      std::bidirectional_iterator_tag; // переназначаем для совместимости
                                       // с библиотекой STL и соответствия
                                       // заданию
  using value_type = typename std::conditional<IsConst, const Key, Key>::type;
  using pointer = value_type *;
  using reference = value_type &;
  using difference_type =
      std::ptrdiff_t; // difference_type - это тип,
                      // представляющий расстояние между двумя итераторами,
                      // используется в арифметических операциях с итераторами
  using tree_reference =
      typename std::conditional<IsConst, const RBTree<Key, Comparator> &,
                                RBTree<Key, Comparator> &>::
          type; // Псевдоним 'tree_ref' представляет тип, который является
                // ссылкой на const или non-const объект RBTree,
                //  в зависимости от значения параметра шаблона 'IsConst'.
                // Это позволяет классу RBTreeBaseIterator работать
                // как с const, так и с non-const итераторами.

  RBTreeBaseIterator() = delete; // не нужен конструктор по умолчанию
                                 // для пустого итератора - удаляем его

  explicit RBTreeBaseIterator(tree_reference tree,
                              typename RBTree<Key, Comparator>::Node *node)
      : tree_(tree), current_(node) {}

  RBTreeBaseIterator(const RBTreeBaseIterator &other)
      : tree_(other.tree_), current_(other.current_) {} // copy constructor

  reference operator*() const;
  pointer operator->() const;

  bool operator!=(const RBTreeBaseIterator &other) const noexcept;
  bool operator==(const RBTreeBaseIterator &other) const noexcept;

protected:
  using Node = typename RBTree<Key, Comparator>::Node;

  Node *getCurrentNode() const {
    return const_cast<Node *>(static_cast<const Node *>(current_));
  }

  void increment();
  void decrement();

  tree_reference tree_;
  Node *current_; // указатель на текущий узел
};

// Iterator:
template <typename Key, typename Comparator>
class RBTreeIterator : public RBTreeBaseIterator<Key, Comparator, false> {
public:
  using Base = RBTreeBaseIterator<Key, Comparator, false>;
  using Node = typename Base::Node;
  using iterator = RBTreeIterator;

  explicit RBTreeIterator(RBTree<Key, Comparator> &tree,
                          typename RBTree<Key, Comparator>::Node *node)
      : Base(tree, node) {
  } // конструктор инициализирует новый объект RBTree и указатель на Node
    // для доступа к полям RBTree через объект tree_
    // explicit запрещает неявное преобразование типов

  RBTreeIterator(const RBTreeIterator &other)
      : Base(other) {} // copy constructor

  Node *getCurrentNode() const { return Base::getCurrentNode(); }

  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);

  iterator &operator=(const iterator &other) {
    if (this != &other) {
      this->tree_ = other.tree_;
      this->current_ = other.current_;
    }
    return *this;
  }
};

// Constant iterator:
template <typename Key, typename Comparator>
class ConstRBTreeIterator : public RBTreeBaseIterator<Key, Comparator, true> {
public:
  using Base = RBTreeBaseIterator<Key, Comparator, true>;
  using Node = typename Base::Node;
  using iterator = ConstRBTreeIterator;

  explicit ConstRBTreeIterator(const RBTree<Key, Comparator> &tree, Node *node)
      : RBTreeBaseIterator<Key, Comparator, true>(tree, node) {}

  ConstRBTreeIterator(const ConstRBTreeIterator &other)
      : Base(other) {} // copy constructor

  const Node *getCurrentNode() const { return Base::getCurrentNode(); }

  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);

  iterator &operator=(const iterator &other) {
    if (this != &other) {
      this->tree_ = other.tree_;
      this->current_ = other.current_;
    }
    return *this;
  }
};

} //  namespace s21

#include "rb_tree.tpp" // Подключаем файл с определениями шаблонов

#endif // CPP2_S21_CONTAINERS_RB_TREE_H_
