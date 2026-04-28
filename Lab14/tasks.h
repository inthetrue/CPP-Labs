#ifndef TASKS_H_
#define TASKS_H_

#include <iosfwd>
#include <fstream>
#include <string>
#include <vector>

enum class InputMode {
  kKeyboard = 1,
  kRandom = 2,
  kFile = 3,
};

int read_int_or_throw(std::istream& input, const std::string& error_message);
int read_int_from_console(const std::string& prompt);
int read_positive_int(const std::string& prompt);
int read_non_negative_int(const std::string& prompt);
int read_range_border(const std::string& prompt);
void read_min_max(int* min_value, int* max_value);
int read_mode_choice();
std::string read_file_path();
std::ifstream open_input_file_with_retry();
bool is_uppercase_english_word(const std::string& word);
char get_last_char_or_throw(const std::string& word);

std::vector<int> read_int_vector_keyboard(const std::string& name);
std::vector<int> read_int_vector_with_size_keyboard(const std::string& name,
                                                    int size);
std::vector<int> read_int_vector_file(std::istream& input,
                                      const std::string& name);
std::vector<int> generate_random_int_vector(const std::string& name, int size,
                                            int min_value, int max_value);

std::vector<std::string> read_uppercase_word_vector_keyboard(
    const std::string& name);
std::vector<std::string> read_uppercase_word_vector_file(
    std::istream& input, const std::string& name);
std::vector<std::string> generate_random_word_vector(const std::string& name,
                                                      int size,
                                                      int min_len,
                                                      int max_len);

void print_int_vector(const std::string& name, const std::vector<int>& values);
void print_word_vector(const std::string& name,
                       const std::vector<std::string>& words);

void run_task_1();
void run_task_2();
void run_task_3();

#endif  // TASKS_H_
