#include "tasks.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>

int randomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

// задача 1
void fitness_task() {
    using namespace std;
    cout << "Задача 1: Фитнес-центр" << endl;
    
    int n;
    cout << "Введите количество записей N: ";
    cin >> n;

    FitnessRecord best_record;
    best_record.duration = -1;

    cout << "Введите данные (формат: Год Месяц Длительность Код):" << endl;
    int mode;
    cout << "1) Ввести вручную  2) Сгенерировать случайно: ";
    cin >> mode;

    for (int i = 0; i < n; ++i) {
        FitnessRecord current;

        if (mode == 2) {
            current.year = randomInt(2000, 2010);
            current.month = randomInt(1, 12);
            current.duration = randomInt(21, 30);
            current.client_code = randomInt(10, 99);
            cout << "Год: " <<current.year << " | "<< "Месяц: " << current.month << " | " << "Продолжительность: " << current.duration << " | " << "Код: " << current.client_code << endl;
        } else {
            cin >> current.year >> current.month >> current.duration >> current.client_code;
        }

        if (current.duration > best_record.duration) {
            best_record = current;
        }
    }

    cout << "\nРезультат: " << endl;
    if (best_record.duration != -1) {
        cout << "Наибольшая продолжительность: " << best_record.duration << " | " << "Год: " << best_record.year << " | " << "Месяц: " << best_record.month << endl;
    } else {
        cout << "Данные не найдены" << endl;
    }
}

// задача 2

void input_pupil(Pupil& p) {
    using namespace std;
    cout << "Фамилия: "; cin >> p.surname;
    cout << "Имя: "; cin >> p.name;
    
    do {
        cout << "Класс (1-4): ";
        cin >> p.classNum;
    } while (p.classNum < 1 || p.classNum > 4);

    if (p.classNum == 1) {
        cout << "Скорость чтения (слов/мин): ";
        cin >> p.info.readingSpeed;
    } 
    else if (p.classNum == 4) {
        cout << "Баллы итоговой аттестации (1.0-100.0): ";
        cin >> p.info.examScore;
    } 
    else { // 2 и 3 классы
        cout << "Оценка по математике (1-10): ";
        cin >> p.info.mathGrade;
    }
}

int get_utf8_length(const std::string& s) {
    int len = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

void print_cell(const std::string& s, int width) {
    using namespace std;
    cout << s;
    int real_len = get_utf8_length(s);
    int padding = width - real_len;
    
    if (padding < 1) padding = 1;
    
    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }
}

void school_task() {
    using namespace std;
    cout << "\n Задача 2: " << endl;
    
    int n;
    cout << "Введите количество учеников: ";
    cin >> n;

    vector<Pupil> pupils(n);
    string filename = "pupils_data.txt";

    // 1. Ввод данных
    for (int i = 0; i < n; ++i) {
        cout << "\nУченик #" << i + 1 << ":" << endl;
        input_pupil(pupils[i]);
    }

    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Ошибка создания файла!" << endl;
        return;
    }

    for (const auto& p : pupils) {
        out << p.surname << " " << p.name << " " << p.classNum << " ";
        
        if (p.classNum == 1) out << p.info.readingSpeed;
        else if (p.classNum == 4) out << p.info.examScore;
        else out << p.info.mathGrade;
        
        out << endl;
    }
    out.close();
    cout << "\nДанные сохранены в '" << filename << "'." << endl;

    cout << "\nТаблица учеников: " << endl;
    ifstream in(filename);
    
    print_cell("Фамилия", 20);
    print_cell("Имя", 15);
    print_cell("Класс", 8);
    cout << "Инфо" << endl;
    
    cout << string(60, '-') << endl;

    string s_sur, s_name;
    int s_class;
    
    while (in >> s_sur >> s_name >> s_class) {
        print_cell(s_sur, 20);
        print_cell(s_name, 15);
        
        cout << left << setw(8) << s_class; 

        if (s_class == 1) {
            short speed; in >> speed;
            cout << speed << " сл/мин";
        } 
        else if (s_class == 4) {
            float score; in >> score;
            cout << score << " баллов";
        } 
        else {
            short grade; in >> grade;
            cout << grade << " (мат)";
        }
        cout << endl;
    }
    in.close();
}

// Задача 3: Студенты

void add_student(std::vector<Student>& students) {
    using namespace std;
    Student s;
    
    cout << "\nДобавление студента: " << endl;
    
    cout << "Имя: "; 
    cin >> s.name;

    while (true) {
        cout << "Возраст: ";
        if (cin >> s.age) {
            break; 
        } else {
            cout << "Ошибка! Введите целое число (например, 20)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Средний балл (например, 4.5): ";
        if (cin >> s.avg_point) {
            break;
        } else {
            cout << "Ошибка! Введите дробное число (через точку)." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    students.push_back(s);
    cout << "Студент добавлен." << endl;
}

void print_students(const std::vector<Student>& students) {
    using namespace std;
    if (students.empty()) {
        cout << "Список пуст." << endl;
        return;
    }

    cout << left << setw(5) << "№"; 
    
    print_cell("Имя", 20);
    print_cell("Возраст", 10);
    cout << "Балл" << endl;
    
    cout << string(45, '-') << endl;

    for (size_t i = 0; i < students.size(); ++i) {
        cout << left << setw(5) << i + 1;
        
        print_cell(students[i].name, 20); 
        
        cout << left << setw(10) << students[i].age;
        
        cout << students[i].avg_point << endl;
    }
}

void print_high_gpa(const std::vector<Student>& students, double threshold) {
    using namespace std;
    int count = 0;
    cout << "\nСтуденты с баллом выше " << threshold << ":" << endl;
    for (const auto& s : students) {
        if (s.avg_point > threshold) {
            cout << s.name << " (" << s.avg_point << ")" << endl;
            count++;
        }
    }
    cout << "Всего: " << count << endl;
}

void find_students_by_age(const std::vector<Student>& students, int age) {
    using namespace std;
    bool found = false;
    cout << "\nСтуденты возраста " << age << ":" << endl;
    for (const auto& s : students) {
        if (s.age == age) {
            cout << s.name << ", балл: " << s.avg_point << endl;
            found = true;
        }
    }
    if (!found) cout << "Не найдено." << endl;
}

void edit_student(std::vector<Student>& students) {
    using namespace std;
    print_students(students);
    if (students.empty()) return;

    int idx;

    while (true) {
        cout << "Введите номер студента для редактирования: ";
        if (cin >> idx) {
            break;
        } else {
            cout << "Введите число!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    idx--;

    if (idx >= 0 && idx < students.size()) {
        cout << "Редактирование " << students[idx].name << ". Введите новые данные." << endl;
        
        cout << "Новое имя: "; 
        cin >> students[idx].name;
        
        while (true) {
            cout << "Новый возраст: ";
            if (cin >> students[idx].age) break;
            else {
                cout << "Ошибка! Введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        while (true) {
            cout << "Новый балл: ";
            if (cin >> students[idx].avg_point) break;
            else {
                cout << "Ошибка! Введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        
        cout << "Обновлено." << endl;
    } else {
        cout << "Неверный номер." << endl;
    }
}

void calculate_average_gpa(const std::vector<Student>& students) {
    using namespace std;
    if (students.empty()) {
        cout << "Нет студентов." << endl;
        return;
    }
    double sum = 0;
    for (const auto& s : students) {
        sum += s.avg_point;
    }
    cout << "Общий средний балл по группе: " << sum / students.size() << endl;
}

void students_task() {
    using namespace std;
    vector<Student> group;
    int choice;

    do {
        cout << "\nМеню Студенты: " << endl;
        cout << "1. Добавить студента" << endl;
        cout << "2. Список всех" << endl;
        cout << "3. Кто отличник (>4.0)" << endl;
        cout << "4. Поиск по возрасту" << endl;
        cout << "5. Редактировать" << endl;
        cout << "6. Общий средний балл" << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "> ";
        cin >> choice;

        switch(choice) {
            case 1: add_student(group); break;
            case 2: print_students(group); break;
            case 3: print_high_gpa(group, 4.0); break;
            case 4: {
                int a; cout << "Введите возраст: "; cin >> a;
                find_students_by_age(group, a);
                break;
            }
            case 5: edit_student(group); break;
            case 6: calculate_average_gpa(group); break;
        }
    } while (choice != 0);
}