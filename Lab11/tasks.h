#ifndef LAB11_TASKS_H_
#define LAB11_TASKS_H_

#include <string>
#include <vector>

namespace lab11 {

class CircularNode {
 public:
  // explicit нужен, чтобы запретить неявное преобразование int -> CircularNode
  // конструктор узла с заданным значением
  explicit CircularNode(int value);

  int value;
  CircularNode* next;
};

class CircularSinglyList {
 public:
  // конструктор пустого односвязного циклического списка
  CircularSinglyList();
  // конструктор копирования односвязного циклического списка
  CircularSinglyList(const CircularSinglyList& other);
  // деструктор односвязного циклического списка
  ~CircularSinglyList();

  void push_back(int value);
  bool remove_value(int value);
  bool contains(int value) const;
  bool empty() const;
  int size() const;
  std::vector<int> to_vector() const;
  std::vector<int> collect_step_two_and_erase();

  // ListWork67: выводит элементы с шагом 2 и удаляет их по одному.
  void export_step_two_and_erase(const std::string& output_file_path);

 private:
  void clear();

  CircularNode* head_;
  int size_;
};

class DoublyNode {
 public:
  // explicit нужен, чтобы запретить неявное преобразование int -> DoublyNode
  // конструктор узла с заданным значением
  explicit DoublyNode(int value);

  int value;
  DoublyNode* prev;
  DoublyNode* next;
};

class DoublyLinearList {
 public:
  // конструктор пустого двусвязного списка
  DoublyLinearList();
  // конструктор копирования двусвязного списка
  DoublyLinearList(const DoublyLinearList& other);
  // деструктор двусвязного списка
  ~DoublyLinearList();

  void push_back(int value);
  bool remove_value(int value);
  bool contains(int value) const;
  bool empty() const;
  std::vector<int> to_vector() const;

  const DoublyNode* head() const;

 private:
  void clear();

  DoublyNode* head_;
  DoublyNode* tail_;
};

// ListWork41: вернуть значения строго между min и max в исходном порядке.
std::vector<int> extract_between_min_max(const DoublyLinearList& list);

class TList {
 public:
  DoublyNode* first;
  DoublyNode* last;
  DoublyNode* current;
};

// процедура инициализации обычного двусвязного списка
void init_t_list(TList& list);
// процедура очистки обычного двусвязного списка
void clear_t_list(TList& list);

// процедура listwork44: добавить в конец и сделать добавленный узел текущим
void insert_last(TList& list, int data);

class TListB {
 public:
  DoublyNode* barrier;
  DoublyNode* current;
};

// процедура инициализации двусвязного списка с барьером
void init_t_list_b(TListB& list);
// процедура очистки двусвязного списка с барьером
void clear_t_list_b(TListB& list);

// процедура listwork47: добавить перед барьером и сделать добавленный узел текущим
void lb_insert_last(TListB& list, int data);

class ChildNode {
 public:
  // explicit нужен, чтобы запретить неявное преобразование string -> ChildNode
  // конструктор узла с заданным именем
  explicit ChildNode(const std::string& name);

  std::string name;
  ChildNode* prev;
  ChildNode* next;
};

class KidsCircle {
 public:
  // конструктор пустого круга детей
  KidsCircle();
  // конструктор копирования круга детей
  KidsCircle(const KidsCircle& other);
  // деструктор круга детей
  ~KidsCircle();

  void push_back(const std::string& name);
  bool remove_by_name(const std::string& name);
  bool contains(const std::string& name) const;
  bool empty() const;
  int size() const;

  // Text2: вернуть порядок выбывания при чередовании направления счета.
  std::vector<std::string> elimination_order(int rhyme_word_count) const;

 private:
  void clear();

  ChildNode* head_;
  int size_;
};

// Решить задачу 5 из входного файла и записать порядок выбывания в выходной.
bool solve_text2_from_file(const std::string& input_file_path,
                        const std::string& output_file_path);

void run_task_1();
void run_task_2();
void run_task_3();
void run_task_4();
void run_task_5();
void run_task_6();

}

#endif
