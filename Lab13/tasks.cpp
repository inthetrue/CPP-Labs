#include "tasks.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <numeric>
#include <random>
#include <string>
#include <vector>


int read_int(const std::string& prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return value;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ошибка ввода, попробуйте снова" << std::endl;
  }
}


std::string read_string(const std::string& prompt) {
  std::string value;
  while (true) {
    std::cout << prompt;
    if (std::cin >> value) {
      return value;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ошибка ввода, попробуйте снова" << std::endl;
  }
}

std::list<int> read_list_int(int size) {
  std::list<int> result;
  std::cout << "Введите " << size << " целых чисел:" << std::endl;
  for (int i = 0; i < size; ++i) {
    int val = read_int("  элемент " + std::to_string(i + 1) + ": ");
    result.push_back(val);
  }
  return result;
}

// читает вектор целых чисел заданного размера
std::vector<int> read_vector_int(int size) {
  std::vector<int> result;
  std::cout << "Введите " << size << " целых чисел:" << std::endl;
  for (int i = 0; i < size; ++i) {
    int val = read_int("  элемент " + std::to_string(i + 1) + ": ");
    result.push_back(val);
  }
  return result;
}

// читает список строк заданного размера
std::list<std::string> read_list_string(int size) {
  std::list<std::string> result;
  std::cout << "Введите " << size << " строк:" << std::endl;
  for (int i = 0; i < size; ++i) {
    std::string val = read_string("  элемент " + std::to_string(i + 1) + ": ");
    result.push_back(val);
  }
  return result;
}

// генерирует список целых чисел случайным образом
std::list<int> generate_list_int(int size, int min_val, int max_val) {
  std::list<int> result;
  std::random_device rd;
  std::mt19937 gen(rd());
  // равномерное распределение в заданном диапазоне
  std::uniform_int_distribution<int> dist(min_val, max_val);

  for (int i = 0; i < size; ++i) {
    result.push_back(dist(gen));
  }
  return result;
}

// генерирует вектор целых чисел случайным образом
std::vector<int> generate_vector_int(int size, int min_val, int max_val) {
  std::vector<int> result;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(min_val, max_val);

  for (int i = 0; i < size; ++i) {
    result.push_back(dist(gen));
  }
  return result;
}

// генерирует список строк случайным образом
std::list<std::string> generate_list_string(int size, int word_length) {
  std::list<std::string> result;
  std::random_device rd;
  std::mt19937 gen(rd());
  // генерируем строки заданной длины из заглавных букв
  std::uniform_int_distribution<int> dist('A', 'Z');

  for (int i = 0; i < size; ++i) {
    std::string word;
    // формируем строку из word_length случайных букв
    for (int j = 0; j < word_length; ++j) {
      word += static_cast<char>(dist(gen));
    }
    result.push_back(word);
  }
  return result;
}

// читает список целых чисел из файла
std::list<int> read_list_int_from_file(const std::string& filename) {
  std::list<int> result;
  std::ifstream file(filename);

  // проверяем, открылся ли файл
  if (!file.is_open()) {
    std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return result;
  }

  int value;
  // читаем числа до конца файла
  while (file >> value) {
    result.push_back(value);
  }

  file.close();
  std::cout << "Прочитано " << result.size() << " элементов из файла" << std::endl;
  return result;
}

// читает вектор целых чисел из файла
std::vector<int> read_vector_int_from_file(const std::string& filename) {
  std::vector<int> result;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return result;
  }

  int value;
  while (file >> value) {
    result.push_back(value);
  }

  file.close();
  std::cout << "Прочитано " << result.size() << " элементов из файла" << std::endl;
  return result;
}

// читает список строк из файла
std::list<std::string> read_list_string_from_file(const std::string& filename) {
  std::list<std::string> result;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Ошибка: не удалось открыть файл " << filename << std::endl;
    return result;
  }

  std::string value;
  // читаем строки до конца файла
  while (file >> value) {
    result.push_back(value);
  }

  file.close();
  std::cout << "Прочитано " << result.size() << " элементов из файла" << std::endl;
  return result;
}

// выводит список целых чисел
void print_list_int(const std::list<int>& lst) {
  for (const auto& elem : lst) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

// выводит вектор целых чисел
void print_vector_int(const std::vector<int>& vec) {
  for (const auto& elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

// выводит дек строк
void print_deque_string(const std::deque<std::string>& deq) {
  for (const auto& elem : deq) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}


int choose_input_method() {
  std::cout << "\nВыберите способ ввода данных:" << std::endl;
  std::cout << "1. С клавиатуры" << std::endl;
  std::cout << "2. Случайно (диапазон от min до max)" << std::endl;
  std::cout << "3. Из файла" << std::endl;

  int method = read_int("Ваш выбор: ");
  while (method < 1 || method > 3) {
    std::cout << "Неверный выбор, попробуйте снова" << std::endl;
    method = read_int("Ваш выбор: ");
  }
  return method;
}

// задача 1: вставить 0 после первого отрицательного
// и перед последним положительным элементом
void stl3_alg5() {
  std::cout << "\nЗадача stl3_alg5" << std::endl;
  std::cout << "Вставить 0 после первого отрицательного" << std::endl;
  std::cout << "и перед последним положительным элементом" << std::endl;

  int size = read_int("Введите размер списка: ");
  while (size <= 0) {
    std::cout << "Размер должен быть положительным" << std::endl;
    size = read_int("Введите размер списка: ");
  }

  int method = choose_input_method();

  std::list<int> l;
  if (method == 1) {

    l = read_list_int(size);
  
  } else if (method == 2) {
    int min_val = read_int("Введите минимальное значение: ");
    int max_val = read_int("Введите максимальное значение: ");
    while (min_val > max_val) {
      std::cout << "Минимум не может быть больше максимума" << std::endl;
      min_val = read_int("Введите минимальное значение: ");
      max_val = read_int("Введите максимальное значение: ");
    }
    l = generate_list_int(size, min_val, max_val);
  } else {
    std::string filename = read_string("Введите имя файла: ");
    l = read_list_int_from_file(filename);
    if (l.empty()) {
      std::cout << "Файл пуст или не найден, введите данные вручную" << std::endl;
      l = read_list_int(size);
    }
  }

  std::cout << "Исходный список: ";
  print_list_int(l);

  // находим первый отрицательный элемент
  auto first_neg = std::find_if(l.begin(), l.end(),
                                [](int x) { return x < 0; });

  // вставляем 0 после первого отрицательного
  if (first_neg != l.end()) {
    l.insert(std::next(first_neg), 0);
    std::cout << "Вставлен 0 после первого отрицательного" << std::endl;
  } else {
    std::cout << "Отрицательных элементов не найдено" << std::endl;
  }

  // находим последний положительный элемент
  auto last_pos_rit = std::find_if(l.rbegin(), l.rend(),
                                   [](int x) { return x > 0; });

  // вставляем 0 перед последним положительным
  if (last_pos_rit != l.rend()) {
    l.insert(--last_pos_rit.base(), 0);
    std::cout << "Вставлен 0 перед последним положительным" << std::endl;
  } else {
    std::cout << "Положительных элементов не найдено" << std::endl;
  }

  std::cout << "Результат: ";
  print_list_int(l);
}

// задача 2: добавить 5 элементов A в начало и 5 элементов B в конец
void stl3_alg17() {
  std::cout << "\nЗадача stl3_alg17" << std::endl;
  std::cout << "Добавить 5 элементов A в начало и 5 элементов B в конец" << std::endl;

  int a = read_int("Введите значение A: ");
  int b = read_int("Введите значение B: ");


  int size1 = read_int("Введите размер вектора V1: ");
  while (size1 < 0) {
    std::cout << "Размер не может быть отрицательным" << std::endl;
    size1 = read_int("Введите размер вектора V1: ");
  }

  int size2 = read_int("Введите размер вектора V2: ");
  while (size2 < 0) {
    std::cout << "Размер не может быть отрицательным" << std::endl;
    size2 = read_int("Введите размер вектора V2: ");
  }

  std::cout << "\nДля вектора V1:" << std::endl;
  int method1 = choose_input_method();

  std::vector<int> v1;
  if (method1 == 1) {
    v1 = read_vector_int(size1);
  } else if (method1 == 2) {
    int min_val = read_int("Введите минимальное значение: ");
    int max_val = read_int("Введите максимальное значение: ");
    while (min_val > max_val) {
      std::cout << "Минимум не может быть больше максимума" << std::endl;
      min_val = read_int("Введите минимальное значение: ");
      max_val = read_int("Введите максимальное значение: ");
    }
    v1 = generate_vector_int(size1, min_val, max_val);
  } else {
    std::string filename = read_string("Введите имя файла: ");
    v1 = read_vector_int_from_file(filename);
    if (v1.empty()) {
      std::cout << "Файл пуст или не найден, введите данные вручную" << std::endl;
      v1 = read_vector_int(size1);
    }
  }

  std::cout << "\nДля вектора V2:" << std::endl;
  int method2 = choose_input_method();

  std::vector<int> v2;
  if (method2 == 1) {
    v2 = read_vector_int(size2);
  } else if (method2 == 2) {
    int min_val = read_int("Введите минимальное значение: ");
    int max_val = read_int("Введите максимальное значение: ");
    while (min_val > max_val) {
      std::cout << "Минимум не может быть больше максимума" << std::endl;
      min_val = read_int("Введите минимальное значение: ");
      max_val = read_int("Введите максимальное значение: ");
    }
    v2 = generate_vector_int(size2, min_val, max_val);
  } else {
    std::string filename = read_string("Введите имя файла: ");
    v2 = read_vector_int_from_file(filename);
    if (v2.empty()) {
      std::cout << "Файл пуст или не найден, введите данные вручную" << std::endl;
      v2 = read_vector_int(size2);
    }
  }

  std::cout << "Исходный v1: ";
  print_vector_int(v1);

  std::cout << "Исходный v2: ";
  print_vector_int(v2);

  // способ 1: для v1 используем fill_n с inserter и back_inserter
  std::fill_n(std::inserter(v1, v1.begin()), 5, a); // первый аргумент итератор, второй кол-во элементов, третий значений
  std::fill_n(std::back_inserter(v1), 5, b); // добавляет в конец

  // способ 2: для v2 используем функцию-член insert
  v2.insert(v2.begin(), 5, a);
  v2.insert(v2.end(), 5, b);
  std::cout << "Результат v1 (fill_n): ";
  print_vector_int(v1);

  std::cout << "Результат v2 (insert): ";
  print_vector_int(v2);
}

// задача 3: найти три минимальных элемента вектора
void stl3_alg37() {
  std::cout << "\nЗадача stl3_alg37" << std::endl;
  std::cout << "Найти три минимальных элемента вектора" << std::endl;

  int size = read_int("Введите размер вектора: ");
  while (size < 3) {
    std::cout << "Размер должен быть не менее 3" << std::endl;
    size = read_int("Введите размер вектора: ");
  }

  int method = choose_input_method();

  std::vector<int> v;
  if (method == 1) {
    v = read_vector_int(size);
  } else if (method == 2) {
    int min_val = read_int("Введите минимальное значение: ");
    int max_val = read_int("Введите максимальное значение: ");
    while (min_val > max_val) {
      std::cout << "Минимум не может быть больше максимума" << std::endl;
      min_val = read_int("Введите минимальное значение: ");
      max_val = read_int("Введите максимальное значение: ");
    }
    v = generate_vector_int(size, min_val, max_val);
  } else {
    std::string filename = read_string("Введите имя файла: ");
    v = read_vector_int_from_file(filename);
    if (v.empty()) {
      std::cout << "Файл пуст или не найден, введите данные вручную" << std::endl;
      v = read_vector_int(size);
    }
  }

  std::cout << "Исходный вектор: ";
  print_vector_int(v);

  // копируем вектор, чтобы не изменять исходный
  std::vector<int> sorted_v = v;

  // сортируем первые 3 элемента по возрастанию
  std::partial_sort(sorted_v.begin(), sorted_v.begin() + 3, sorted_v.end());
  std::cout << "Три минимальных элемента: ";
  std::copy(sorted_v.begin(), sorted_v.begin() + 3,
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

// функциональный объект для формирования строки из пары соседних элементов
struct CombinePair {
  std::string operator()(const std::string& current,
                         const std::string& previous) const {
    if (current.empty() || previous.empty()) {
      return "";
    }
    // берём первую букву из предыдущего элемента (левый в паре)
    char first_char = previous.front();
    // берём последнюю букву из текущего элемента (правый в паре)
    char last_char = current.back();
    return std::string(1, first_char) + std::string(1, last_char);
  }
};

// задача 4: создать дек из пар соседних элементов списка
void stl3_alg61() {
  std::cout << "\nЗадача stl3_alg61" << std::endl;
  std::cout << "Создать дек из пар соседних элементов списка" << std::endl;


  int size = read_int("Введите размер списка: ");
  while (size < 2) {
    std::cout << "Размер должен быть не менее 2" << std::endl;
    size = read_int("Введите размер списка: ");
  }

  int method = choose_input_method();

  std::list<std::string> l;
  if (method == 1) {
    l = read_list_string(size);
  } else if (method == 2) {
    int word_length = read_int("Введите длину каждого слова: ");
    while (word_length <= 0) {
      std::cout << "Длина должна быть положительной" << std::endl;
      word_length = read_int("Введите длину каждого слова: ");
    }
    l = generate_list_string(size, word_length);
  } else {
    std::string filename = read_string("Введите имя файла: ");
    l = read_list_string_from_file(filename);
    if (l.empty()) {
      std::cout << "Файл пуст или не найден, введите данные вручную" << std::endl;
      l = read_list_string(size);
    }
  }

  std::cout << "Исходный список: ";
  for (const auto& elem : l) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  std::deque<std::string> d;

  // используем adjacent_difference с функциональным объектом
  std::adjacent_difference(l.begin(), l.end(),
                           std::inserter(d, d.end()),
                           CombinePair());
  // удаляем первый элемент дека, так как он дублирует первый элемент списка
  if (!d.empty()) {
    d.erase(d.begin());
  }

  std::cout << "Результат дек: ";
  print_deque_string(d);
}