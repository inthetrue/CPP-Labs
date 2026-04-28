#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <cstddef>
#include <vector>

class Stack {
 private:
  struct TNode {
    int Data;
    TNode* Next;
    TNode(int value, TNode* next = nullptr) : Data(value), Next(next) {} // конструктор со списком инициализации
  };

  TNode* top_;

  void copy_from(const Stack& other);
  void clear();

 public:
  Stack(); // конструктор по умолчанию
  Stack(const Stack& other); // конструктор копирования
  Stack& operator=(const Stack& other); // оператор присваивания
  ~Stack(); // деструктор

  void push(int value);
  bool pop(int& removed_value);
  bool contains(int value) const;
  bool is_empty() const;
  const void* top_address() const;
  int top_value() const;
  void print_values() const;
};

class Queue {
 private:
  struct TNode {
    int Data;
    TNode* Next;
    explicit TNode(int value) : Data(value), Next(nullptr) {}
  };

  TNode* head_;
  TNode* tail_;

  void copy_from(const Queue& other);
  void clear();

 public:
  Queue();
  Queue(const Queue& other);
  Queue& operator=(const Queue& other);
  ~Queue();

  void enqueue(int value);
  bool dequeue(int& removed_value);
  bool contains(int value) const;
  bool is_empty() const;
  bool front(int& value) const;
  bool back(int& value) const;
  void move_until_even(Queue& other);
  void print_values() const;
  const void* head_address() const;
  const void* tail_address() const;
};

class LinkedList {
 private:
  struct Node {
    int value;
    Node* next;
    explicit Node(int value_arg) : value(value_arg), next(nullptr) {}
  };

  Node* head_;
  Node* tail_;

  void copy_from(const LinkedList& other);
  void clear();

 public:
  LinkedList();
  LinkedList(const LinkedList& other);
  LinkedList& operator=(const LinkedList& other);
  ~LinkedList();

  void push_back(int value);
  bool remove_first(int value);
  bool contains(int value) const;
  bool is_empty() const;

  const void* third_address() const;
  int third_value() const;
  void insert_after_every_third(int value);
  LinkedList copy_with_inserted_sorted(int value) const;
  void print_values() const;

  const void* head_address() const;
  const void* tail_address() const;
};

Stack build_stack_from_numbers(const std::vector<int>& numbers);
void run_task_dynamic4();
void run_task_dynamic23();
void run_task_list_work2();
void run_task_list_work23();
void run_task_list_work60();
void run_demo_operations();

#endif  // STRUCTURES_H_
