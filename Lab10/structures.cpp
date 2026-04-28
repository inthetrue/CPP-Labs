#include "structures.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

Stack::Stack() : top_(nullptr) {}

Stack::Stack(const Stack& other) : top_(nullptr) {
  copy_from(other);
}

Stack& Stack::operator=(const Stack& other) {
  if (this != &other) {
    clear();
    copy_from(other);
  }
  return *this;
}

Stack::~Stack() {
  clear();
}

void Stack::copy_from(const Stack& other) {
  std::vector<int> values;
  for (TNode* cur = other.top_; cur != nullptr; cur = cur->Next) {
    values.push_back(cur->Data);
  }

  for (std::size_t i = values.size(); i > 0; --i) {
    push(values[i - 1]);
  }
}

void Stack::clear() {
  while (top_ != nullptr) {
    TNode* to_delete = top_;
    top_ = top_->Next;
    delete to_delete;
  }
}

void Stack::push(int value) {
  top_ = new TNode(value, top_);
}

bool Stack::pop(int& removed_value) {
  if (top_ == nullptr) {
    return false;
  }
  TNode* to_delete = top_;
  removed_value = to_delete->Data;
  top_ = top_->Next;
  delete to_delete;
  return true;
}

bool Stack::contains(int value) const {
  for (TNode* cur = top_; cur != nullptr; cur = cur->Next) {
    if (cur->Data == value) {
      return true;
    }
  }
  return false;
}

bool Stack::is_empty() const {
  return top_ == nullptr;
}

const void* Stack::top_address() const {
  return static_cast<const void*>(top_);
}

int Stack::top_value() const {
  return top_->Data;
}

void Stack::print_values() const {
  if (top_ == nullptr) {
    std::cout << "(пусто)\n";
    return;
  }

  TNode* cur = top_;
  while (cur != nullptr) {
    std::cout << cur->Data;
    if (cur->Next != nullptr) {
      std::cout << ' ';
    }
    cur = cur->Next;
  }
  std::cout << '\n';
}

Queue::Queue() : head_(nullptr), tail_(nullptr) {}

Queue::Queue(const Queue& other) : head_(nullptr), tail_(nullptr) {
  copy_from(other);
}

Queue& Queue::operator=(const Queue& other) {
  if (this != &other) {
    clear();
    copy_from(other);
  }
  return *this;
}

Queue::~Queue() {
  clear();
}

void Queue::copy_from(const Queue& other) {
  for (TNode* cur = other.head_; cur != nullptr; cur = cur->Next) {
    enqueue(cur->Data);
  }
}

void Queue::clear() {
  while (head_ != nullptr) {
    TNode* to_delete = head_;
    head_ = head_->Next;
    delete to_delete;
  }
  tail_ = nullptr;
}

void Queue::enqueue(int value) {
  TNode* node = new TNode(value);
  if (tail_ == nullptr) {
    head_ = tail_ = node;
  } else {
    tail_->Next = node;
    tail_ = node;
  }
} // добавляем элементы в tail

bool Queue::dequeue(int& removed_value) {
  if (head_ == nullptr) {
    return false;
  }
  TNode* to_delete = head_;
  removed_value = to_delete->Data;
  head_ = head_->Next;
  if (head_ == nullptr) {
    tail_ = nullptr;
  }
  delete to_delete;
  return true;
} // удаляем элементы из head

bool Queue::contains(int value) const {
  for (TNode* cur = head_; cur != nullptr; cur = cur->Next) {
    if (cur->Data == value) {
      return true;
    }
  }
  return false;
}

bool Queue::is_empty() const {
  return head_ == nullptr;
}

bool Queue::front(int& value) const {
  if (head_ == nullptr) {
    return false;
  }
  value = head_->Data;
  return true;
}

bool Queue::back(int& value) const {
  if (tail_ == nullptr) {
    return false;
  }
  value = tail_->Data;
  return true;
}

// Для Dynamic23
void Queue::move_until_even(Queue& other) {
  while (head_ != nullptr && (head_->Data % 2 != 0)) {
    TNode* moved = head_;
    head_ = head_->Next;
    if (head_ == nullptr) {
      tail_ = nullptr;
    }

    moved->Next = nullptr;
    if (other.tail_ == nullptr) {
      other.head_ = other.tail_ = moved;
    } else {
      other.tail_->Next = moved;
      other.tail_ = moved;
    }
  }
}

void Queue::print_values() const {
  if (head_ == nullptr) {
    std::cout << "(пусто)\n";
    return;
  }

  TNode* cur = head_;
  while (cur != nullptr) {
    std::cout << cur->Data;
    if (cur->Next != nullptr) {
      std::cout << ' ';
    }
    cur = cur->Next;
  }
  std::cout << '\n';
}

const void* Queue::head_address() const {
  return static_cast<const void*>(head_);
}

const void* Queue::tail_address() const {
  return static_cast<const void*>(tail_);
}

LinkedList::LinkedList() : head_(nullptr), tail_(nullptr) {}

LinkedList::LinkedList(const LinkedList& other)
    : head_(nullptr), tail_(nullptr) {
  copy_from(other);
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
  if (this != &other) {
    clear();
    copy_from(other);
  }
  return *this;
}

LinkedList::~LinkedList() {
  clear();
}

void LinkedList::copy_from(const LinkedList& other) {
  for (Node* cur = other.head_; cur != nullptr; cur = cur->next) {
    push_back(cur->value);
  }
}

void LinkedList::clear() {
  while (head_ != nullptr) {
    Node* to_delete = head_;
    head_ = head_->next;
    delete to_delete;
  }
  tail_ = nullptr;
}

void LinkedList::push_back(int value) {
  Node* node = new Node(value);
  if (tail_ == nullptr) {
    head_ = tail_ = node;
  } else {
    tail_->next = node;
    tail_ = node;
  }
}

bool LinkedList::remove_first(int value) {
  Node* prev = nullptr;
  Node* cur = head_;

  while (cur != nullptr) {
    if (cur->value == value) {
      if (prev == nullptr) {
        head_ = cur->next;
      } else {
        prev->next = cur->next;
      }

      if (cur == tail_) {
        tail_ = prev;
      }

      delete cur;
      return true;
    }
    prev = cur;
    cur = cur->next;
  }
  return false;
}

bool LinkedList::contains(int value) const {
  for (Node* cur = head_; cur != nullptr; cur = cur->next) {
    if (cur->value == value) {
      return true;
    }
  }
  return false;
}

bool LinkedList::is_empty() const {
  return head_ == nullptr;
}

const void* LinkedList::third_address() const {
  Node* cur = head_;
  for (int i = 0; i < 2 && cur != nullptr; ++i) {
    cur = cur->next;
  }
  return static_cast<const void*>(cur);
}

int LinkedList::third_value() const {
  Node* cur = head_;
  for (int i = 0; i < 2 && cur != nullptr; ++i) {
    cur = cur->next;
  }
  return cur->value;
}

void LinkedList::insert_after_every_third(int value) {
  Node* cur = head_;
  int index = 0;

  while (cur != nullptr) {
    ++index;
    if (index % 3 == 0) {
      Node* inserted = new Node(value);
      inserted->next = cur->next;
      cur->next = inserted;
      if (tail_ == cur) {
        tail_ = inserted;
      }
      cur = inserted->next;
    } else {
      cur = cur->next;
    }
  }
}

LinkedList LinkedList::copy_with_inserted_sorted(int value) const {
  LinkedList result(*this); // создаем копию текущего списка

  Node* node = new Node(value);
  if (result.head_ == nullptr || value <= result.head_->value) {
    node->next = result.head_;
    result.head_ = node;
    if (result.tail_ == nullptr) { // если список был пустой
      result.tail_ = node;
    }
    return result;
  }

  Node* cur = result.head_;
  while (cur->next != nullptr && cur->next->value < value) {
    cur = cur->next;
  } // двигаемся пока след элемент меньше value

  node->next = cur->next;
  cur->next = node;
  if (node->next == nullptr) {
    result.tail_ = node;
  }
  return result;
}

void LinkedList::print_values() const {
  if (head_ == nullptr) {
    std::cout << "(empty)\n";
    return;
  }

  Node* cur = head_;
  while (cur != nullptr) {
    std::cout << cur->value;
    if (cur->next != nullptr) {
      std::cout << ' ';
    }
    cur = cur->next;
  }
  std::cout << '\n';
}

const void* LinkedList::head_address() const {
  return static_cast<const void*>(head_);
}

const void* LinkedList::tail_address() const {
  return static_cast<const void*>(tail_);
}

Stack build_stack_from_numbers(const std::vector<int>& numbers) {
  Stack stack;
  for (int value : numbers) {
    stack.push(value);
  }
  return stack;
}

namespace {

enum class InputMode {
  kKeyboard = 1,
  kFile = 2,
  kRandom = 3,
};

void print_ptr_or_null(const void* ptr) {
  if (ptr == nullptr) {
    std::cout << "nullptr";
  } else {
    std::cout << ptr;
  }
}

bool read_int(const std::string& prompt, int& value) {
  std::cout << prompt;
  std::cin >> value;
  if (std::cin) {
    return true;
  }

  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return false;
}

InputMode read_input_mode(const std::string& label) {
  while (true) {
    std::cout << "\nВыбор ввода для " << label << ":\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Из файла\n";
    std::cout << "3. Рандомно (с диапазоном)\n";
    int choice = 0;
    if (!read_int("Введите 1/2/3: ", choice)) {
      std::cout << "Некорректный ввод.\n";
      continue;
    }

    if (choice == static_cast<int>(InputMode::kKeyboard)) {
      return InputMode::kKeyboard;
    }
    if (choice == static_cast<int>(InputMode::kFile)) {
      return InputMode::kFile;
    }
    if (choice == static_cast<int>(InputMode::kRandom)) {
      return InputMode::kRandom;
    }
    std::cout << "Нет такого варианта.\n";
  }
}

bool read_count_and_values_keyboard(
    const std::string& label, int min_count, std::vector<int>& values) {
  int count = 0;
  if (!read_int("Введите количество элементов для " + label + ": ", count) ||
      count < min_count) {
    std::cout << "Некорректное количество.\n";
    return false;
  }

  values.assign(count, 0);
  std::cout << "Введите " << count << " чисел: ";
  for (int i = 0; i < count; ++i) {
    std::cin >> values[i];
    if (!std::cin) {
      std::cout << "Некорректный ввод числа.\n";
      return false;
    }
  }
  return true;
}

bool read_count_and_values_file(
    const std::string& label, int min_count, std::vector<int>& values) {
  std::cout << "Введите путь к файлу для " << label << ": ";
  std::string path;
  std::cin >> path;

  std::ifstream input(path);
  if (!input.is_open()) {
    std::cout << "Не удалось открыть файл.\n";
    return false;
  }

  int count = 0;
  input >> count;
  if (!input || count < min_count) {
    std::cout << "Некорректное количество в файле.\n";
    return false;
  }

  values.assign(count, 0); // делаем вектор values длиной count и заполняем все элементы 0
  for (int i = 0; i < count; ++i) {
    input >> values[i];
    if (!input) {
      std::cout << "В файле недостаточно чисел.\n";
      return false;
    }
  }
  return true;
}

bool read_count_and_values_random(
    const std::string& label, int min_count, std::vector<int>& values) {
  int count = 0;
  if (!read_int("Введите количество элементов для " + label + ": ", count) ||
      count < min_count) {
    std::cout << "Некорректное количество.\n";
    return false;
  }

  int min_value = 0;
  int max_value = 0;
  if (!read_int("Введите минимум диапазона: ", min_value) ||
      !read_int("Введите максимум диапазона: ", max_value)) {
    std::cout << "Некорректный диапазон.\n";
    return false;
  }
  if (min_value > max_value) {
    std::swap(min_value, max_value);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(min_value, max_value);

  values.assign(count, 0);
  for (int i = 0; i < count; ++i) {
    values[i] = dist(gen);
  }

  std::cout << "Сгенерировано: ";
  for (int i = 0; i < count; ++i) {
    std::cout << values[i] << (i + 1 == count ? '\n' : ' ');
  }
  return true;
}

bool read_values_with_mode(
    const std::string& label, int min_count, std::vector<int>& values) {
  InputMode mode = read_input_mode(label);
  if (mode == InputMode::kKeyboard) {
    return read_count_and_values_keyboard(label, min_count, values);
  }
  if (mode == InputMode::kFile) {
    return read_count_and_values_file(label, min_count, values);
  }
  return read_count_and_values_random(label, min_count, values);
}

bool read_single_int_with_mode(const std::string& label, int& value) {
  InputMode mode = read_input_mode(label);
  if (mode == InputMode::kKeyboard) {
    return read_int("Введите значение для " + label + ": ", value);
  }

  if (mode == InputMode::kFile) {
    std::cout << "Введите путь к файлу для " << label << ": ";
    std::string path;
    std::cin >> path;
    std::ifstream input(path);
    if (!input.is_open()) {
      std::cout << "Не удалось открыть файл.\n";
      return false;
    }
    input >> value;
    if (!input) {
      std::cout << "В файле нет корректного числа.\n";
      return false;
    }
    return true;
  }

  int min_value = 0;
  int max_value = 0;
  if (!read_int("Введите минимум диапазона: ", min_value) ||
      !read_int("Введите максимум диапазона: ", max_value)) {
    std::cout << "Некорректный диапазон.\n";
    return false;
  }
  if (min_value > max_value) {
    std::swap(min_value, max_value);
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(min_value, max_value);
  value = dist(gen);
  std::cout << "Сгенерировано значение: " << value << '\n';
  return true;
}

bool is_sorted_vector(const std::vector<int>& values) {
  for (std::size_t i = 1; i < values.size(); ++i) {
    if (values[i] < values[i - 1]) {
      return false;
    }
  }
  return true;
}

}  // namespace

void run_task_dynamic4() {
  std::cout << "\n[Dynamic4]\n";

  std::vector<int> values;
  if (!read_values_with_mode("стека", 1, values)) {
    std::cout << "Не удалось получить входные данные.\n";
    return;
  }

  Stack stack = build_stack_from_numbers(values);

  std::cout << "Стек: ";
  stack.print_values();
  std::cout << "Указатель на вершину стека: ";
  print_ptr_or_null(stack.top_address());
  std::cout << '\n';
  std::cout << "Значение вершины: " << stack.top_value() << "\n";
}

void run_task_dynamic23() {
  std::cout << "\n[Dynamic23]\n";

  std::vector<int> first_values;
  if (!read_values_with_mode("первой очереди", 1, first_values)) {
    std::cout << "Не удалось получить первую очередь.\n";
    return;
  }

  std::vector<int> second_values;
  if (!read_values_with_mode("второй очереди", 1, second_values)) {
    std::cout << "Не удалось получить вторую очередь.\n";
    return;
  }

  Queue queue1;
  Queue queue2;
  for (int value : first_values) {
    queue1.enqueue(value);
  }
  for (int value : second_values) {
    queue2.enqueue(value);
  }

  queue1.move_until_even(queue2);

  std::cout << "Первая очередь после переноса: ";
  queue1.print_values();
  std::cout << "Вторая очередь после переноса: ";
  queue2.print_values();

  std::cout << "Новые адреса первой очереди (P1, P2): ";
  print_ptr_or_null(queue1.head_address());
  std::cout << ' ';
  print_ptr_or_null(queue1.tail_address());
  std::cout << '\n';

  std::cout << "Новые адреса второй очереди (P3, P4): ";
  print_ptr_or_null(queue2.head_address());
  std::cout << ' ';
  print_ptr_or_null(queue2.tail_address());
  std::cout << '\n';

  int first_head_value = 0;
  int first_tail_value = 0;
  std::cout << "Значения по адресам первой очереди (P1, P2): ";
  if (queue1.front(first_head_value)) {
    std::cout << first_head_value << ' ';
  } else {
    std::cout << "nullptr ";
  }
  if (queue1.back(first_tail_value)) {
    std::cout << first_tail_value;
  } else {
    std::cout << "nullptr";
  }
  std::cout << '\n';

  int second_head_value = 0;
  int second_tail_value = 0;
  std::cout << "Значения по адресам второй очереди (P3, P4): ";
  if (queue2.front(second_head_value)) {
    std::cout << second_head_value << ' ';
  } else {
    std::cout << "nullptr ";
  }
  if (queue2.back(second_tail_value)) {
    std::cout << second_tail_value;
  } else {
    std::cout << "nullptr";
  }
  std::cout << '\n';
}

void run_task_list_work2() {
  std::cout << "\n[ListWork2]\n";

  std::vector<int> values;
  if (!read_values_with_mode("односвязного списка", 3, values)) {
    std::cout << "Не удалось получить список.\n";
    return;
  }

  LinkedList list;
  for (int value : values) {
    list.push_back(value);
  }

  std::cout << "Указатель на третий элемент P3: ";
  print_ptr_or_null(list.third_address());
  std::cout << '\n';
  std::cout << "Значение третьего элемента: " << list.third_value() << '\n';
}

void run_task_list_work23() {
  std::cout << "\n[ListWork23]\n";

  std::vector<int> values;
  if (!read_values_with_mode("односвязного списка", 1, values)) {
    std::cout << "Не удалось получить список.\n";
    return;
  }

  int m = 0;
  if (!read_single_int_with_mode("M", m)) {
    std::cout << "Не удалось получить значение M.\n";
    return;
  }

  LinkedList list;
  for (int value : values) {
    list.push_back(value);
  }
  list.insert_after_every_third(m);

  std::cout << "Список после вставки M: ";
  list.print_values();
  std::cout << "Указатель на последний элемент P2: ";
  print_ptr_or_null(list.tail_address());
  std::cout << '\n';
}

void run_task_list_work60() {
  std::cout << "\n[ListWork60]\n";

  std::vector<int> values;
  if (!read_values_with_mode("упорядоченного списка", 1, values)) {
    std::cout << "Не удалось получить список.\n";
    return;
  }

  if (!is_sorted_vector(values)) {
    std::sort(values.begin(), values.end());
    std::cout << "Внимание: список отсортирован автоматически.\n";
  }

  int m = 0;
  if (!read_single_int_with_mode("M", m)) {
    std::cout << "Не удалось получить значение M.\n";
    return;
  }

  LinkedList list;
  for (int value : values) {
    list.push_back(value);
  }

  LinkedList copy = list.copy_with_inserted_sorted(m);
  std::cout << "Новый список после вставки M: ";
  copy.print_values();
  std::cout << "Указатель на первый элемент нового списка P2: ";
  print_ptr_or_null(copy.head_address());
  std::cout << '\n';
}

void run_demo_operations() {
  std::cout << "\n[Демонстрация операций]\n";

  Stack stack;
  std::cout << "\nStack:\n";
  std::cout << "  Добавление: push(10), push(20)\n";
  stack.push(10);
  stack.push(20);
  int removed_value = 0;
  bool popped = stack.pop(removed_value);
  std::cout << "  Удаление: pop() -> "
            << (popped ? std::to_string(removed_value) : std::string("empty"))
            << '\n';
  std::cout << "  Поиск: contains(10) -> "
            << (stack.contains(10) ? "true" : "false") << '\n';

  Queue queue;
  std::cout << "\nQueue:\n";
  std::cout << "  Добавление: enqueue(1), enqueue(2)\n";
  queue.enqueue(1);
  queue.enqueue(2);
  bool dequeued = queue.dequeue(removed_value);
  std::cout << "  Удаление: dequeue() -> "
            << (dequeued ? std::to_string(removed_value)
                         : std::string("empty"))
            << '\n';
  std::cout << "  Поиск: contains(2) -> "
            << (queue.contains(2) ? "true" : "false") << '\n';

  LinkedList list;
  std::cout << "\nList:\n";
  std::cout << "  Добавление: push_back(5), push_back(7), push_back(9)\n";
  list.push_back(5);
  list.push_back(7);
  list.push_back(9);
  bool deleted = list.remove_first(7);
  std::cout << "  Удаление: remove_first(7) -> "
            << (deleted ? "true" : "false") << '\n';
  std::cout << "  Поиск: contains(9) -> "
            << (list.contains(9) ? "true" : "false") << '\n';
}
