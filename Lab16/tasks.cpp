#include "tasks.h"

#include <fstream>
#include <iostream>
#include <sstream>

static const int kMinNodesCount = 1;
static const int kMaxNodesCount = 100;

static void print_ui_title(const std::string& title) {
  std::cout << "\n" << title << "\n";
}

static bool parse_ints_from_line(const std::string& line,
                                 std::vector<int>* values) {
  std::stringstream stream(line);
  values->clear();
  int value = 0;

  while (stream >> value) {
    values->push_back(value);
  }
  char extra = '\0';
  if (stream >> extra) {
    return false;
  }

  return true;
}

static void print_values_line(const std::string& title,
                              const std::vector<int>& values) {
  std::cout << title;
  for (int value : values) {
    std::cout << value << " ";
  }
  std::cout << "\n";
}

int InputValidator::read_int(const std::string& prompt) {
  while (true) {
    std::cout << prompt;

    std::string line;
    if (!std::getline(std::cin, line)) {
      std::cin.clear();
      std::cout << "Ошибка ввода: не удалось прочитать строку\n";
      std::cout << "Повторите ввод\n";
      continue;
    }

    std::vector<int> values;
    if (!parse_ints_from_line(line, &values)) {
      std::cout << "Ошибка ввода: в строке есть неверные символы\n";
      std::cout << "Повторите ввод\n";
      continue;
    }

    if (values.size() != 1) {
      std::cout << "Ошибка ввода: нужно ввести ровно одно целое число\n";
      std::cout << "Повторите ввод\n";
      continue;
    }

    return values[0];
  }
}

int InputValidator::read_int_in_range(const std::string& prompt, int min_value,
                                      int max_value) {
  while (true) {
    const int value = read_int(prompt);

    if (value < min_value || value > max_value) {
      std::cout << "Ошибка ввода: число вне допустимого диапазона\n";
      std::cout << "Допустимый диапазон: [" << min_value << ", "
                << max_value << "]\n";
      continue;
    }

    return value;
  }
}

std::vector<int> InputValidator::read_values_from_keyboard() {
  while (true) {
    // заранее спрашиваем количество, чтобы не принимать пустые наборы
    const int count = read_int_in_range(
        "Введите количество элементов дерева: ",
        kMinNodesCount, kMaxNodesCount);

    std::cout << "Введите " << count
              << " целых чисел через пробел: ";

    std::string line;
    if (!std::getline(std::cin, line)) {
      std::cin.clear();
      std::cout << "Ошибка ввода: не удалось прочитать строку\n";
      std::cout << "Повторите ввод набора\n";
      continue;
    }

    // разбираем строку и проверяем точное количество чисел
    std::vector<int> values;
    if (!parse_ints_from_line(line, &values)) {
      std::cout << "Ошибка ввода: в строке есть неверные символы\n";
      std::cout << "Повторите ввод набора\n";
      continue;
    }

    if (static_cast<int>(values.size()) != count) {
      std::cout << "Ошибка ввода: количество чисел не совпадает\n";
      std::cout << "Повторите ввод набора\n";
      continue;
    }

    return values;
  }
}

std::vector<int> InputValidator::generate_random_values() {
  while (true) {
    // читаем параметры генерации с полной валидацией
    const int count = read_int_in_range(
        "Введите количество случайных элементов: ",
        kMinNodesCount, kMaxNodesCount);

    const int min_value = read_int("Введите минимальное значение диапазона: ");
    const int max_value = read_int("Введите максимальное значение диапазона: ");

    if (min_value > max_value) {
      std::cout << "Ошибка ввода: минимум не может быть больше максимума\n";
      std::cout << "Повторите ввод параметров генерации\n";
      continue;
    }

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<int> distribution(min_value, max_value);

    std::vector<int> values;
    values.reserve(count);

    for (int i = 0; i < count; ++i) {
      values.push_back(distribution(generator));
    }

    return values;
  }
}

std::vector<int> InputValidator::read_values_from_file() {
  while (true) {
    std::cout << "Введите путь к файлу: ";
    std::string file_path;
    if (!std::getline(std::cin, file_path)) {
      std::cin.clear();
      std::cout << "Ошибка ввода: не удалось прочитать строку\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }

    if (file_path.empty()) {
      std::cout << "Ошибка ввода: путь к файлу не должен быть пустым\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }

    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
      std::cout << "Ошибка ввода: не удалось открыть файл\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }

    std::stringstream buffer;
    buffer << input_file.rdbuf();
    std::vector<int> values;
    if (!parse_ints_from_line(buffer.str(), &values)) {
      std::cout << "Ошибка ввода: в файле есть неверные символы\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }

    if (values.empty()) {
      std::cout << "Ошибка ввода: файл не содержит целых чисел\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }
    if (static_cast<int>(values.size()) > kMaxNodesCount) {
      std::cout << "Ошибка ввода: в файле слишком много чисел\n";
      std::cout << "Повторите ввод пути к файлу\n";
      continue;
    }

    return values;
  }
}

void BinarySearchTree::insert(int value) {
  // вставляем значение в bst с сохранением порядка
  insert_impl(&root_, value);
}

bool BinarySearchTree::contains(int value) const {
  return contains_impl(root_.get(), value);
}

std::vector<int> BinarySearchTree::get_inorder_values() const {
  std::vector<int> values;
  // сортировка по возрастанию
  inorder_impl(root_.get(), &values);
  return values;
}

bool BinarySearchTree::get_second_max(int* second_max) const {
  // если дерево пустое или один узел, второго максимума нет
  if (root_ == nullptr ||
      (root_->left_node() == nullptr && root_->right_node() == nullptr)) {
    return false;
  }

  const TreeNode* current = root_.get();
  const TreeNode* parent = nullptr;

  // идем вправо до максимального узла
  while (current->right_node() != nullptr) {
    parent = current;
    current = current->right_node().get();
  }

  // если у максимума есть левое поддерево,
  // второй максимум это максимум в его левом поддереве
  if (current->left_node() != nullptr) {
    const TreeNode* max_in_left = current->left_node().get();
    while (max_in_left->right_node() != nullptr) {
      max_in_left = max_in_left->right_node().get();
    }
    *second_max = max_in_left->get_value();
    return true;
  }

  // иначе второй максимум это родитель максимального узла
  if (parent != nullptr) {
    *second_max = parent->get_value();
    return true;
  }

  return false;
}

void BinarySearchTree::print_graphical(const std::string& title) const {
  std::cout << title << "\n";

  if (root_ == nullptr) {
    std::cout << "(пустое дерево)\n";
    return;
  }

  // печатаем дерево боком: правый выше, левый ниже
  print_graphical_impl(root_.get(), 0);
}

bool BinarySearchTree::empty() const {
  return root_ == nullptr;
}

void BinarySearchTree::insert_impl(std::unique_ptr<TreeNode>* node, int value) {
  if (*node == nullptr) {
    *node = std::make_unique<TreeNode>(value);
    return;
  }

  if (value < (*node)->get_value()) {
    insert_impl((*node)->left_ptr(), value); // рекурсивно
  } else {
    insert_impl((*node)->right_ptr(), value);
  }
}

bool BinarySearchTree::contains_impl(const TreeNode* node, int value) const {
  if (node == nullptr) {
    return false;
  }

  if (node->get_value() == value) {
    return true;
  }

  // идем только в одну ветку,
  // поэтому при сбалансированном дереве это O(log n)
  if (value < node->get_value()) {
    return contains_impl(node->left_node().get(), value);
  }

  return contains_impl(node->right_node().get(), value);
}

void BinarySearchTree::inorder_impl(const TreeNode* node,
                                    std::vector<int>* values) const {
  // рекурсивно обходим левое поддерево
  if (node == nullptr) {
    return;
  }

  inorder_impl(node->left_node().get(), values);
  // добавляем текущий узел между левым и правым обходом
  values->push_back(node->get_value());
  inorder_impl(node->right_node().get(), values);
}

void BinarySearchTree::print_graphical_impl(const TreeNode* node,
                                            int depth) const {
  if (node == nullptr) {
    return;
  }

  // сначала печатаем правое поддерево, чтобы оно было сверху
  print_graphical_impl(node->right_node().get(), depth + 1);

  // делаем отступ по глубине
  for (int i = 0; i < depth; ++i) {
    std::cout << "  ";
  }

  // печатаем метку узла
  std::cout << node->get_value() << "\n";

  // потом печатаем левое поддерево
  print_graphical_impl(node->left_node().get(), depth + 1);
}

TaskInputData build_tree_with_three_input_modes() {
  while (true) {
    print_ui_title("Выбор способа ввода");
    std::cout << "1. Ввод с клавиатуры\n";
    std::cout << "2. Случайная генерация\n";
    std::cout << "3. Ввод из файла\n";

    const int mode =
        InputValidator::read_int_in_range("Введите режим: ", 1, 3);

    std::vector<int> values;

    if (mode == 1) {
      values = InputValidator::read_values_from_keyboard();
    } else if (mode == 2) {
      values = InputValidator::generate_random_values();
    } else {
      values = InputValidator::read_values_from_file();
    }

    if (values.empty()) {
      std::cout << "Ошибка ввода: набор значений не должен быть пустым\n";
      std::cout << "Повторите выбор способа ввода\n";
      continue;
    }

    BinarySearchTree tree;
    for (int value : values) {
      tree.insert(value);
    }

    TaskInputData input_data;
    input_data.tree = std::move(tree);
    input_data.source_values = std::move(values);
    return input_data;
  }
}

void run_tree_work_2() {
  print_ui_title("TreeWork2");

  TaskInputData input_data = build_tree_with_three_input_modes();

  std::cout << "Данные до преобразования\n";
  input_data.tree.print_graphical(
      "Графическое представление дерева до преобразования");

  // получаем значения в возрастающем порядке
  const std::vector<int> sorted_values = input_data.tree.get_inorder_values();
  print_values_line(
      "Содержимое дерева в возрастающем порядке: ", sorted_values);
}

void run_tree_work_11() {
  print_ui_title("TreeWork11");

  TaskInputData input_data = build_tree_with_three_input_modes();

  std::cout << "Проверка до выполнения\n";
  input_data.tree.print_graphical(
      "Графическое представление дерева до преобразования");

  // читаем искомое значение x с проверкой ввода
  const int x = InputValidator::read_int("Введите значение X для поиска: ");

  // проверяем наличие x через bst-поиск
  const bool found = input_data.tree.contains(x);
  std::cout << "Результат поиска X: " << (found ? "True" : "False")
            << "\n";
}

void run_tree_work_18() {
  print_ui_title("TreeWork18");

  TaskInputData input_data = build_tree_with_three_input_modes();

  std::cout << "Данные до вычисления\n";
  input_data.tree.print_graphical(
      "Графическое представление дерева до преобразования");

  int second_max = 0;
  if (input_data.tree.get_second_max(&second_max)) {
    std::cout << "Второе максимальное значение: " << second_max << "\n";
  } else {
    std::cout << "В дереве недостаточно вершин для поиска второго "
              << "максимума\n";
  }

}
