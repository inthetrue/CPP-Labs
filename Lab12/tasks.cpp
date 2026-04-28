#include "tasks.h"

#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace tasks_internal {

constexpr int kInputKeyboard = 1;
constexpr int kInputRandom = 2;
constexpr int kInputFile = 3;

// читает целое число с повторным запросом при ошибке
int read_int_value(const std::string& prompt) {
  // просим число пока ввод не станет корректным
  while (true) {
    std::cout << prompt;
    int value = 0;
    if (std::cin >> value) {
      return value;
    }

    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n');
    std::cout << "Нужно ввести целое число\n";
  }
}

// читает строковое значение для имени файла
std::string read_text_value(const std::string& prompt) {
  // читаем одно слово для имени файла
  std::cout << prompt;
  std::string value;
  std::cin >> value;
  if (!std::cin) {
    throw std::runtime_error("Не удалось прочитать текстовое значение");
  }
  return value;
}

// показывает меню выбора способа ввода данных
int choose_input_mode() {
  // даем выбор источника данных
  std::cout << "Выберите способ ввода данных\n";
  std::cout << "1 - С клавиатуры\n";
  std::cout << "2 - Случайные числа\n";
  std::cout << "3 - Из файла\n";

  // валидируем пункт меню
  while (true) {
    const int mode = read_int_value("Режим: ");
    if (mode >= kInputKeyboard && mode <= kInputFile) {
      return mode;
    }
    std::cout << "Доступны только 1, 2, 3\n";
  }
}

// читает набор целых чисел с клавиатуры
std::vector<int> read_numbers_keyboard(int count) {
  // проверяем что размер положительный
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  // читаем count чисел через потоковый итератор
  std::cout << "Введите " << count << " целых чисел: ";
  std::vector<int> values;
  std::copy_n(
      std::istream_iterator<int>(std::cin),
      count,
      std::back_inserter(values));

  // проверяем что получили все элементы
  if (static_cast<int>(values.size()) != count) {
    throw std::runtime_error("Не удалось прочитать нужное количество чисел");
  }

  return values;
}

// генерирует набор случайных целых чисел
std::vector<int> generate_random_numbers(int count) {
  // проверяем что размер положительный
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  // читаем границы генерации
  const int min_value = read_int_value("Минимум: ");
  const int max_value = read_int_value("Максимум: ");
  if (min_value > max_value) {
    throw std::invalid_argument("Минимум должен быть <= максимум");
  }

  // заполняем вектор случайными числами
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> dist(min_value, max_value);

  std::vector<int> values;
  values.reserve(count);
  std::generate_n(
      std::back_inserter(values),
      count,
      [&dist, &generator]() { return dist(generator); });
  return values;
}

// читает набор целых чисел из файла
std::vector<int> read_numbers_file(const std::string& file_name) {
  // открываем файл с числами
  std::ifstream input_file(file_name);
  if (!input_file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: " + file_name);
  }

  // читаем все целые через итераторы
  std::vector<int> values{
      std::istream_iterator<int>(input_file),
      std::istream_iterator<int>()};

  // защищаемся от пустого файла
  if (values.empty()) {
    throw std::runtime_error("В файле нет целых чисел");
  }

  return values;
}

// выводит элементы дека через обычные итераторы
void print_deque(std::deque<int>::const_iterator begin,
                 std::deque<int>::const_iterator end) {
  // выводим дек обычными итераторами
  for (std::deque<int>::const_iterator it = begin; it != end; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

// выводит элементы списка через обычные итераторы
void print_list(std::list<int>::const_iterator begin,
                std::list<int>::const_iterator end) {
  // выводим список обычными итераторами
  for (std::list<int>::const_iterator it = begin; it != end; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

// выводит исходный набор чисел перед обработкой
void print_source_numbers(const std::vector<int>& values) {
  std::cout << "Исходные данные: ";
  for (std::vector<int>::const_iterator it = values.begin();
       it != values.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

// загружает данные для задачи STL2Seq с проверкой размера
std::vector<int> load_numbers_for_seq_task(
    bool (*is_valid)(int),
    const std::string& rule_text) {
  const int mode = choose_input_mode();

  if (mode == kInputKeyboard) {
    while (true) {
      const int count = read_int_value("Количество: ");
      if (!is_valid(count)) {
        std::cout << "Неверное количество, " << rule_text << '\n';
        continue;
      }
      return read_numbers_keyboard(count);
    }
  }

  if (mode == kInputRandom) {
    while (true) {
      const int count = read_int_value("Количество: ");
      if (!is_valid(count)) {
        std::cout << "Неверное количество, " << rule_text << '\n';
        continue;
      }
      return generate_random_numbers(count);
    }
  }

  const std::string file_name = read_text_value("Имя файла: ");
  const std::vector<int> values = read_numbers_file(file_name);
  if (!is_valid(static_cast<int>(values.size()))) {
    throw std::invalid_argument(
        "Неверное количество элементов в файле, " + rule_text);
  }
  return values;
}

// проверяет что размер положительный и четный
bool is_even_positive(int count) {
  return count > 0 && count % 2 == 0;
}

// проверяет что размер нечетный и не меньше пяти
bool is_odd_at_least_five(int count) {
  return count >= 5 && count % 2 != 0;
}

// записывает числа в файл с вводом с клавиатуры
void write_numbers_to_file_keyboard(const std::string& target_file) {
  const int count = read_int_value("Сколько чисел записать: ");
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  // открываем файл и записываем через итератор
  std::ofstream output_file(target_file);
  if (!output_file.is_open()) {
    throw std::runtime_error(
        "Не удалось открыть файл для записи: " + target_file);
  }

  std::cout << "Введите " << count << " целых чисел: ";
  std::ostream_iterator<int> out_it(output_file, " ");
  for (int index = 0; index < count; ++index) {
    int value = 0;
    if (!(std::cin >> value)) {
      throw std::runtime_error("Не удалось прочитать число для файла");
    }
    *out_it = value;
    ++out_it;
  }
}

// записывает в файл случайно сгенерированные числа
void write_numbers_to_file_random(const std::string& target_file) {
  // читаем параметры генерации
  const int count = read_int_value("Сколько чисел записать: ");
  if (count <= 0) {
    throw std::invalid_argument("Количество должно быть положительным");
  }

  const int min_value = read_int_value("Минимум: ");
  const int max_value = read_int_value("Максимум: ");
  if (min_value > max_value) {
    throw std::invalid_argument("Минимум должен быть <= максимум");
  }

  // генерируем и пишем сразу в файл
  std::ofstream output_file(target_file);
  if (!output_file.is_open()) {
    throw std::runtime_error(
        "Не удалось открыть файл для записи: " + target_file);
  }

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> dist(min_value, max_value);
  std::ostream_iterator<int> out_it(output_file, " ");

  for (int index = 0; index < count; ++index) {
    *out_it = dist(generator);
    ++out_it;
  }
}

// копирует числа из одного файла в другой
void write_numbers_to_file_from_file(const std::string& target_file) {
  const std::string source_file = read_text_value("Имя файла-источника: ");
  std::ifstream input_file(source_file);
  if (!input_file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл-источник: " +
                             source_file);
  }

  std::ofstream output_file(target_file);
  if (!output_file.is_open()) {
    throw std::runtime_error(
        "Не удалось открыть файл для записи: " + target_file);
  }

  std::copy(
      std::istream_iterator<int>(input_file),
      std::istream_iterator<int>(),
      std::ostream_iterator<int>(output_file, " "));
}

// задание STL1Iter9
std::string prepare_file_for_stl1iter9() {
  const std::string target_file = read_text_value("Имя рабочего файла: ");

  const int mode = choose_input_mode();
  if (mode == kInputKeyboard) {
    write_numbers_to_file_keyboard(target_file);
  } else if (mode == kInputRandom) {
    write_numbers_to_file_random(target_file);
  } else {
    write_numbers_to_file_from_file(target_file);
  }

  return target_file;
}

}

// задача STL2Seq4
void run_stl2seq4() {
  // загружаем данные с проверкой на четный размер
  std::cout << "\nSTL2Seq4\n";
  const std::vector<int> values =
      tasks_internal::load_numbers_for_seq_task(
          tasks_internal::is_even_positive,
          "Нужно четное количество > 0");
  tasks_internal::print_source_numbers(values);

  // строим дек через конструктор от итераторов
  std::deque<int> deque_data(values.begin(), values.end());
  const int half = static_cast<int>(deque_data.size()) / 2;

  // выводим первую половину в обратном порядке
  // старт rbegin + half дает элемент с индексом half - 1
  std::cout << "Первая половина в обратном порядке\n";
  for (std::deque<int>::const_reverse_iterator it =
           deque_data.rbegin() + half;
       it != deque_data.rend(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';

  // диапазон от rbegin до rbegin + half покрывает правую половину
  std::cout << "Вторая половина в обратном порядке\n";
  for (std::deque<int>::const_reverse_iterator it = deque_data.rbegin();
       it != deque_data.rbegin() + half; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}

void run_stl2seq9() {
  std::cout << "\nSTL2Seq9\n";
  const std::vector<int> values =
      tasks_internal::load_numbers_for_seq_task(
          tasks_internal::is_odd_at_least_five,
          "Нужно нечетное количество >= 5");
  tasks_internal::print_source_numbers(values);

  // строим дек через конструктор от итераторов
  std::deque<int> deque_data(values.begin(), values.end());
  const int count = static_cast<int>(deque_data.size());

  // выделяем 5 средних элементов в исходном порядке
  const int middle_index = count / 2;
  std::deque<int>::const_iterator middle_begin =
      deque_data.begin() + (middle_index - 2);
  std::deque<int>::const_iterator middle_end =
      deque_data.begin() + (middle_index + 3);

  std::deque<int> middle_values(middle_begin, middle_end);

  std::cout << "5 Средних чисел: ";
  tasks_internal::print_deque(
      middle_values.begin(),
      middle_values.end());

  // вставляем диапазон в начало одним вызовом
  deque_data.insert(
      deque_data.begin(),
      middle_values.begin(),
      middle_values.end());

  std::cout << "Дек после вставки\n";
  tasks_internal::print_deque(deque_data.begin(), deque_data.end());
}

// решает задачу STL2Seq33
void run_stl2seq33() {
  std::cout << "\nSTL2Seq33\n";
  const std::vector<int> values =
      tasks_internal::load_numbers_for_seq_task(
          tasks_internal::is_even_positive,
          "Нужно четное количество > 0");
  tasks_internal::print_source_numbers(values);

  std::list<int> list_data(values.begin(), values.end());
  const int count = static_cast<int>(list_data.size());

  std::cout << "Список до перестановки\n";
  tasks_internal::print_list(list_data.begin(), list_data.end());

  std::list<int>::iterator i = list_data.begin();
  std::list<int>::iterator r = std::prev(list_data.end()); // prev сдвигает итератор end - 1

  // делаем n/2 итераций
  for (int step = 0; step < count / 2; ++step) {
    list_data.splice(i++, list_data, r--); // i идет слева направо, r идет справа налево
    // берем r с конца, переносим перед i, двигаем i++ и r--.
  }

  std::cout << "Список после перестановки\n";
  tasks_internal::print_list(list_data.begin(), list_data.end());
}

// задача STL1Iter9
void run_stl1iter9() {
  std::cout << "\nSTL1Iter9\n";
  const std::string file_name =
      tasks_internal::prepare_file_for_stl1iter9();

  std::ifstream input_file(file_name);
  if (!input_file.is_open()) {
    throw std::runtime_error("Не удалось открыть файл: " + file_name);
  }
  std::istream_iterator<int> begin(input_file);
  const std::istream_iterator<int> end;

  if (begin == end) {
    throw std::runtime_error("В файле нет целых чисел");
  }

  // remove_copy_if отбрасывает элементы где вернулось true
  std::cout << "Значения с нечетными номерами\n";
  int position = 1;
  std::remove_copy_if(
      begin,
      end,
      std::ostream_iterator<int>(std::cout, " "),
      // лямбда-предикат вызывается для каждого элемента, если вернет true, удаляется
      // если вернет false элемент выводится
      [&position](int) {
        const bool remove_value = (position % 2 == 0);
        ++position;
        return remove_value;
      });
  std::cout << '\n';
}
