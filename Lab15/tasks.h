#ifndef TASKS_H_
#define TASKS_H_

#include <fstream>
#include <string>
#include <utility>
#include <vector>

enum class InputMode {
  kKeyboard = 1,
  kRandom = 2,
  kFile = 3
};

class Human {
 public:
  // конструкторы класса human
  Human();
  Human(const std::string& name, int height);
  // деструктор класса human
  ~Human() = default;

  const std::string& name() const;
  int height() const;

  void set_name(const std::string& name);
  void set_height(int height);

  void print() const;

 private:
  std::string name_;
  int height_;
};

class Name {
 public:
  // конструкторы класса name
  Name();
  Name(const std::string& surname,
       const std::string& given_name,
       const std::string& patronymic);
  // деструктор класса name
  ~Name() = default;

  const std::string& surname() const;
  const std::string& given_name() const;
  const std::string& patronymic() const;

  void set_surname(const std::string& surname);
  void set_given_name(const std::string& given_name);
  void set_patronymic(const std::string& patronymic);

  std::string to_string() const;
  void print() const;

 private:
  std::string surname_;
  std::string given_name_;
  std::string patronymic_;
};

class PersonWithName {
 public:
  // конструкторы класса personwithname
  PersonWithName();
  PersonWithName(const Human& person, const Name& full_name);
  // деструктор класса personwithname
  ~PersonWithName() = default;

  const Human& person() const;
  const Name& full_name() const;

  void set_person(const Human& person);
  void set_full_name(const Name& full_name);

  void print() const;

 private:
  Human person_;
  Name full_name_;
};

class City {
 public:
  // конструкторы класса city
  City();
  explicit City(const std::string& name);
  City(const std::string& name,
       const std::vector<std::pair<std::string, int>>& routes);
  // деструктор класса city
  ~City() = default;

  const std::string& name() const;
  const std::vector<std::pair<std::string, int>>& routes() const;

  void set_name(const std::string& name);
  void add_route(const std::string& to_city, int cost);
  void clear_routes();

  void print() const;

 private:
  std::string name_;
  std::vector<std::pair<std::string, int>> routes_;
};

class CityFactory {
 public:
  // конструкторы класса cityfactory
  CityFactory();
  explicit CityFactory(const std::vector<City>& existing_cities);
  // деструктор класса cityfactory
  ~CityFactory() = default;

  City create_city(const std::string& name) const;
  City create_city(
      const std::string& name,
      const std::vector<std::pair<std::string, int>>& routes) const;
  std::vector<City> create_default_cities() const;

 private:
  std::vector<City> existing_cities_;
};

class Fraction {
 public:
  // конструкторы класса fraction
  Fraction();
  Fraction(int numerator, int denominator);
  // деструктор класса fraction
  ~Fraction() = default;

  int numerator() const;
  int denominator() const;

  void set_numerator(int numerator);
  void set_denominator(int denominator);

  Fraction add(const Fraction& other) const;
  Fraction subtract(const Fraction& other) const;
  Fraction multiply(const Fraction& other) const;
  Fraction divide(const Fraction& other) const;

  void reduce();
  void print() const;

 private:
  int numerator_;
  int denominator_;
};

bool is_valid_word(const std::string& text);
bool is_valid_phrase(const std::string& text);

std::string read_non_empty_line(const std::string& prompt);
std::string read_word(const std::string& prompt);
std::string read_phrase(const std::string& prompt);
std::string read_optional_word(const std::string& prompt);
int read_int(const std::string& prompt, int min_value, int max_value);
int read_mode_choice();
std::string read_file_path();
std::ifstream open_input_file_with_retry();

void run_task_human();
void run_task_names();
void run_task_person_with_name();
void run_task_cities();
void run_task_create_cities();
void run_task_fractions();

#endif
