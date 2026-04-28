#ifndef TASKS_H
#define TASKS_H

#include <list>
#include <vector>
#include <deque>
#include <string>

// вспомогательные функции для ввода с проверкой
// читает целое число с повторением при ошибке ввода
int read_int(const std::string& prompt);

// читает строку с повторением при ошибке ввода
std::string read_string(const std::string& prompt);

// читает список целых чисел заданного размера
std::list<int> read_list_int(int size);

// читает вектор целых чисел заданного размера
std::vector<int> read_vector_int(int size);

// читает список строк заданного размера
std::list<std::string> read_list_string(int size);

// генерирует список целых чисел случайным образом
std::list<int> generate_list_int(int size, int min_val, int max_val);

// генерирует вектор целых чисел случайным образом
std::vector<int> generate_vector_int(int size, int min_val, int max_val);

// генерирует список строк случайным образом
std::list<std::string> generate_list_string(int size, int word_length = 3);

// читает список целых чисел из файла
std::list<int> read_list_int_from_file(const std::string& filename);

// читает вектор целых чисел из файла
std::vector<int> read_vector_int_from_file(const std::string& filename);

// читает список строк из файла
std::list<std::string> read_list_string_from_file(const std::string& filename);

// выводит список целых чисел
void print_list_int(const std::list<int>& lst);

// выводит вектор целых чисел
void print_vector_int(const std::vector<int>& vec);

// выводит дек строк
void print_deque_string(const std::deque<std::string>& deq);

// выбор способа ввода данных
// возвращает 1 - клавиатура, 2 - рандом, 3 - файл
int choose_input_method();

// задача 1: вставить 0 после первого отрицательного
// и перед последним положительным элементом
void stl3_alg5();

// задача 2: добавить 5 элементов A в начало и 5 элементов B в конец
void stl3_alg17();

// задача 3: найти три минимальных элемента вектора
void stl3_alg37();

// задача 4: создать дек из пар соседних элементов списка
void stl3_alg61();

#endif  // TASKS_H