#ifndef LAB16_TASKS_H_
#define LAB16_TASKS_H_

#include <memory>
#include <random>
#include <string>
#include <vector>

// класс для проверки
class InputValidator {
 public:
  static int read_int(const std::string& prompt);
  static int read_int_in_range(const std::string& prompt, int min_value,
                               int max_value);
  static std::vector<int> read_values_from_keyboard();
  static std::vector<int> generate_random_values();
  static std::vector<int> read_values_from_file();
};

// класс бинарного дерева поиска
class TreeNode {
 public:
  explicit TreeNode(int node_value) : value(node_value) {}

  int get_value() const { return value; }

  const std::unique_ptr<TreeNode>& left_node() const { return left; }
  const std::unique_ptr<TreeNode>& right_node() const { return right; }

  std::unique_ptr<TreeNode>* left_ptr() { return &left; }
  std::unique_ptr<TreeNode>* right_ptr() { return &right; }

 private:
  int value;
  std::unique_ptr<TreeNode> left;
  std::unique_ptr<TreeNode> right;
};

class BinarySearchTree {
 public:
  BinarySearchTree() = default; // конструктор по умолчанию

  void insert(int value);
  bool contains(int value) const;
  std::vector<int> get_inorder_values() const; // в возрастающем порядке
  bool get_second_max(int* second_max) const; // второе максимальное
  void print_graphical(const std::string& title) const;
  bool empty() const;

 private:
  std::unique_ptr<TreeNode> root_;

  void insert_impl(std::unique_ptr<TreeNode>* node,
                   int value); // рекурсивная вставка
  bool contains_impl(const TreeNode* node,
                     int value) const; // рекурсивный поиск по дереву
  void inorder_impl(
      const TreeNode* node,
      std::vector<int>* values) const; // рекурсивный симметричный обход
  void print_graphical_impl(const TreeNode* node, int depth) const;
};

struct TaskInputData {
  BinarySearchTree tree; // дерево bst
  std::vector<int> source_values; // исходные значения в порядке ввода/генерации
};

TaskInputData build_tree_with_three_input_modes();

void run_tree_work_2();
void run_tree_work_11();
void run_tree_work_18();

#endif
