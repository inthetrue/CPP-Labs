#include "tasks.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <random>

const int kMinHeight = 50;
const int kMaxHeight = 250;
const int kMinCost = 1;
const int kMaxCost = 1000;

const std::vector<std::string> kRandomCities = {
    "Москва", "Санкт-Петербург", "Казань", "Екатеринбург",
    "Новосибирск", "Омск", "Самара", "Пермь",
    "Челябинск", "Уфа", "Красноярск", "Тюмень",
    "Иркутск", "Томск", "Воронеж", "Ростов-на-Дону",
    "Нижний-Новгород", "Владивосток", "Хабаровск", "Сочи",
    "Ярославль", "Калининград", "Барнаул", "Кемерово",
    "Саратов", "Волгоград"};

const std::vector<std::string> kRandomGivenNames = {
    "Александр", "Владимир", "Иван", "Петр",
    "Анна", "Мария", "Елена", "Ольга",
    "Клеопатра", "Сергей", "Николай", "Михаил"};

const std::vector<std::string> kRandomSurnames = {
    "Пушкин", "Маяковский", "Иванов", "Петров",
    "Сидоров", "Смирнов", "Кузнецов", "Попов",
    "Соколов", "Романов", "Лебедев", "Федоров"};

const std::vector<std::string> kRandomPatronymics = {
    "Иванович", "Петрович", "Сергеевич", "Николаевич",
    "Михайлович", "Александрович", "Владимирович", "Андреевич",
    "Павлович", "Дмитриевич", "Федорович", "Егорович"};
const int kMinIntValue = -1000000;
const int kMaxIntValue = 1000000;

bool is_extended_alpha(unsigned char ch) {
  if (std::isalpha(ch) != 0) {
    return true;
  }
  return ch >= 128;
}

int random_int(int min_value, int max_value) {
  static std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(min_value, max_value);
  return dist(rng);
}

std::string fraction_to_string(const Fraction& value) {
  return std::to_string(value.numerator()) + "/" +
         std::to_string(value.denominator());
}

std::string random_word(const std::vector<std::string>& values) {
  if (values.empty()) {
    return "value";
  }
  const int index = random_int(0, static_cast<int>(values.size()) - 1);
  return values[static_cast<std::size_t>(index)];
}

std::vector<std::string> random_unique_cities() {
  std::vector<std::string> cities = kRandomCities;
  static std::mt19937 rng(std::random_device{}());
  std::shuffle(cities.begin(), cities.end(), rng);
  return cities;
}

std::vector<City> build_scheme_cities(const std::vector<std::string>& names,
                                      const std::vector<int>& costs) {
  if (names.size() != 6) {
    std::cout << "Ошибка: некорректное число городов\n";
    return {};
  }
  if (costs.size() != 8) {
    std::cout << "Ошибка: некорректное число стоимостей\n";
    return {};
  }

  std::vector<City> cities;
  for (std::size_t i = 0; i < names.size(); ++i) {
    cities.push_back(City(names[i]));
  }

  // фиксируем индексы чтобы дальше не путать вершины схемы
  const std::vector<std::pair<int, int>> edges = {
      {1, 0}, {0, 5}, {5, 1}, {4, 5},
      {3, 4}, {1, 2}, {3, 2}, {0, 3}};

  // добавляем базовые ребра в одном месте чтобы проще менять схему
  for (std::size_t i = 0; i < edges.size(); ++i) {
    const int from_index = edges[i].first;
    const int to_index = edges[i].second;

    // берем ссылку на исходный город чтобы добавить ребро без копий
    City* from_city = &cities[static_cast<std::size_t>(from_index)];
    from_city->add_route(
        names[static_cast<std::size_t>(to_index)], costs[i]);
    // из города from_city по индексу from_index проводим путь в город из массива
    // names по индексу to_index со стоимостью costs[i]
  }

  // B <-> C
  cities[2].add_route(names[1], costs[5]);
  // C <-> D
  cities[2].add_route(names[3], costs[6]);
  // F <-> E
  cities[5].add_route(names[4], costs[3]);
  // обратный путь D -> A
  cities[3].add_route(names[0], costs[7]);
  // обратный путь A -> B
  cities[0].add_route(names[1], costs[0]);

  return cities;
}

Human::Human() : name_("Unknown"), height_(170) {}

Human::Human(const std::string& name, int height) {
  set_name(name);
  set_height(height);
}

const std::string& Human::name() const {
  return name_;
}

int Human::height() const {
  return height_;
}

void Human::set_name(const std::string& name) {
  if (!is_valid_phrase(name) || name.empty()) {
    name_ = "Unknown";
    return;
  }
  name_ = name;
}

void Human::set_height(int height) {
  if (height < kMinHeight || height > kMaxHeight) {
    height_ = 170;
    return;
  }
  height_ = height;
}

void Human::print() const {
  std::cout << name_ << ", рост: " << height_ << '\n';
}

Name::Name() = default;

Name::Name(const std::string& surname,
           const std::string& given_name,
           const std::string& patronymic) {
  set_surname(surname);
  set_given_name(given_name);
  set_patronymic(patronymic);
}

const std::string& Name::surname() const {
  return surname_;
}

const std::string& Name::given_name() const {
  return given_name_;
}

const std::string& Name::patronymic() const {
  return patronymic_;
}

void Name::set_surname(const std::string& surname) {
  if (surname == "0" || surname == "-") {
    surname_.clear();
    return;
  }
  if (!surname.empty() && !is_valid_word(surname)) {
    surname_.clear();
    return;
  }
  surname_ = surname;
}

void Name::set_given_name(const std::string& given_name) {
  if (given_name == "0" || given_name == "-") {
    given_name_.clear();
    return;
  }
  if (!given_name.empty() && !is_valid_word(given_name)) {
    given_name_.clear();
    return;
  }
  given_name_ = given_name;
}

void Name::set_patronymic(const std::string& patronymic) {
  if (patronymic == "0" || patronymic == "-") {
    patronymic_.clear();
    return;
  }
  if (!patronymic.empty() && !is_valid_word(patronymic)) {
    patronymic_.clear();
    return;
  }
  patronymic_ = patronymic;
}

std::string Name::to_string() const {
  std::string result;

  if (!surname_.empty()) {
    result += surname_;
  }
  if (!given_name_.empty()) {
    if (!result.empty()) {
      result += ' ';
    }
    result += given_name_;
  }
  if (!patronymic_.empty()) {
    if (!result.empty()) {
      result += ' ';
    }
    result += patronymic_;
  }

  return result;
}

void Name::print() const {
  std::cout << to_string() << '\n';
}

PersonWithName::PersonWithName()
    : person_(), full_name_() {}

PersonWithName::PersonWithName(const Human& person,
                               const Name& full_name)
    : person_(person) {
  set_full_name(full_name);
}

const Human& PersonWithName::person() const {
  return person_;
}

const Name& PersonWithName::full_name() const {
  return full_name_;
}

void PersonWithName::set_person(const Human& person) {
  person_ = person;
}

void PersonWithName::set_full_name(const Name& full_name) {
  full_name_ = full_name;
}

void PersonWithName::print() const {
  std::cout << "Человек: ";
  person_.print();
  std::cout << "Имя: ";
  full_name_.print();
}

City::City() : name_("Unknown") {}

City::City(const std::string& name) {
  set_name(name);
}

City::City(const std::string& name,
           const std::vector<std::pair<std::string, int>>& routes) {
  set_name(name);

  // используем add_route чтобы фильтровать некорректные пути в одном месте
  for (const std::pair<std::string, int>& route : routes) {
    add_route(route.first, route.second);
  }
}

const std::string& City::name() const {
  return name_;
}

const std::vector<std::pair<std::string, int>>& City::routes() const {
  return routes_;
}

void City::set_name(const std::string& name) {
  if (!is_valid_phrase(name)) {
    name_ = "Unknown";
    return;
  }
  name_ = name;
}

void City::add_route(const std::string& to_city, int cost) {
  if (!is_valid_word(to_city)) {
    return;
  }
  if (cost < kMinCost || cost > kMaxCost) {
    return;
  }
  routes_.push_back(std::make_pair(to_city, cost));
}

void City::clear_routes() {
  routes_.clear();
}

void City::print() const {
  std::cout << "Город: " << name_ << '\n';

  if (routes_.empty()) {
    std::cout << " Пути: нет\n";
    return;
  }

  std::cout << " Пути:\n";
  for (std::size_t i = 0; i < routes_.size(); ++i) {
    std::cout << "  => " << routes_[i].first
              << " (Стоимость: " << routes_[i].second << ")\n";
  }
}

CityFactory::CityFactory() = default;

CityFactory::CityFactory(const std::vector<City>& existing_cities)
    : existing_cities_(existing_cities) {}

City CityFactory::create_city(const std::string& name) const {
  return City(name);
}

City CityFactory::create_city(
    const std::string& name,
    const std::vector<std::pair<std::string, int>>& routes) const {
  if (existing_cities_.empty()) {
    return City(name, routes);
  }

  std::vector<std::pair<std::string, int>> filtered_routes;
  for (const std::pair<std::string, int>& route : routes) {
    if (route.first == name) {
      continue;
    }

    bool city_exists = false;
    for (const City& city : existing_cities_) {
      if (city.name() == route.first) {
        city_exists = true;
        break;
      }
    }
    if (!city_exists) {
      continue;
    }
    filtered_routes.push_back(route);
  }

  return City(name, filtered_routes);
}

std::vector<City> CityFactory::create_default_cities() const {
  const std::vector<std::string> names = {"A", "B", "C", "D", "E", "F"};
  const std::vector<int> costs = {5, 1, 1, 2, 2, 3, 4, 6};
  return build_scheme_cities(names, costs);
}

Fraction::Fraction() : numerator_(0), denominator_(1) {}

Fraction::Fraction(int numerator, int denominator)
    : numerator_(numerator), denominator_(1) {
  set_denominator(denominator);
  reduce();
}

int Fraction::numerator() const {
  return numerator_;
}

int Fraction::denominator() const {
  return denominator_;
}

void Fraction::set_numerator(int numerator) {
  numerator_ = numerator;
  reduce();
}

void Fraction::set_denominator(int denominator) {

  if (denominator == 0) {
    denominator_ = 1;
    reduce();
    return;
    // ноль в знаменателе заменяется на 1
  }
  denominator_ = denominator;
  reduce();
}

// складываем две дроби:
// умножает числ. первой на знам. второй, умножает числ. второй на знам. первой
// складывает их, знаменатели тоже перемножает и создает новую дробь
Fraction Fraction::add(const Fraction& other) const {
  const int new_numerator =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  const int new_denominator = denominator_ * other.denominator_;
  return Fraction(new_numerator, new_denominator);
}

// вычитаем одну дробь из другой
// логика: приводит дроби к общему знаменателю, считает новый числитель
// создает новую дробь
Fraction Fraction::subtract(const Fraction& other) const {
  const int new_numerator =
      numerator_ * other.denominator_ - other.numerator_ * denominator_;
  const int new_denominator = denominator_ * other.denominator_;
  return Fraction(new_numerator, new_denominator);
}

// умножает две дроби, числитель на числитель, знаменатель на знаменатель
Fraction Fraction::multiply(const Fraction& other) const {
  const int new_numerator = numerator_ * other.numerator_;
  const int new_denominator = denominator_ * other.denominator_;
  return Fraction(new_numerator, new_denominator);
}

// делит одну дробь на другую
// первая дробь умножается на перевернутую вторую
Fraction Fraction::divide(const Fraction& other) const {
  // оставляем защиту на случай прямого вызова метода вне задачи
  if (other.numerator_ == 0) {
    return Fraction(0, 1);
  }
  const int new_numerator = numerator_ * other.denominator_;
  const int new_denominator = denominator_ * other.numerator_;
  return Fraction(new_numerator, new_denominator);
}

// сокращает дробь алгоритмом евклида
void Fraction::reduce() {
  if (denominator_ < 0) {
    numerator_ = -numerator_;
    denominator_ = -denominator_;
  }

  // для нулевой дроби оставляем вид 0/1 чтобы не множились варианты 0/x
  if (numerator_ == 0) {
    denominator_ = 1;
    return;
  }

  // сокращаем
  int a = numerator_;
  if (a < 0) {
    a = -a;
  }
  int b = denominator_;
  if (b < 0) {
    b = -b;
  }

  // алгоритм евклида для сокращения дробей
  while (b != 0) {
    const int temp = a % b;
    a = b;
    b = temp;
  }
  const int divisor = a;
  numerator_ /= divisor;
  denominator_ /= divisor;
}

void Fraction::print() const {
  std::cout << numerator_ << '/' << denominator_ << '\n';
}

bool is_valid_word(const std::string& text) {
  if (text.empty()) {
    return false;
  }

  // фильтр символов и служебных слов
  for (unsigned char ch : text) {
    if (ch == '-') {
      continue;
    }
    if (!is_extended_alpha(ch)) {
      return false;
    }
  }

  // убираем случаи город- и -город
  if (text.front() == '-' || text.back() == '-') {
    return false;
  }

  return true;
}

bool is_valid_phrase(const std::string& text) {
  if (text.empty()) {
    return false;
  }

  bool has_letter = false;

  for (unsigned char ch : text) {
    if (ch == ' ' || ch == '-' || ch == '\'') {
      continue;
    }
    if (!is_extended_alpha(ch)) {
      return false;
    }
    has_letter = true;
  }

  return has_letter;
}

std::string read_non_empty_line(const std::string& prompt) {
  while (true) {
    std::cout << prompt;

    std::string value;
    std::getline(std::cin, value);

    if (!std::cin.good()) {
      std::cin.clear();
      continue;
    }

    if (value.empty()) {
      std::cout << "Ошибка: строка не может быть "
                << "пустой\n";
      continue;
    }

    return value;
  }
}

std::string read_word(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);
    if (!is_valid_word(value)) {
      std::cout << "Ошибка: вводите только "
                << "буквы и дефис\n";
      continue;
    }
    return value;
  }
}

std::string read_phrase(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);
    if (!is_valid_phrase(value)) {
      std::cout << "Ошибка: недопустимые символы\n";
      continue;
    }
    return value;
  }
}

std::string read_optional_word(const std::string& prompt) {
  while (true) {
    const std::string value = read_non_empty_line(prompt);

    if (value == "-" || value == "0") {
      return "";
    }

    if (!is_valid_word(value)) {
      std::cout << "Ошибка: введите слово, "
                << "или - , или 0\n";
      continue;
    }
    return value;
  }
}

int read_int(const std::string& prompt, int min_value, int max_value) {
  while (true) {
    const std::string raw = read_non_empty_line(prompt);

    std::size_t start = 0;
    if (raw[0] == '+' || raw[0] == '-') {
      if (raw.size() == 1) {
        std::cout << "Ошибка: введите целое число\n";
        continue;
      }
      start = 1;
    }

    bool valid_integer = true;
    for (std::size_t i = start; i < raw.size(); ++i) {
      if (std::isdigit(static_cast<unsigned char>(raw[i])) == 0) {
        valid_integer = false;
        break;
      }
    }
    if (!valid_integer) {
      std::cout << "Ошибка: введите целое число\n";
      continue;
    }

    long long value_ll = 0;
    const int sign = (raw[0] == '-') ? -1 : 1;
    for (std::size_t i = start; i < raw.size(); ++i) {
      const int digit = raw[i] - '0';
      value_ll = value_ll * 10 + digit;
      if (value_ll > 2147483647LL) {
        break;
      }
    }

    value_ll *= sign;
    if (value_ll < static_cast<long long>(kMinIntValue) ||
        value_ll > static_cast<long long>(kMaxIntValue)) {
      std::cout << "Ошибка: число слишком большое\n";
      continue;
    }
    const int value = static_cast<int>(value_ll);

    if (value < min_value || value > max_value) {
      std::cout << "Ошибка: число вне диапазона ["
                << min_value << ", " << max_value << "]\n";
      continue;
    }
    return value;
  }
}

int read_mode_choice() {
  while (true) {
    std::cout << "Выберите способ "
              << "заполнения данных\n";
    std::cout << "1. С клавиатуры\n";
    std::cout << "2. Случайно\n";
    std::cout << "3. Из файла\n";
    std::cout << "Введите вариант: ";

    int mode = 0;
    if (!(std::cin >> mode)) {
      std::cout << "Ошибка: введите 1, 2 или 3\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (mode < static_cast<int>(InputMode::kKeyboard) ||
        mode > static_cast<int>(InputMode::kFile)) {
      std::cout << "Ошибка: вариант "
                << "должен быть 1, 2 или 3\n";
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
      std::cout << "Ошибка: не удалось "
                << "прочитать путь\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return path;
  }
}

std::ifstream open_input_file_with_retry() {
  while (true) {
    const std::string path = read_file_path();
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cout << "Ошибка: не удалось открыть файл, "
                << "попробуйте снова\n";
      continue;
    }
    std::cout << "Чтение из файла начато\n";
    return file;
  }
}

std::string read_word_from_file(std::ifstream& file) {
  std::string value;
  if (!(file >> value)) {
    std::cout << "Ошибка: не хватает данных в файле\n";
    return "";
  }
  return value;
}

std::string get_word_value(int mode,
                           std::ifstream& file,
                           const std::string& prompt,
                           const std::vector<std::string>& random_values) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_word(prompt);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const std::string value = random_word(random_values);
    return value;
  }

  const std::string value = read_word_from_file(file);
  if (value.empty()) {
    const std::string fallback = random_word(random_values);
    std::cout << prompt << fallback << '\n';
    return fallback;
  }
  if (!is_valid_word(value)) {
    std::cout << "Ошибка: некорректное слово в файле\n";
    const std::string fallback = random_word(random_values);
    std::cout << prompt << fallback << '\n';
    return fallback;
  }
  std::cout << prompt << value << '\n';
  return value;
}

std::string get_optional_word_value(
    int mode,
    std::ifstream& file,
    const std::string& prompt,
    const std::vector<std::string>& random_values) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_optional_word(prompt);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const int roll = random_int(1, 100);
    if (roll <= 10) {
      return "";
    }
    const std::string value = random_word(random_values);
    return value;
  }

  const std::string value = read_word_from_file(file);
  if (value.empty()) {
    return "";
  }
  std::cout << prompt << value << '\n';
  if (value == "-" || value == "0") {
    return "";
  }
  if (!is_valid_word(value)) {
    std::cout << "Ошибка: некорректный атрибут в файле\n";
    return "";
  }
  return value;
}

int get_int_value(int mode,
                  std::ifstream& file,
                  const std::string& prompt,
                  int min_value,
                  int max_value) {
  if (mode == static_cast<int>(InputMode::kKeyboard)) {
    return read_int(prompt, min_value, max_value);
  }

  if (mode == static_cast<int>(InputMode::kRandom)) {
    const int value = random_int(min_value, max_value);
    return value;
  }

  int value = 0;
  if (!(file >> value)) {
    std::cout << "Ошибка: не хватает чисел в файле\n";
    return min_value;
  }
  if (value < min_value || value > max_value) {
    std::cout << "Ошибка: число в файле вне диапазона\n";
    return min_value;
  }
  std::cout << prompt << value << '\n';
  return value;
}

// Задача 1:
void run_task_human() {
  std::cout << "\nЗадача человек\n";
  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }
  const int count = read_int(
      "Введите количество людей: ", 1, 30);

  std::vector<Human> people;
  for (int i = 0; i < count; ++i) {
    const std::string prompt_name =
        "Введите имя человека " +
        std::to_string(i + 1) + ": ";
    const std::string prompt_height =
        "Введите рост человека " +
        std::to_string(i + 1) + ": ";
    const Human person(
        get_word_value(mode, file, prompt_name, kRandomGivenNames),
        get_int_value(mode, file, prompt_height, kMinHeight, kMaxHeight));
    people.push_back(person);
  }

  std::cout << "\nРезультат\n";
  for (const Human& person : people) {
    person.print();
  }
}

// Задача 1.2
void run_task_names() {
  std::cout << "\nЗадача имена\n";
  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }
  const int count = read_int(
      "Введите количество имен: ", 1, 30);

  std::vector<Name> names;
  for (int i = 0; i < count; ++i) {
    while (true) {
      const std::string prompt_surname =
          "Введите фамилию для имени " +
          std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_given =
          "Введите личное имя для имени " +
          std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_patronymic =
          "Введите отчество для имени " +
          std::to_string(i + 1) + " или - если нет: ";

      // создаем сущность name, но хотя бы одна часть должна быть задана
      const Name current(
          get_optional_word_value(mode, file, prompt_surname, kRandomSurnames),
          get_optional_word_value(mode, file, prompt_given, kRandomGivenNames),
          get_optional_word_value(
              mode, file, prompt_patronymic, kRandomPatronymics));
      if (current.to_string().empty()) {
        std::cout << "Ошибка: хотя бы один аргумент "
                  << "должен быть задан\n";
        continue;
      }
      names.push_back(current);
      break;
    }
  }

  std::cout << "\nРезультат\n";
  for (const Name& current : names) {
    current.print();
  }
}

// Задача 2
void run_task_person_with_name() {
  std::cout << "\nЗадача человек с именем\n";
  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }
  const int count = read_int(
      "Введите количество человек с именем: ", 1, 30);

  std::vector<PersonWithName> people;
  for (int i = 0; i < count; ++i) {
    while (true) {
      const std::string prompt_surname =
          "Введите фамилию для человека " +
          std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_given =
          "Введите личное имя для человека " +
          std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_patronymic =
          "Введите отчество для человека " +
          std::to_string(i + 1) + " или - если нет: ";
      const std::string prompt_height =
          "Введите рост для человека " +
          std::to_string(i + 1) + ": ";

      const Name full_name(
          get_optional_word_value(mode, file, prompt_surname, kRandomSurnames),
          get_optional_word_value(mode, file, prompt_given, kRandomGivenNames),
          get_optional_word_value(
              mode, file, prompt_patronymic, kRandomPatronymics));
      if (full_name.to_string().empty()) {
        std::cout << "Ошибка: хотя бы один аргумент "
                  << "должен быть задан\n";
        continue;
      }

      // человек хранит имя через сущность Name
      const Human human(full_name.to_string(),
                        get_int_value(mode, file, prompt_height,
                                      kMinHeight, kMaxHeight));

      people.push_back(PersonWithName(human, full_name));
      break;
    }
  }

  std::cout << "\nРезультат\n";
  for (const PersonWithName& person : people) {
    person.print();
  }
}

// Задача 3
void run_task_cities() {
  std::cout << "\nЗадача города\n";
  std::vector<City> cities;

  while (true) {
    std::cout << "\n1. Добавить город\n";
    std::cout << "2. Добавить путь\n";
    std::cout << "3. Показать все города\n";
    std::cout << "4. Пример\n";
    std::cout << "0. Выход\n";
    const int command = read_int("Введите команду: ", 0, 4);

    if (command == 0) {
      break;
    }

    if (command == 1) {
      const int add_mode = read_mode_choice();
      std::string city_name;

      if (add_mode == static_cast<int>(InputMode::kKeyboard)) {
        city_name = read_phrase("Введите название города: ");
      } else if (add_mode == static_cast<int>(InputMode::kRandom)) {
        // подбираем случайное название города без повторов
        bool added = false;
        for (std::size_t attempt = 0;
             attempt < kRandomCities.size(); ++attempt) {
          const std::string candidate = random_word(kRandomCities);
          bool exists = false;
          for (const City& city : cities) {
            if (city.name() == candidate) {
              exists = true;
              break;
            }
          }
          if (!exists) {
            city_name = candidate;
            added = true;
            break;
          }
        }
        if (!added) {
          std::cout << "Ошибка: свободных случайных названий не осталось\n";
          continue;
        }
        std::cout << "Добавлен город: " << city_name << '\n';
      } else {
        std::ifstream input_file = open_input_file_with_retry();
        int added_count = 0;
        std::string file_city_name;
        while (input_file >> file_city_name) {
          if (!is_valid_word(file_city_name)) {
            continue;
          }

          bool exists_in_list = false;
          for (const City& city : cities) {
            if (city.name() == file_city_name) {
              exists_in_list = true;
              break;
            }
          }
          if (exists_in_list) {
            continue;
          }

          cities.push_back(City(file_city_name));
          ++added_count;
        }
        std::cout << "Добавлено городов: "
                  << added_count << '\n';
        continue;
      }

      bool exists = false;
      for (const City& city : cities) {
        if (city.name() == city_name) {
          exists = true;
          break;
        }
      }
      if (exists) {
        std::cout << "Ошибка: такой город уже существует\n";
        continue;
      }
      cities.push_back(City(city_name));
      std::cout << "Город добавлен\n";
      continue;
    }

    if (command == 2) {
      if (cities.size() < 2) {
        std::cout << "Ошибка: нужно добавить минимум 2 города\n";
        continue;
      }

      std::cout << "Список городов\n";
      for (std::size_t i = 0; i < cities.size(); ++i) {
        std::cout << (i + 1) << ". " << cities[i].name() << '\n';
      }

      int from_index = 0;
      int to_index = 0;
      while (true) {
        from_index = read_int("Номер города откуда: ",
                              1, static_cast<int>(cities.size()));
        to_index = read_int("Номер города куда: ",
                            1, static_cast<int>(cities.size()));
        if (from_index == to_index) {
          std::cout << "Ошибка: нельзя добавить путь в самого себя\n";
          continue;
        }

        // проверка на наличие существующего пути
        bool exists = false;
        const std::vector<std::pair<std::string, int>>& routes =
            cities[static_cast<std::size_t>(from_index - 1)].routes();
        for (const std::pair<std::string, int>& route : routes) {
          if (route.first ==
              cities[static_cast<std::size_t>(to_index - 1)].name()) {
            exists = true;
            break;
          }
        }
        if (exists) {
          std::cout << "Ошибка: такой путь уже существует\n";
          continue;
        }
        break;
      }
      // добавляем стоимость пути
      const int cost = read_int("Стоимость пути: ", kMinCost, kMaxCost);
      cities[static_cast<std::size_t>(from_index - 1)].add_route(
          cities[static_cast<std::size_t>(to_index - 1)].name(), cost);
      std::cout << "Путь добавлен\n";
      continue;
    }

    // вывод всех городов
    if (command == 3) {
      if (cities.empty()) {
        std::cout << "Города еще не добавлены\n";
        continue;
      }
      std::cout << "Текущий граф\n";
      for (std::size_t i = 0; i < cities.size(); ++i) {
        std::cout << (i + 1) << " - ";
        cities[i].print();
        std::cout << '\n';
      }
      continue;
    }

    // пример
    if (command == 4) {
      const std::vector<std::string> names = {
          "A", "B", "C", "D", "E", "F"};
      const std::vector<int> costs = {5, 1, 1, 2, 2, 3, 4, 6};
      const std::vector<City> example_cities = build_scheme_cities(names, costs);
      const std::vector<std::string> labels = {
          "A", "B", "C", "D", "E", "F"};

      std::cout << "Пример графа\n";
      for (std::size_t i = 0; i < example_cities.size(); ++i) {
        std::cout << labels[i] << " - ";
        example_cities[i].print();
        std::cout << '\n';
      }
      continue;
    }
  }
}

// Задача 4
void run_task_create_cities() {
  std::cout << "\nЗадача создаем города\n";

  // размер графа
  const int max_cities = static_cast<int>(kRandomCities.size());
  const int cities_count = read_int(
      "Сколько городов создать (например 6): ",
      2, max_cities);

  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }

  // список городов нужен для построения графа
  std::vector<City> cities;
  CityFactory empty_factory;

  // рандомная генерация
  if (mode == static_cast<int>(InputMode::kRandom)) {
    const std::vector<std::string> random_names = random_unique_cities();
    for (int i = 0; i < cities_count; ++i) {
      const std::string city_name =
          random_names[static_cast<std::size_t>(i)];
      cities.push_back(empty_factory.create_city(city_name));
      std::cout << "Добавлен город: " << city_name << '\n';
    }
  } else {
    // заполнение с клавиатуры или из файла
    for (int i = 0; i < cities_count; ++i) {
      const std::string prompt_name =
          "Введите название города " +
          std::to_string(i + 1) + ": ";
      while (true) {
        const std::string city_name = get_word_value(
            mode, file, prompt_name, kRandomCities);

        bool already_exists = false;
        for (const City& city : cities) {
          if (city.name() == city_name) {
            already_exists = true;
            break;
          }
        }
        if (already_exists) {
          std::cout << "Ошибка: такой город уже есть, "
                    << "введите другое название\n";
          continue;
        }
        cities.push_back(empty_factory.create_city(city_name));
        break;
      }
    }
  }

  // создаем матрицу, чтобы видеть какие пути уже были добавлены
  const int max_edges = cities_count * (cities_count - 1);
  std::vector<std::vector<bool>> used_edges(
      static_cast<std::size_t>(cities_count),
      std::vector<bool>(static_cast<std::size_t>(cities_count), false));

      // заполнение рандомом, автоматически создает пути
  if (mode == static_cast<int>(InputMode::kRandom)) {

    int created_edges = 0;
    const int min_edges = std::max(1, max_edges / 3);
    while (created_edges < max_edges) {

      if (created_edges >= min_edges &&
          random_int(1, 100) <= 10) {
        break;
      }
      const int from_index = random_int(1, cities_count);
      const int to_index = random_int(1, cities_count);
      if (from_index == to_index) {
        continue;
      }
      if (used_edges[static_cast<std::size_t>(from_index - 1)]
                    [static_cast<std::size_t>(to_index - 1)]) {
        continue;
      }

      const int cost = random_int(kMinCost, kMaxCost);
      std::vector<std::pair<std::string, int>> routes =
          cities[static_cast<std::size_t>(from_index - 1)].routes();
      routes.push_back(std::make_pair(
          cities[static_cast<std::size_t>(to_index - 1)].name(), cost));
      const CityFactory route_factory(cities);
      cities[static_cast<std::size_t>(from_index - 1)] =
          route_factory.create_city(
              cities[static_cast<std::size_t>(from_index - 1)].name(),
              routes);
      used_edges[static_cast<std::size_t>(from_index - 1)]
                [static_cast<std::size_t>(to_index - 1)] = true;
      ++created_edges;
    }

    // после рандома даем руками донастроить граф
    while (created_edges < max_edges) {
      std::cout << "\nТекущие пути\n";
      for (int j = 0; j < cities_count; ++j) {
        std::cout << (j + 1) << " - ";
        cities[static_cast<std::size_t>(j)].print();
        std::cout << '\n';
      }

      std::cout << "\n1. Добавить путь\n";
      std::cout << "2. Хватит путей\n";
      const int action = read_int("Выберите вариант: ", 1, 2);
      if (action == 2) {
        break;
      }

      std::cout << "\nПуть " << (created_edges + 1) << '\n';
      for (int j = 0; j < cities_count; ++j) {
        std::cout << (j + 1) << ". "
                  << cities[static_cast<std::size_t>(j)].name() << '\n';
      }

      int from_index = 0;
      int to_index = 0;
      while (true) {
        from_index = read_int(
            "Номер города откуда: ", 1, cities_count);
        to_index = read_int(
            "Номер города куда: ", 1, cities_count);
        if (from_index == to_index) {
          std::cout << "Ошибка: город не может вести сам в себя\n";
          continue;
        }
        if (used_edges[static_cast<std::size_t>(from_index - 1)]
                      [static_cast<std::size_t>(to_index - 1)]) {
          std::cout << "Ошибка: путь из этого города "
                    << "в этот город уже есть\n";
          continue;
        }
        break;
      }

      const int cost = read_int(
          "Стоимость пути: ", kMinCost, kMaxCost);
      std::vector<std::pair<std::string, int>> routes =
          cities[static_cast<std::size_t>(from_index - 1)].routes();
      routes.push_back(std::make_pair(
          cities[static_cast<std::size_t>(to_index - 1)].name(), cost));
      const CityFactory route_factory(cities);
      cities[static_cast<std::size_t>(from_index - 1)] =
          route_factory.create_city(
              cities[static_cast<std::size_t>(from_index - 1)].name(),
              routes);
      used_edges[static_cast<std::size_t>(from_index - 1)]
                [static_cast<std::size_t>(to_index - 1)] = true;
      ++created_edges;
    }

    // ввод с файла/клавиатуры
  } else {
    int created_edges = 0;
    while (created_edges < max_edges) {
      std::cout << "\nТекущие пути\n";
      for (int j = 0; j < cities_count; ++j) {
        std::cout << (j + 1) << " - ";
        cities[static_cast<std::size_t>(j)].print();
        std::cout << '\n';
      }

      std::cout << "\n1. Добавить путь\n";
      std::cout << "2. Хватит путей\n";
      const int action = get_int_value(
          mode, file, "Выберите вариант: ", 1, 2);
      if (action == 2) {
        break;
      }

      std::cout << "\nПуть " << (created_edges + 1) << '\n';
      for (int j = 0; j < cities_count; ++j) {
        std::cout << (j + 1) << ". "
                  << cities[static_cast<std::size_t>(j)].name() << '\n';
      }

      int from_index = 0;
      int to_index = 0;
      while (true) {
        from_index = get_int_value(
            mode, file, "Номер города откуда: ", 1, cities_count);
        to_index = get_int_value(
            mode, file, "Номер города куда: ", 1, cities_count);
        if (from_index == to_index) {
          std::cout << "Ошибка: город не может вести сам в себя\n";
          continue;
        }
        if (used_edges[static_cast<std::size_t>(from_index - 1)]
                      [static_cast<std::size_t>(to_index - 1)]) {
          std::cout << "Ошибка: путь из этого города "
                    << "в этот город уже есть\n";
          continue;
        }
        break;
      }

      const int cost = get_int_value(
          mode, file, "Стоимость пути: ", kMinCost, kMaxCost);
      std::vector<std::pair<std::string, int>> routes =
          cities[static_cast<std::size_t>(from_index - 1)].routes();
      routes.push_back(std::make_pair(
          cities[static_cast<std::size_t>(to_index - 1)].name(), cost));
      const CityFactory route_factory(cities);
      cities[static_cast<std::size_t>(from_index - 1)] =
          route_factory.create_city(
              cities[static_cast<std::size_t>(from_index - 1)].name(),
              routes);
      used_edges[static_cast<std::size_t>(from_index - 1)]
                [static_cast<std::size_t>(to_index - 1)] = true;
      ++created_edges;
    }
  }

  // вывод результата: номер, название, список путей
  std::cout << "\nРезультат\n";
  std::cout << "Граф городов\n";
  for (int i = 0; i < cities_count; ++i) {
    std::cout << (i + 1) << " - ";
    cities[static_cast<std::size_t>(i)].print();
    std::cout << '\n';
  }

  // поиск отдельных изолированных городов: вершин, которые вообще ни с кем не связаны
  std::vector<std::string> isolated;
  for (std::size_t i = 0; i < cities.size(); ++i) {
    bool has_incoming = false;
    for (const City& city : cities) {
      for (const std::pair<std::string, int>& route : city.routes()) {
        if (route.first == cities[i].name()) {
          has_incoming = true;
        }
      }
    }
    if (cities[i].routes().empty() && !has_incoming) {
      isolated.push_back(cities[i].name());
    }
  }

  if (!isolated.empty()) {
    std::cout << "Изолированные города: ";
    for (std::size_t i = 0; i < isolated.size(); ++i) {
      std::cout << isolated[i];
      if (i + 1 != isolated.size()) {
        std::cout << ", ";
      }
    }
    std::cout << '\n';
  }
}


// Задача 5
void run_task_fractions() {
  std::cout << "\nЗадача дроби\n";
  const int mode = read_mode_choice();
  std::ifstream file;
  if (mode == static_cast<int>(InputMode::kFile)) {
    file = open_input_file_with_retry();
  }
  int min_value = kMinIntValue;
  int max_value = kMaxIntValue;

  if (mode == static_cast<int>(InputMode::kRandom)) {
    while (true) {
      min_value = read_int(
          "Введите min для случайного "
          "заполнения: ",
          kMinIntValue, kMaxIntValue);
      max_value = read_int(
          "Введите max для случайного "
          "заполнения: ",
          kMinIntValue, kMaxIntValue);
      if (min_value > max_value) {
        std::cout << "Ошибка: min не может "
                  << "быть больше max\n";
        continue;
      }
      break;
    }
  }

  const int count = read_int(
      "Сколько дробей создать: ", 2, 20);
  std::vector<Fraction> fractions;
  for (int i = 0; i < count; ++i) {
    const std::string prompt_numerator =
        "Введите числитель дроби " + std::to_string(i + 1) + ": ";
    const std::string prompt_denominator =
        "Введите знаменатель дроби " + std::to_string(i + 1) + ": ";

    const int numerator = get_int_value(
        mode, file, prompt_numerator, min_value, max_value);
    int denominator = 0;
    while (true) {
      denominator = get_int_value(
          mode, file, prompt_denominator, min_value, max_value);
      if (denominator == 0) {
        std::cout << "Ошибка: знаменатель "
                  << "не может быть равен нулю\n";
        continue;
      }
      break;
    }
    fractions.push_back(Fraction(numerator, denominator));
  }

  const Fraction first = fractions[0];
  const Fraction second = fractions[1];
  const Fraction five(5, 1);

  const Fraction sum = first.add(second);
  const Fraction diff = first.subtract(second);
  const Fraction prod = first.multiply(second);

  std::cout << "\nСозданные дроби\n";
  for (int i = 0; i < count; ++i) {
    std::cout << "f" << (i + 1) << " = "
              << fraction_to_string(fractions[static_cast<std::size_t>(i)])
              << '\n';
  }

  std::cout << "\nПримеры методов\n";
  std::cout << fraction_to_string(first) << " + "
            << fraction_to_string(second) << " = "
            << fraction_to_string(sum) << '\n';
  std::cout << fraction_to_string(first) << " - "
            << fraction_to_string(second) << " = "
            << fraction_to_string(diff) << '\n';
  std::cout << fraction_to_string(first) << " * "
            << fraction_to_string(second) << " = "
            << fraction_to_string(prod) << '\n';

  if (second.numerator() == 0) {
    std::cout << fraction_to_string(first) << " / "
              << fraction_to_string(second)
              << " = ошибка, деление на нулевую дробь невозможно\n";
  } else {
    const Fraction quot = first.divide(second);
    std::cout << fraction_to_string(first) << " / "
              << fraction_to_string(second) << " = "
              << fraction_to_string(quot) << '\n';
  }

  std::cout << "\nЦепочка f1.add(f2).divide(f3).subtract(5/1)\n";
  if (count < 3) {
    std::cout << "Для цепочки нужно минимум 3 дроби\n";
  } else {
    const Fraction third = fractions[2];
    if (third.numerator() == 0) {
      std::cout << "Ошибка: f3 равна нулю, цепочку деления выполнить нельзя\n";
      return;
    }
    const Fraction chain = first.add(second).divide(third).subtract(five);
    std::cout << "(" << fraction_to_string(first) << " + "
              << fraction_to_string(second) << ") / "
              << fraction_to_string(third) << " - 5/1 = "
              << fraction_to_string(chain) << '\n';
  }
}
