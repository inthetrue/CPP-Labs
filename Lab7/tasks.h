#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

int randomInt(int min, int max);

int getValidNumber(const std::string& prompt, int min, int max);
int askUserMode(const std::string& taskName);

// Структура для Five12
struct StudentEGE {
    std::string surname;
    int score;
};

// Задача Sort2
void solve_sort2();

// Задача ExamTaskC14
void solve_exam_c14();

struct YearResult {
    int year;
    int month;
    int duration;
    int line_num;
};


int get_utf8_length(const std::string& s);
// Задача Five12
void solve_five12();

void create_ege_test_file(const std::string& filename);

#endif