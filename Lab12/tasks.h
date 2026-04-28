#ifndef LAB12_TASKS_H_
#define LAB12_TASKS_H_

#include <deque>
#include <list>
#include <string>
#include <vector>

void run_stl2seq4();
void run_stl2seq9();
void run_stl2seq33();
void run_stl1iter9();

namespace tasks_internal {

int read_int_value(const std::string& prompt);
std::string read_text_value(const std::string& prompt);
int choose_input_mode();
std::vector<int> read_numbers_keyboard(int count);
std::vector<int> generate_random_numbers(int count);
std::vector<int> read_numbers_file(const std::string& file_name);
void print_deque(std::deque<int>::const_iterator begin,
                 std::deque<int>::const_iterator end);
void print_list(std::list<int>::const_iterator begin,
                std::list<int>::const_iterator end);
void print_source_numbers(const std::vector<int>& values);
std::vector<int> load_numbers_for_seq_task(
    bool (*is_valid)(int),
    const std::string& rule_text);
bool is_even_positive(int count);
bool is_odd_at_least_five(int count);
void write_numbers_to_file_keyboard(const std::string& target_file);
void write_numbers_to_file_random(const std::string& target_file);
void write_numbers_to_file_from_file(const std::string& target_file);
std::string prepare_file_for_stl1iter9();

}

#endif  // LAB12_TASKS_H_
