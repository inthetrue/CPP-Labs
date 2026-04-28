#include "tasks.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_set>
#include <utility>

namespace lab11 {

CircularNode::CircularNode(int value) : value(value), next(nullptr) {}

CircularSinglyList::CircularSinglyList() : head_(nullptr), size_(0) {}

CircularSinglyList::CircularSinglyList(const CircularSinglyList& other)
    : head_(nullptr), size_(0) {
  // копируем значения в том же порядке
  std::vector<int> values = other.to_vector();
  for (int value : values) {
    push_back(value);
  }
}

CircularSinglyList::~CircularSinglyList() {
  // удаляем все узлы списка
  clear();
}

void CircularSinglyList::push_back(int value) {
  // в кольце новый узел ставим между хвостом и головой
  CircularNode* node = new CircularNode(value);
  if (head_ == nullptr) {
    node->next = node;
    head_ = node;
    ++size_;
    return;
  }

  CircularNode* tail = head_;
  while (tail->next != head_) {
    tail = tail->next;
  }

  tail->next = node;
  node->next = head_;
  ++size_;
}

bool CircularSinglyList::remove_value(int value) {
  // удаляем первый узел с нужным значением
  if (head_ == nullptr) {
    return false;
  }

  CircularNode* current = head_;
  CircularNode* prev = nullptr;

  do {
    if (current->value == value) {
      if (current == head_) {
        if (head_->next == head_) {
          delete head_;
          head_ = nullptr;
          size_ = 0;
          return true;
        }

        CircularNode* tail = head_;
        while (tail->next != head_) {
          tail = tail->next;
        }
        head_ = head_->next;
        tail->next = head_;
      } else {
        prev->next = current->next;
      }
      delete current;
      --size_;
      return true;
    }
    prev = current;
    current = current->next;
  } while (current != head_);

  return false;
}

bool CircularSinglyList::contains(int value) const {
  // делаем один круг и ищем значение
  if (head_ == nullptr) {
    return false;
  }

  CircularNode* current = head_;
  do {
    if (current->value == value) {
      return true;
    }
    current = current->next;
  } while (current != head_);

  return false;
}

bool CircularSinglyList::empty() const { return head_ == nullptr; }

int CircularSinglyList::size() const { return size_; }

std::vector<int> CircularSinglyList::to_vector() const {
  // собираем список в вектор для удобного вывода
  std::vector<int> result;
  if (head_ == nullptr) {
    return result;
  }

  CircularNode* current = head_;
  do {
    result.push_back(current->value);
    current = current->next;
  } while (current != head_);

  return result;
}

void CircularSinglyList::export_step_two_and_erase(const std::string& output_file_path) {
  // получаем порядок удаления и пишем его в файл
  std::ofstream output(output_file_path);
  if (!output.is_open()) {
    std::cerr << "Cannot open file for ListWork67 output: " << output_file_path
              << '\n';
    return;
  }

  const std::vector<int> order = collect_step_two_and_erase();
  for (size_t i = 0; i < order.size(); ++i) {
    output << order[i];
    if (i + 1 < order.size()) {
      output << ' ';
    }
  }
  output << '\n';
}

std::vector<int> CircularSinglyList::collect_step_two_and_erase() {
  // формируем новый список в порядке удаления
  std::vector<int> order;
  if (head_ == nullptr) {
    return order;
  }

  CircularNode* current = head_;
  CircularNode* prev = head_;
  while (prev->next != head_) {
    prev = prev->next;
  }

  while (size_ > 0) {
    order.push_back(current->value);

    CircularNode* next_after_removed = current->next;
    if (size_ == 1) {
      delete current;
      head_ = nullptr;
      size_ = 0;
      break;
    }

    if (current == head_) {
      head_ = current->next;
    }

    prev->next = current->next;
    delete current;
    --size_;

    // шаг 2: пропускаем один узел и берем следующий
    current = next_after_removed->next;
    prev = next_after_removed;
  }

  return order;
}

void CircularSinglyList::clear() {
  // по очереди удаляем узлы, пока список не станет пустым
  while (head_ != nullptr) {
    if (head_->next == head_) {
      delete head_;
      head_ = nullptr;
      size_ = 0;
      return;
    }

    CircularNode* tail = head_;
    while (tail->next != head_) {
      tail = tail->next;
    }

    CircularNode* old_head = head_;
    head_ = head_->next;
    tail->next = head_;
    delete old_head;
    --size_;
  }
}

DoublyNode::DoublyNode(int value)
    : value(value), prev(nullptr), next(nullptr) {}

DoublyLinearList::DoublyLinearList() : head_(nullptr), tail_(nullptr) {}

DoublyLinearList::DoublyLinearList(const DoublyLinearList& other)
    : head_(nullptr), tail_(nullptr) {
  // копируем элементы в том же порядке
  for (const DoublyNode* node = other.head(); node != nullptr; node = node->next) {
    push_back(node->value);
  }
}

DoublyLinearList::~DoublyLinearList() {
  // удаляем все узлы списка
  clear();
}

void DoublyLinearList::push_back(int value) {
  // добавляем узел в конец по указателю tail
  DoublyNode* node = new DoublyNode(value);
  if (head_ == nullptr) {
    head_ = node;
    tail_ = node;
    return;
  }

  tail_->next = node;
  node->prev = tail_;
  tail_ = node;
}

bool DoublyLinearList::remove_value(int value) {
  // удаляем первый найденный узел по значению
  for (DoublyNode* node = head_; node != nullptr; node = node->next) {
    if (node->value != value) {
      continue;
    }

    if (node->prev != nullptr) {
      node->prev->next = node->next;
    } else {
      head_ = node->next;
    }

    if (node->next != nullptr) {
      node->next->prev = node->prev;
    } else {
      tail_ = node->prev;
    }

    delete node;
    return true;
  }

  return false;
}

bool DoublyLinearList::contains(int value) const {
  // ищем значение простым проходом
  for (const DoublyNode* node = head_; node != nullptr; node = node->next) {
    if (node->value == value) {
      return true;
    }
  }
  return false;
}

bool DoublyLinearList::empty() const { return head_ == nullptr; }

std::vector<int> DoublyLinearList::to_vector() const {
  // собираем элементы в вектор
  std::vector<int> result;
  for (const DoublyNode* node = head_; node != nullptr; node = node->next) {
    result.push_back(node->value);
  }
  return result;
}

const DoublyNode* DoublyLinearList::head() const { return head_; }

void DoublyLinearList::clear() {
  // удаляем узлы циклом
  DoublyNode* node = head_;
  while (node != nullptr) {
    DoublyNode* next = node->next;
    delete node;
    node = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

std::vector<int> extract_between_min_max(const DoublyLinearList& list) {
  // сначала находим min и max, потом берем элементы между ними
  const DoublyNode* min_node = nullptr;
  const DoublyNode* max_node = nullptr;

  for (const DoublyNode* node = list.head(); node != nullptr; node = node->next) {
    if (min_node == nullptr || node->value < min_node->value) {
      min_node = node;
    }
    if (max_node == nullptr || node->value > max_node->value) {
      max_node = node;
    }
  }

  std::vector<int> result;
  if (min_node == nullptr || max_node == nullptr || min_node == max_node) {
    return result;
  }

  bool between = false;
  for (const DoublyNode* node = list.head(); node != nullptr; node = node->next) {
    if (node == min_node || node == max_node) {
      if (!between) {
        between = true;
      } else {
        break;
      }
      continue;
    }

    if (between) {
      result.push_back(node->value);
    }
  }

  return result;
}

void init_t_list(TList& list) {
  // процедура инициализации списка tlist
  // задаем пустое состояние списка
  list.first = nullptr;
  list.last = nullptr;
  list.current = nullptr;
}

void clear_t_list(TList& list) {
  // процедура очистки списка tlist
  // удаляем все узлы списка
  DoublyNode* node = list.first;
  while (node != nullptr) {
    DoublyNode* next = node->next;
    delete node;
    node = next;
  }
  init_t_list(list);
}

void insert_last(TList& list, int data) {
  // процедура вставки в конец tlist
  // добавляем в конец и делаем новый узел текущим
  DoublyNode* node = new DoublyNode(data);
  if (list.first == nullptr) {
    list.first = node;
    list.last = node;
    list.current = node;
    return;
  }

  list.last->next = node;
  node->prev = list.last;
  list.last = node;
  list.current = node;
}

void init_t_list_b(TListB& list) {
  // процедура инициализации списка tlistb
  // пустой список: барьер указывает сам на себя
  list.barrier = new DoublyNode(0);
  list.barrier->next = list.barrier;
  list.barrier->prev = list.barrier;
  list.current = nullptr;
}

void clear_t_list_b(TListB& list) {
  // процедура очистки списка tlistb
  // удаляем все узлы данных и потом барьер
  if (list.barrier == nullptr) {
    list.current = nullptr;
    return;
  }

  DoublyNode* node = list.barrier->next;
  while (node != list.barrier) {
    DoublyNode* next = node->next;
    delete node;
    node = next;
  }

  delete list.barrier;
  list.barrier = nullptr;
  list.current = nullptr;
}

void lb_insert_last(TListB& list, int data) {
  // процедура вставки в конец списка с барьером
  // вставляем новый узел перед барьером
  if (list.barrier == nullptr) {
    init_t_list_b(list);
  }

  DoublyNode* node = new DoublyNode(data);
  DoublyNode* old_last = list.barrier->prev;

  node->next = list.barrier;
  node->prev = old_last;
  old_last->next = node;
  list.barrier->prev = node;

  list.current = node;
}

ChildNode::ChildNode(const std::string& name)
    : name(name), prev(nullptr), next(nullptr) {}

KidsCircle::KidsCircle() : head_(nullptr), size_(0) {}

KidsCircle::KidsCircle(const KidsCircle& other) : head_(nullptr), size_(0) {
  // копируем имена в том же порядке
  if (other.head_ == nullptr) {
    return;
  }

  ChildNode* node = other.head_;
  do {
    push_back(node->name);
    node = node->next;
  } while (node != other.head_);
}

KidsCircle::~KidsCircle() {
  // удаляем все узлы круга
  clear();
}

void KidsCircle::push_back(const std::string& name) {
  // в двусвязном кольце можно идти в обе стороны
  ChildNode* node = new ChildNode(name);
  if (head_ == nullptr) {
    node->next = node;
    node->prev = node;
    head_ = node;
    ++size_;
    return;
  }

  ChildNode* tail = head_->prev;
  node->next = head_;
  node->prev = tail;
  tail->next = node;
  head_->prev = node;
  ++size_;
}

bool KidsCircle::remove_by_name(const std::string& name) {
  // удаляем ребенка по имени
  if (head_ == nullptr) {
    return false;
  }

  ChildNode* node = head_;
  do {
    if (node->name == name) {
      if (size_ == 1) {
        delete node;
        head_ = nullptr;
        size_ = 0;
        return true;
      }

      node->prev->next = node->next;
      node->next->prev = node->prev;
      if (node == head_) {
        head_ = node->next;
      }
      delete node;
      --size_;
      return true;
    }
    node = node->next;
  } while (node != head_);

  return false;
}

bool KidsCircle::contains(const std::string& name) const {
  // делаем один круг и ищем имя
  if (head_ == nullptr) {
    return false;
  }

  ChildNode* node = head_;
  do {
    if (node->name == name) {
      return true;
    }
    node = node->next;
  } while (node != head_);

  return false;
}

bool KidsCircle::empty() const { return size_ == 0; }

int KidsCircle::size() const { return size_; }

std::vector<std::string> KidsCircle::elimination_order(int rhyme_word_count) const {
  // считаем на копии, чтобы исходный круг не менять
  std::vector<std::string> order;
  if (rhyme_word_count <= 0 || head_ == nullptr) {
    return order;
  }

  KidsCircle working(*this);
  ChildNode* start = working.head_;
  bool clockwise = true; // направление

  while (!working.empty()) {
    ChildNode* eliminated = start;
    for (int i = 1; i < rhyme_word_count; ++i) {
      eliminated = clockwise ? eliminated->next : eliminated->prev;
    }

    order.push_back(eliminated->name);

    if (working.size_ == 1) {
      delete eliminated;
      working.head_ = nullptr;
      working.size_ = 0;
      break;
    }

    ChildNode* next_start = clockwise ? eliminated->prev : eliminated->next;

    eliminated->prev->next = eliminated->next;
    eliminated->next->prev = eliminated->prev;
    if (eliminated == working.head_) {
      working.head_ = eliminated->next;
    }
    delete eliminated;
    --working.size_;

    start = next_start;
    clockwise = !clockwise;
  }

  return order;
}

void KidsCircle::clear() {
  // удаляем узлы, пока круг не опустеет
  while (size_ > 0) {
    if (size_ == 1) {
      delete head_;
      head_ = nullptr;
      size_ = 0;
      return;
    }

    ChildNode* node = head_;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    head_ = node->next;
    delete node;
    --size_;
  }
}

bool solve_text2_from_file(const std::string& input_file_path,
                        const std::string& output_file_path) {
  // читаем данные из файла и пишем результат в файл
  std::ifstream input(input_file_path);
  if (!input.is_open()) {
    return false;
  }

  int rhyme_count = 0;
  input >> rhyme_count;
  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  KidsCircle kids;
  std::string name;
  while (std::getline(input, name)) {
    if (!name.empty()) {
      kids.push_back(name);
    }
  }

  std::vector<std::string> order = kids.elimination_order(rhyme_count);

  std::ofstream output(output_file_path);
  if (!output.is_open()) {
    return false;
  }

  for (const std::string& child_name : order) {
    output << child_name << '\n';
  }

  return true;
}

namespace {

enum class InputMode {
  kKeyboard = 1,
  kRandom = 2,
  kFile = 3,
};

void clear_input() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int read_int(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    int value = 0;
    if (std::cin >> value) {
      return value;
    }
    std::cout << "Ошибка ввода. Повторите.\n";
    clear_input();
  }
}

std::string read_line(const std::string& prompt) {
  std::cout << prompt;
  std::string line;
  std::getline(std::cin >> std::ws, line);
  return line;
}

InputMode ask_input_mode() {
  while (true) {
    std::cout << "Выберите тип ввода:\n";
    std::cout << "1 - с клавиатуры\n";
    std::cout << "2 - случайно (диапазон min..max)\n";
    std::cout << "3 - из файла\n";
    const int mode = read_int("Ваш выбор: ");
    if (mode >= 1 && mode <= 3) {
      return static_cast<InputMode>(mode);
    }
    std::cout << "Неверный пункт меню.\n";
  }
}

bool ask_yes_no(const std::string& prompt) {
  while (true) {
    const int choice = read_int(prompt + " (1 - да, 0 - нет): ");
    if (choice == 1) {
      return true;
    }
    if (choice == 0) {
      return false;
    }
    std::cout << "Введите 1 или 0\n";
  }
}

std::vector<int> read_ints_keyboard(const std::string& title) {
  const int count = read_int("Введите количество элементов для " + title + ": ");
  std::vector<int> data;
  for (int i = 0; i < count; ++i) {
    data.push_back(read_int("Значение [" + std::to_string(i) + "]: "));
  }
  return data;
}

std::vector<int> read_ints_random(const std::string& title) {
  const int count = read_int("Введите количество элементов для " + title + ": ");
  int min_value = read_int("Введите min: ");
  int max_value = read_int("Введите max: ");
  if (min_value > max_value) {
    std::swap(min_value, max_value);
  }

  std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(min_value, max_value);

  std::vector<int> data;
  for (int i = 0; i < count; ++i) {
    data.push_back(distribution(generator));
  }

  std::cout << "Сгенерированные данные: ";
  for (int value : data) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
  return data;
}

bool read_count_and_ints_from_file(const std::string& file_path, std::vector<int>& data) {
  std::ifstream input(file_path);
  if (!input.is_open()) {
    return false;
  }

  int count = 0;
  if (!(input >> count) || count < 0) {
    return false;
  }

  data.clear();
  data.reserve(static_cast<size_t>(count));
  for (int i = 0; i < count; ++i) {
    int value = 0;
    if (!(input >> value)) {
      return false;
    }
    data.push_back(value);
  }
  return true;
}

std::vector<int> read_ints_file(const std::string& title) {
  while (true) {
    std::cout << "Формат файла для " << title << ": сначала N, затем N чисел.\n";
    const std::string path = read_line("Введите путь к файлу: ");
    std::vector<int> data;
    if (read_count_and_ints_from_file(path, data)) {
      return data;
    }
    std::cout << "Не удалось прочитать файл. Попробуйте снова.\n";
  }
}

std::vector<int> acquire_int_data(const std::string& title, InputMode mode) {
  if (mode == InputMode::kKeyboard) {
    return read_ints_keyboard(title);
  }
  if (mode == InputMode::kRandom) {
    return read_ints_random(title);
  }
  return read_ints_file(title);
}

void print_int_vector(const std::vector<int>& values, const std::string& title) {
  std::cout << title;
  for (int value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}

void print_string_vector(const std::vector<std::string>& values,
                       const std::string& title) {
  std::cout << title;
  for (const std::string& value : values) {
    std::cout << value << ' ';
  }
  std::cout << '\n';
}

std::vector<int> make_distinct(const std::vector<int>& data) {
  std::unordered_set<int> seen;
  std::vector<int> unique;
  for (int value : data) {
    if (seen.insert(value).second) {
      unique.push_back(value);
    }
  }
  return unique;
}

bool read_two_sequences_from_file(const std::string& file_path,
                              std::vector<int>& first,
                              std::vector<int>& second) {
  std::ifstream input(file_path);
  if (!input.is_open()) {
    return false;
  }

  int first_count = 0;
  if (!(input >> first_count) || first_count < 0) {
    return false;
  }
  first.clear();
  for (int i = 0; i < first_count; ++i) {
    int value = 0;
    if (!(input >> value)) {
      return false;
    }
    first.push_back(value);
  }

  int second_count = 0;
  if (!(input >> second_count) || second_count < 0) {
    return false;
  }
  second.clear();
  for (int i = 0; i < second_count; ++i) {
    int value = 0;
    if (!(input >> value)) {
      return false;
    }
    second.push_back(value);
  }

  return true;
}

void acquire_two_int_sets(InputMode mode,
                       const std::string& first_title,
                       const std::string& second_title,
                       std::vector<int>& first,
                       std::vector<int>& second) {
  if (mode == InputMode::kFile) {
    while (true) {
      std::cout << "Формат файла: K, K чисел, затем N, N чисел.\n";
      const std::string path = read_line("Введите путь к файлу: ");
      if (read_two_sequences_from_file(path, first, second)) {
        return;
      }
      std::cout << "Ошибка чтения файла.\n";
    }
  }

  first = acquire_int_data(first_title, mode);
  second = acquire_int_data(second_title, mode);
}

std::vector<std::string> read_names_keyboard() {
  const int count = read_int("Введите количество детей: ");
  std::vector<std::string> names;
  for (int i = 0; i < count; ++i) {
    names.push_back(read_line("Имя [" + std::to_string(i) + "]: "));
  }
  return names;
}

std::vector<std::string> read_names_random() {
  const int count = read_int("Введите количество детей: ");
  std::vector<std::string> names;
  names.reserve(static_cast<size_t>(count));
  const std::vector<std::string> kBaseNames = {
      "Первый",   "Второй", "Третий", "Четвертый", "Пятый",
      "Шестой",   "Седьмой", "Восьмой", "Девятый", "Десятый"};
  for (int i = 1; i <= count; ++i) {
    if (i <= static_cast<int>(kBaseNames.size())) {
      names.push_back(kBaseNames[i - 1]);
    } else {
      names.push_back("Ребенок " + std::to_string(i));
    }
  }

  std::cout << "Сгенерированные имена: ";
  for (const std::string& name : names) {
    std::cout << name << ' ';
  }
  std::cout << '\n';
  return names;
}

bool read_text2_input_file(const std::string& file_path,
                           int& rhyme_count,
                           std::vector<std::string>& names) {
  // читаем количество слов и список детей из файла
  std::ifstream input(file_path);
  if (!input.is_open()) {
    return false;
  }
  if (!(input >> rhyme_count)) {
    return false;
  }
  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  names.clear();
  std::string name;
  while (std::getline(input, name)) {
    if (!name.empty()) {
      names.push_back(name);
    }
  }
  return true;
}

struct Text2Step {
  std::string starts_from;
  std::string stopped_on;
  std::vector<std::string> list_after_removal;
};

std::vector<Text2Step> build_text2_steps(const std::vector<std::string>& names,
                                         int rhyme_count) {
  // строим шаги выбывания в том же порядке, что и основной алгоритм
  std::vector<Text2Step> steps;
  if (rhyme_count <= 0 || names.empty()) {
    return steps;
  }

  std::vector<std::string> circle = names;
  int start_index = 0;
  bool clockwise = true;

  while (!circle.empty()) {
    const std::string starts_from = circle[start_index];
    int eliminated_index = start_index;
    for (int i = 1; i < rhyme_count; ++i) {
      if (clockwise) {
        eliminated_index = (eliminated_index + 1) % static_cast<int>(circle.size());
      } else {
        eliminated_index =
            (eliminated_index - 1 + static_cast<int>(circle.size())) %
            static_cast<int>(circle.size());
      }
    }

    const std::string eliminated_name = circle[eliminated_index];

    if (circle.size() == 1) {
      steps.push_back({starts_from, eliminated_name, {}});
      circle.clear();
      break;
    }

    const int old_size = static_cast<int>(circle.size());
    const int old_prev = (eliminated_index - 1 + old_size) % old_size;
    const int old_next = (eliminated_index + 1) % old_size;
    int next_start_old = clockwise ? old_prev : old_next;

    circle.erase(circle.begin() + eliminated_index);
    steps.push_back({starts_from, eliminated_name, circle});
    if (next_start_old > eliminated_index) {
      --next_start_old;
    }
    start_index = next_start_old;
    clockwise = !clockwise;
  }

  return steps;
}

std::vector<int> t_list_to_vector(const TList& list) {
  // собираем значения из tlist по next
  std::vector<int> values;
  for (DoublyNode* node = list.first; node != nullptr; node = node->next) {
    values.push_back(node->value);
  }
  return values;
}

void print_node_state(const std::string& name, const DoublyNode* node) {
  // печатаем адрес и значение узла
  if (node == nullptr) {
    std::cout << name << ": nullptr\n";
    return;
  }
  std::cout << name << ": value = " << node->value
            << ", address = " << static_cast<const void*>(node) << '\n';
}

std::vector<int> t_list_b_to_vector(const TListB& list) {
  // собираем значения из списка с барьером
  std::vector<int> values;
  if (list.barrier == nullptr) {
    return values;
  }
  for (DoublyNode* node = list.barrier->next; node != list.barrier;
       node = node->next) {
    values.push_back(node->value);
  }
  return values;
}

}  // namespace

void run_task_1() {
  const std::string kOutputPath = "listwork67_output.txt";
  const InputMode mode = ask_input_mode();
  std::vector<int> values = acquire_int_data("ListWork67", mode);
  if (values.empty()) {
    std::cout << "Список пуст, задание не выполнено.\n";
    return;
  }

  CircularSinglyList ring;
  for (int value : values) {
    ring.push_back(value);
  }
  print_int_vector(ring.to_vector(), "Исходный список: ");

  const bool show_new_list_iterations =
      ask_yes_no("Показать итерации формирования нового списка");
  if (show_new_list_iterations) {
    CircularSinglyList preview(ring);
    const std::vector<int> order = preview.collect_step_two_and_erase();
    std::vector<int> prefix;
    for (size_t i = 0; i < order.size(); ++i) {
      prefix.push_back(order[i]);
      print_int_vector(prefix, "Шаг " + std::to_string(i + 1) + ": ");
    }
  }

  ring.export_step_two_and_erase(kOutputPath);
  std::cout << "Результат записан в: " << kOutputPath << '\n';
}

void run_task_2() {
  const InputMode mode = ask_input_mode();
  std::vector<int> values = acquire_int_data("ListWork41", mode);
  values = make_distinct(values);

  if (values.size() < 2) {
    std::cout << "Нужно минимум 2 различных элемента.\n";
    return;
  }

  DoublyLinearList list;
  for (int value : values) {
    list.push_back(value);
  }

  int min_value = values[0];
  int max_value = values[0];
  for (size_t i = 1; i < values.size(); ++i) {
    if (values[i] < min_value) {
      min_value = values[i];
    }
    if (values[i] > max_value) {
      max_value = values[i];
    }
  }

  print_int_vector(list.to_vector(), "Исходный список: ");
  std::cout << "min = " << min_value << '\n';
  std::cout << "max = " << max_value << '\n';
  print_int_vector(extract_between_min_max(list), "Элементы между min и max: ");
}

void run_task_3() {
  const InputMode mode = ask_input_mode();
  std::vector<int> initial_values;
  std::vector<int> added_values;
  acquire_two_int_sets(mode, "начального списка (ListWork44)",
                    "добавляемого набора (ListWork44)", initial_values,
                    added_values);

  TList list;
  init_t_list(list);
  print_int_vector(initial_values, "Исходный список: ");
  print_int_vector(added_values, "Добавляемый набор: ");

  for (int value : initial_values) {
    insert_last(list, value);
  }
  for (int value : added_values) {
    insert_last(list, value);
  }

  print_int_vector(t_list_to_vector(list), "Итоговый список: ");
  print_node_state("first", list.first);
  print_node_state("last", list.last);
  print_node_state("current", list.current);

  clear_t_list(list);
}

void run_task_4() {
  const InputMode mode = ask_input_mode();
  std::vector<int> initial_values;
  std::vector<int> added_values;
  acquire_two_int_sets(mode, "начального списка (ListWork47)",
                    "добавляемого набора (ListWork47)", initial_values,
                    added_values);

  TListB list;
  init_t_list_b(list);
  print_int_vector(initial_values, "Исходный список: ");
  print_int_vector(added_values, "Добавляемый набор: ");

  for (int value : initial_values) {
    lb_insert_last(list, value);
  }
  for (int value : added_values) {
    lb_insert_last(list, value);
  }

  print_int_vector(t_list_b_to_vector(list), "Итоговый список: ");
  print_node_state("current", list.current);

  clear_t_list_b(list);
}

void run_task_5() {
  const std::string kOutputPath = "text2_output.txt";
  const InputMode mode = ask_input_mode();
  int rhyme_count = 0;
  std::vector<std::string> names;
  if (mode == InputMode::kFile) {
    const std::string input_path = read_line("Входной файл Text2: ");
    if (!read_text2_input_file(input_path, rhyme_count, names)) {
      std::cout << "Не удалось обработать файл.\n";
      return;
    }
  } else {
    rhyme_count = read_int("Введите количество слов считалки: ");
    names = (mode == InputMode::kKeyboard) ? read_names_keyboard()
                                           : read_names_random();
  }

  if (names.empty() || rhyme_count <= 0) {
    std::cout << "Недостаточно данных для моделирования.\n";
    return;
  }

  print_string_vector(names, "Исходный список: ");

  KidsCircle kids;
  for (const std::string& name : names) {
    kids.push_back(name);
  }
  const std::vector<Text2Step> steps = build_text2_steps(names, rhyme_count);
  for (size_t i = 0; i < steps.size(); ++i) {
    std::cout << "Шаг " << (i + 1) << '\n';
    std::cout << "с кого начинается считалка: " << steps[i].starts_from << '\n';
    std::cout << "на ком остановилась: " << steps[i].stopped_on << '\n';
    if (steps[i].list_after_removal.empty()) {
      std::cout << "список после удаления: (пусто)\n";
    } else {
      print_string_vector(steps[i].list_after_removal,
                          "список после удаления: ");
    }
  }

  const std::vector<std::string> order = kids.elimination_order(rhyme_count);
  print_string_vector(order, "Итоговый список: ");
  std::ofstream output(kOutputPath);
  if (!output.is_open()) {
    std::cout << "Не удалось открыть выходной файл.\n";
    return;
  }
  for (const std::string& name : order) {
    output << name << '\n';
  }
  std::cout << "Результат записан в: " << kOutputPath << '\n';
}

void run_task_6() {
  const std::string kOutput67 = "listwork67_output.txt";
  const std::string kOutputText2 = "text2_output.txt";

  std::cout << "\nДЕМОНСТРАЦИЯ LISTWORK67\n";
  CircularSinglyList ring;
  ring.push_back(10);
  ring.push_back(20);
  ring.push_back(30);
  ring.push_back(40);
  ring.push_back(50);
  print_int_vector(ring.to_vector(), "создан объект и добавлены элементы: ");
  std::cout << "поиск 30: " << (ring.contains(30) ? "найден" : "не найден")
            << '\n';
  std::cout << "удаление 20: " << (ring.remove_value(20) ? "успех" : "нет")
            << '\n';
  print_int_vector(ring.to_vector(), "после удаления: ");
  CircularSinglyList ring_for_solution(ring);
  ring_for_solution.export_step_two_and_erase(kOutput67);
  std::cout << "решение варианта записано в: " << kOutput67 << '\n';

  std::cout << "\nДЕМОНСТРАЦИЯ LISTWORK41\n";
  DoublyLinearList list41;
  list41.push_back(7);
  list41.push_back(1);
  list41.push_back(4);
  list41.push_back(9);
  list41.push_back(6);
  print_int_vector(list41.to_vector(), "создан объект и добавлены элементы: ");
  std::cout << "поиск 4: " << (list41.contains(4) ? "найден" : "не найден")
            << '\n';
  std::cout << "удаление 6: " << (list41.remove_value(6) ? "успех" : "нет")
            << '\n';
  print_int_vector(list41.to_vector(), "после удаления: ");
  print_int_vector(extract_between_min_max(list41),
                   "решение варианта (между min и max): ");

  std::cout << "\nДЕМОНСТРАЦИЯ LISTWORK44\n";
  TList list44;
  init_t_list(list44);
  std::vector<int> initial44 = {100, 200, 300};
  std::vector<int> add44 = {11, 22, 33};
  print_int_vector(initial44, "исходный список: ");
  print_int_vector(add44, "добавляемый набор: ");
  for (int value : initial44) {
    insert_last(list44, value);
  }
  for (int value : add44) {
    insert_last(list44, value);
  }
  print_int_vector(t_list_to_vector(list44), "итоговый список: ");
  print_node_state("first", list44.first);
  print_node_state("last", list44.last);
  print_node_state("current", list44.current);
  clear_t_list(list44);

  std::cout << "\nДЕМОНСТРАЦИЯ LISTWORK47\n";
  TListB list47;
  init_t_list_b(list47);
  std::vector<int> initial47 = {5, 6, 7};
  std::vector<int> add47 = {77, 88, 99};
  print_int_vector(initial47, "исходный список: ");
  print_int_vector(add47, "добавляемый набор: ");
  for (int value : initial47) {
    lb_insert_last(list47, value);
  }
  for (int value : add47) {
    lb_insert_last(list47, value);
  }
  print_int_vector(t_list_b_to_vector(list47), "итоговый список: ");
  print_node_state("current", list47.current);
  clear_t_list_b(list47);

  std::cout << "\nДЕМОНСТРАЦИЯ TEXT2\n";
  KidsCircle kids;
  const int kRhymeWordCount = 3;
  const std::string kStartChild = "Анна";
  std::vector<std::string> active_names = {"Анна", "Борис", "Вика", "Глеб", "Даша"};
  kids.push_back("Анна");
  kids.push_back("Борис");
  kids.push_back("Вика");
  kids.push_back("Глеб");
  kids.push_back("Даша");
  print_string_vector(
      std::vector<std::string>{"Анна", "Борис", "Вика", "Глеб", "Даша"},
      "создан объект и добавлены дети: ");
  std::cout << "кол-во слов в считалке: " << kRhymeWordCount << '\n';
  std::cout << "с кого начинается считалка: " << kStartChild << '\n';
  std::cout << "поиск Борис: "
            << (kids.contains("Борис") ? "найден" : "не найден") << '\n';
  std::cout << "удаление Глеб: "
            << (kids.remove_by_name("Глеб") ? "успех" : "нет") << '\n';
  active_names.erase(
      std::remove(active_names.begin(), active_names.end(), "Глеб"),
      active_names.end());

  const std::vector<Text2Step> steps =
      build_text2_steps(active_names, kRhymeWordCount);
  if (!steps.empty()) {
    std::cout << "на ком остановилась: " << steps[0].stopped_on << '\n';
    std::cout << "кого удаляет: " << steps[0].stopped_on << '\n';
    if (steps[0].list_after_removal.empty()) {
      std::cout << "список после удаления: (пусто)\n";
    } else {
      print_string_vector(steps[0].list_after_removal, "список после удаления: ");
    }
  }

  const std::vector<std::string> order = kids.elimination_order(kRhymeWordCount);
  print_string_vector(order, "решение варианта (порядок выбывания): ");
  std::ofstream output(kOutputText2);
  if (output.is_open()) {
    for (const std::string& name : order) {
      output << name << '\n';
    }
    std::cout << "результат записан в: " << kOutputText2 << '\n';
  } else {
    std::cout << "не удалось открыть файл: " << kOutputText2 << '\n';
  }
}

}
