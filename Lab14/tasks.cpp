#include "tasks.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <set>
#include <stdexcept>

int read_int_or_throw(std::istream& input, const std::string& error_message) {
  int value = 0;
  if (!(input >> value)) {
    throw std::runtime_error(error_message);
  }
  return value;
}

int read_int_from_console(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    int value = 0;
    if (!(std::cin >> value)) {
      std::cout << "Ошибка: введите целое число\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    return value;
  }
}

int read_positive_int(const std::string& prompt) {
  while (true) {
    const int value = read_int_from_console(prompt);
    if (value <= 0) {
      std::cout << "Ошибка: ожидается число больше нуля\n";
      continue;
    }
    return value;
  }
}

int read_non_negative_int(const std::string& prompt) {
  while (true) {
    const int value = read_int_from_console(prompt);
    if (value < 0) {
      std::cout << "Ошибка: ожидается неотрицательное число\n";
      continue;
    }
    return value;
  }
}

int read_range_border(const std::string& prompt) {
  return read_int_from_console(prompt);
}

void read_min_max(int* min_value, int* max_value) {
  while (true) {
    *min_value = read_range_border("Введите min: ");
    *max_value = read_range_border("Введите max: ");
    if (*min_value > *max_value) {
      std::cout << "Ошибка: min не может быть больше max\n";
      continue;
    }
    return;
  }
}

int read_mode_choice() {
  while (true) {
    std::cout << "Выберите способ заполнения данных\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайно (от min до max)\n";
    std::cout << "3. Из файла\n";
    std::cout << "Введите вариант: ";

    int mode = 0;
    if (!(std::cin >> mode)) {
      std::cout << "Ошибка: введите 1, 2 или 3\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    if (mode < static_cast<int>(InputMode::kKeyboard) ||
        mode > static_cast<int>(InputMode::kFile)) {
      std::cout << "Ошибка: вариант должен быть 1, 2 или 3\n";
      continue;
    }
    return mode;
  }
}

std::string read_file_path() {
  while (true) {
    std::cout << "Введите путь к файлу: ";
    std::string path;
    if (!(std::cin >> path)) {
      std::cout << "Ошибка: не удалось прочитать путь\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    return path;
  }
}

bool is_uppercase_english_word(const std::string& word) {
  if (word.empty()) {
    return false;
  }

  for (const char ch : word) {
    if (ch < 'A' || ch > 'Z') {
      return false;
    }
  }
  return true;
}

char get_last_char_or_throw(const std::string& word) {
  // проверяем что слово не пустое перед доступом к хвосту
  if (word.empty()) {
    throw std::runtime_error("слово не должно быть пустым");
  }

  // используем последнюю букву как ключ группировки
  return word.back();
}

std::vector<int> read_int_vector_keyboard(const std::string& name) {
  // запрашиваем размер вектора у пользователя
  const int size = read_non_negative_int("Введите размер " + name + ": ");

  // создаем вектор нужной длины
  std::vector<int> values(size);

  // читаем элементы по порядку и повторяем ввод при ошибке
  for (int i = 0; i < size; ++i) {
    while (true) {
      std::cout << "Введите элемент " << name << "[" << (i + 1) << "]: ";
      if (!(std::cin >> values[i])) {
        std::cout << "Ошибка: введите целое число\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      break;
    }
  }
  return values;
}

std::vector<int> read_int_vector_with_size_keyboard(const std::string& name,
                                                    int size) {
  std::vector<int> values(size);
  for (int i = 0; i < size; ++i) {
    while (true) {
      std::cout << "Введите элемент " << name << "[" << (i + 1) << "]: ";
      if (!(std::cin >> values[i])) {
        std::cout << "Ошибка: введите целое число\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      break;
    }
  }
  return values;
}

std::vector<int> read_int_vector_file(std::istream& input,
                                      const std::string& name) {
  const int size = read_int_or_throw(input,
                                     "не удалось прочитать размер вектора " +
                                         name + " из файла");
  if (size < 0) {
    throw std::runtime_error("размер вектора " + name +
                             " в файле не может быть отрицательным");
  }
  std::vector<int> values(size);
  for (int i = 0; i < size; ++i) {
    values[i] =
        read_int_or_throw(input,
                          "не удалось прочитать элемент вектора " + name +
                              " из файла");
  }
  return values;
}

std::vector<int> generate_random_int_vector(const std::string& name, int size,
                                            int min_value, int max_value) {
  if (size < 0) {
    throw std::runtime_error("размер вектора " + name +
                             " не может быть отрицательным");
  }
  if (min_value > max_value) {
    throw std::runtime_error("min не может быть больше max");
  }

  static std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(min_value, max_value);

  std::vector<int> values(size);
  for (int& value : values) {
    value = distribution(generator);
  }
  return values;
}

std::vector<std::string> read_uppercase_word_vector_keyboard(
    const std::string& name) {
  const int size = read_non_negative_int("Введите размер " + name + ": ");
  std::vector<std::string> words(size);

  for (int i = 0; i < size; ++i) {
    while (true) {
      std::cout << "Введите слово " << name << "[" << (i + 1) << "]: ";
      if (!(std::cin >> words[i])) {
        std::cout << "Ошибка: введите слово\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      if (!is_uppercase_english_word(words[i])) {
        std::cout << "Ошибка: слово должно быть из заглавных букв A..Z\n";
        continue;
      }
      break;
    }
  }
  return words;
}

std::vector<std::string> read_uppercase_word_vector_file(
    std::istream& input, const std::string& name) {
  const int size = read_int_or_throw(input,
                                     "не удалось прочитать размер " + name +
                                         " из файла");
  if (size < 0) {
    throw std::runtime_error("размер вектора слов " + name +
                             " в файле не может быть отрицательным");
  }

  std::vector<std::string> words(size);
  for (int i = 0; i < size; ++i) {
    if (!(input >> words[i])) {
      throw std::runtime_error("не удалось прочитать слово " + name +
                               " из файла");
    }
    if (!is_uppercase_english_word(words[i])) {
      throw std::runtime_error("слово в файле должно быть из заглавных букв");
    }
  }
  return words;
}

std::vector<std::string> generate_random_word_vector(const std::string& name,
                                                      int size,
                                                      int min_len,
                                                      int max_len) {
  if (size < 0) {
    throw std::runtime_error("размер вектора слов " + name +
                             " не может быть отрицательным");
  }
  if (min_len <= 0 || max_len <= 0) {
    throw std::runtime_error("длины слов должны быть больше нуля");
  }
  if (min_len > max_len) {
    throw std::runtime_error("минимальная длина слова больше максимальной");
  }

  static std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> len_distribution(min_len, max_len);
  std::uniform_int_distribution<int> char_distribution(0, 25);

  std::vector<std::string> words;

  for (int i = 0; i < size; ++i) {
    const int current_len = len_distribution(generator);
    std::string word;

    for (int j = 0; j < current_len; ++j) {
      const char letter = static_cast<char>('A' + char_distribution(generator));
      word.push_back(letter);
    }
    words.push_back(word);
  }
  return words;
}

void print_int_vector(const std::string& name, const std::vector<int>& values) {
  std::cout << name << " = ";
  for (const int value : values) {
    std::cout << value << " ";
  }
  std::cout << "\n";
}

void print_word_vector(const std::string& name,
                       const std::vector<std::string>& words) {
  std::cout << name << " = ";
  for (const std::string& word : words) {
    std::cout << word << " ";
  }
  std::cout << "\n";
}

std::ifstream open_input_file_with_retry() {
  while (true) {
    const std::string path = read_file_path();
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cout << "Ошибка: не удалось открыть файл, попробуйте снова\n";
      continue;
    }
    return file;
  }
}

// задача 1: ищет номера Vi, которые включают все элементы V0
// с учетом повторений, и выводит их количество
void run_task_1() {
  std::cout << "\nЗапуск задачи 1 STL5Assoc3\n";
  const int mode = read_mode_choice();

  // контейнеры для входных данных задачи
  std::vector<int> v0;
  int n = 0;
  std::vector<std::vector<int>> vectors;

  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    // читаем V0 и количество векторов Vi
    v0 = read_int_vector_keyboard("V0");
    n = read_positive_int("Введите N: ");

    // читаем размеры всех Vi
    std::vector<int> sizes(n);
    for (int i = 1; i <= n; ++i) {
      while (true) {
        const int current_size = read_non_negative_int(
            "Введите размер V" + std::to_string(i) + ": ");
        if (current_size < static_cast<int>(v0.size())) {
          std::cout << "Ошибка: размер каждого Vi должен быть не меньше V0\n";
          continue;
        }
        sizes[i - 1] = current_size;
        break;
      }
    }

    int fill_mode = 0;
    while (true) {
      std::cout << "Выберите способ заполнения V1..Vn\n";
      std::cout << "1. С клавиатуры\n";
      std::cout << "2. Случайно (от min до max)\n";
      fill_mode = read_int_from_console("Введите вариант: ");
      if (fill_mode != 1 && fill_mode != 2) {
        std::cout << "Ошибка: вариант должен быть 1 или 2\n";
        continue;
      }
      break;
    }

    if (fill_mode == 1) {
      // заполняем каждый Vi с клавиатуры
      for (int i = 1; i <= n; ++i) {
        const std::string name = "V" + std::to_string(i);
        vectors.push_back(
            read_int_vector_with_size_keyboard(name, sizes[i - 1]));
      }
    } else {
      // заполняем каждый Vi случайными числами
      int min_value = 0;
      int max_value = 0;
      read_min_max(&min_value, &max_value);
      for (int i = 1; i <= n; ++i) {
        const std::string name = "V" + std::to_string(i);
        vectors.push_back(
            generate_random_int_vector(name, sizes[i - 1], min_value, max_value));
      }
    }
  } else if (mode == static_cast<int>(InputMode::kRandom)) {
    // читаем диапазон случайных значений
    int min_value = 0;
    int max_value = 0;
    read_min_max(&min_value, &max_value);

    // читаем размер V0 и количество Vi
    const int v0_size = read_non_negative_int("Введите размер V0: ");
    n = read_positive_int("Введите N: ");

    // читаем общий размер для всех V1..VN
    int common_size = 0;
    while (true) {
      common_size = read_non_negative_int("Введите общий размер для V1..VN: ");
      if (common_size < v0_size) {
        std::cout << "Ошибка: размер каждого Vi должен быть не меньше V0\n";
        continue;
      }
      break;
    }

    v0 = generate_random_int_vector("V0", v0_size, min_value, max_value);

    // генерируем все Vi одного размера
    for (int i = 1; i <= n; ++i) {
      const std::string name = "V" + std::to_string(i);
      vectors.push_back(generate_random_int_vector(name, common_size,
                                                   min_value, max_value));
    }

  } else {
    std::ifstream file = open_input_file_with_retry();

    v0 = read_int_vector_file(file, "V0");
    n = read_int_or_throw(file, "не удалось прочитать N из файла");
    if (n <= 0) {
      throw std::runtime_error("N в файле должен быть больше нуля");
    }

    for (int i = 1; i <= n; ++i) {
      const std::string name = "V" + std::to_string(i);
      const std::vector<int> current = read_int_vector_file(file, name);
      if (current.size() < v0.size()) {
        throw std::runtime_error("размер каждого Vi в файле должен быть >= V0");
      }
      vectors.push_back(current);
    }

  }

  print_int_vector("V0", v0);
  for (int i = 0; i < n; ++i) {
    print_int_vector("V" + std::to_string(i + 1), vectors[i]);
  }

  // создаем мультимножество из V0 для проверки includes с учетом повторов
  const std::multiset<int> base_set(v0.begin(), v0.end());


  // собираем номера Vi, в которых есть все элементы V0
  std::vector<int> matched_indices;
  for (int i = 0; i < n; ++i) {
    // берем текущий вектор
    const std::vector<int>& current_vector = vectors[i];
    // превращаем вектор в multiset, чтобы учитывались повторы + элементы были отсортированы
    const std::multiset<int> current_set(current_vector.begin(),
                                         current_vector.end());
    // проверяет, содержит ли current_et все элементы base_set
    if (std::includes(current_set.begin(), current_set.end(),
                      base_set.begin(), base_set.end())) {
      matched_indices.push_back(i + 1); // если содержит, то добавляем номер вектора
    }
  }

  std::cout << "Номера подходящих векторов: ";
  if (matched_indices.empty()) {
    std::cout << "нет";
  } else {
    for (const int index : matched_indices) {
      std::cout << index << " ";
    }
  }
  std::cout << "\n";
  std::cout << "Количество подходящих векторов: "
            << matched_indices.size() << "\n";
}

// задача 2: считает количество повторений каждого числа в V
// и выводит пары число - количество по возрастанию
void run_task_2() {
  std::cout << "\nЗапуск задачи 2 STL5Assoc15\n";

  const int mode = read_mode_choice();
  std::vector<int> v;

  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    v = read_int_vector_keyboard("V");
  } else if (mode == static_cast<int>(InputMode::kRandom)) {
    int min_value = 0;
    int max_value = 0;
    read_min_max(&min_value, &max_value);

    const int size = read_non_negative_int("Введите размер V: ");
    v = generate_random_int_vector("V", size, min_value, max_value);
    print_int_vector("V", v);
  } else {
    std::ifstream file = open_input_file_with_retry();
    v = read_int_vector_file(file, "V");
    print_int_vector("V", v);
  }

  // -------------------------------------------------------------

  // map хранит число и количество его повторений
  std::map<int, int> counts;

  // заполняем map подсчетом повторений
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    ++counts[*it];
  }

  // выводим пары число - количество в порядке возрастания
  std::cout << "Кол-во элементов\n";
  for (std::map<int, int>::const_iterator it = counts.begin();
       it != counts.end(); ++it) {
    std::cout << it->first << " - " << it->second << "\n";
  }
}

// задача 3: группирует слова по последней букве в multimap
// и выводит пары ключ - слово
void run_task_3() {
  std::cout << "\nЗапуск задачи 3 STL5Assoc22\n";

  // заполнение векторов
  const int mode = read_mode_choice();
  std::vector<std::string> v;

  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    v = read_uppercase_word_vector_keyboard("V");
  } else if (mode == static_cast<int>(InputMode::kRandom)) {
    const int size = read_non_negative_int("Введите размер V: ");
    int min_len = 0;
    int max_len = 0;
    while (true) {
      min_len = read_positive_int("Введите минимальную длину слова: ");
      max_len = read_positive_int("Введите максимальную длину слова: ");
      if (min_len > max_len) {
        std::cout << "Ошибка: min длины не может быть больше max длины\n";
        continue;
      }
      break;
    }

    v = generate_random_word_vector("V", size, min_len, max_len);
    print_word_vector("V", v);
  } else {
    std::ifstream file = open_input_file_with_retry();
    v = read_uppercase_word_vector_file(file, "V");
    print_word_vector("V", v);
  }
 // -------------------------------------------------------


  // создаем multimap для группировки по последней букве
  std::multimap<char, std::string> grouped;

  // разворачиваем вектор, чтобы порядок в группах был обратным
  const std::vector<std::string> reversed_words(v.rbegin(), v.rend());

  // добавляем пары: последняя буква -> слово
  for (const std::string& word : reversed_words) {
    const char key = get_last_char_or_throw(word);
    grouped.insert(std::make_pair(key, word)); // добавляем в multimap пару key - word
  }

  // выводим пары ключ - слово
  std::cout << "Ключ - Слово\n";
  for (const auto& item : grouped) {
    std::cout << "\"" << item.first << "\" - " << item.second << "\n";
  }
}
