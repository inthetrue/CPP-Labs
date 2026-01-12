#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <vector>

// Задача 1: Фитнес-центр
struct FitnessRecord {
    int year;
    int month;
    int duration;
    int client_code;
};

void fitness_task();


// Задача 2: Школа

union GradeData {
    short int readingSpeed; // 1 класс
    short int mathGrade;    // 2-3 класс
    float examScore;        // 4 класс
};

struct Pupil {
    std::string surname;
    std::string name;
    int classNum; // 1, 2, 3 или 4
    GradeData info; // Поле с union
};

void school_task();

int get_utf8_length(const std::string& s);
void print_cell(const std::string& s, int width);

// Задача 3: Студенты
struct Student {
    std::string name;
    int age;
    double avg_point;
};

void students_task();

void add_student(std::vector<Student>& students);
void print_students(const std::vector<Student>& students);
void print_high_gpa(const std::vector<Student>& students, double threshold);
void find_students_by_age(const std::vector<Student>& students, int age);
void edit_student(std::vector<Student>& students);
void calculate_average_gpa(const std::vector<Student>& students);

#endif