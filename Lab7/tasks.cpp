#include "tasks.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>    

int randomInt(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int getValidNumber(const std::string& prompt, int min, int max) {
    using namespace std;
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= min && value <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            } else {
                cout << "Ошибка! Число должно быть от " << min << " до " << max << "." << endl;
            }
        } else {
            cout << "Ошибка! Введите целое число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера
        }
    }
}

int askUserMode(const std::string& taskName) {
    using namespace std;
    cout << "\n--- Задача: " << taskName << " ---" << endl;
    cout << "Выберите режим ввода данных:" << endl;
    cout << "1. Ввести вручную с клавиатуры" << endl;
    cout << "2. Сгенерировать случайно" << endl;
    
    return getValidNumber("Ваш выбор > ", 1, 2);
}

// Задача Sort2 сортировка пузырьком
void solve_sort2() {
    using namespace std;
    cout << "\nЗадача Sort2: Сортировка простыми обменами" << endl;

    int n = getValidNumber("Введите размер массива N (1-10000): ", 1, 10000);

    vector<int> arr(n);
    int mode = askUserMode("Sort2");
    
    cout << "Данные массива:" << endl;
    for (int i = 0; i < n; ++i) {
        if (mode == 2) {
            arr[i] = randomInt(1, 100);
            cout << arr[i] << " ";
        } 
        else {
            while(!(cin >> arr[i])) {
                cout << "Ошибка! Введите число: ";
                cin.clear(); cin.ignore(10000, '\n');
            }
        }
    }
    if (mode == 2) cout << endl;
    if (mode == 1) cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string filename = "sort_log.txt";
    ofstream f(filename);
    if (!f.is_open()) {
        cerr << "Ошибка создания файла" << endl;
        return;
    }

    f << "Исходный массив: ";
    for (int x : arr) f << x << " ";
    f << endl << endl;

    // Сортировка пузырьком
    for (int i = 0; i < n - 1; ++i) {
        bool changed = false;
        
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                
                changed = true;
            }
        }

        f << "Итерация " << i + 1 << ": ";
        int split_idx = n - 1 - i;
        for (int k = 0; k < n; ++k) {
            if (k == split_idx) f << "| ";
            f << arr[k] << " ";
        }
        f << endl;
    }

    f.close();
    cout << "Протокол записан в '" << filename << "'" << endl;
    cout << "Результат: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

// задача ExamTaskC14

void solve_exam_c14() {
    using namespace std;
    cout << "\nЗадача ExamTaskC14: Фитнес" << endl;

    int target_k = getValidNumber("Введите искомый код клиента K (10-99): ", 10, 99);

    int n = getValidNumber("Введите количество записей N (1-1000): ", 1, 1000);

    vector<YearResult> results;
    bool found_record = false;

    cout << "Введите данные (Год, Месяц, Код, Длительность):" << endl;
    int mode = askUserMode("Ввод данных");
    
    for (int i = 0; i < n; ++i) {
        int current_line = i + 1;
        int year, month, code, duration;
        
        if (mode == 2) {
            year = randomInt(2000, 2010);
            month = randomInt(1, 12);
            code = randomInt(10, 99);
            duration = randomInt(0, 30);
            cout << current_line << ". " << "Год: " << year << " | " << "Месяц: " << month << " | " << "Код: " << code << " | " << "Длит: " << duration << endl;
        } else {
            cout << "\nЗапись #" << current_line << endl;
            year = getValidNumber("Год (2000-2010): ", 2000, 2010);
            month = getValidNumber("Месяц (1-12): ", 1, 12);
            code = getValidNumber("Код клиента (10-99): ", 10, 99);
            duration = getValidNumber("Продолжительность (0-30): ", 0, 30);
        }

        if (code != target_k) continue;
        if (duration == 0) continue;

        found_record = true;

        bool year_found = false;
        for (auto& res : results) {
            if (res.year == year) {
                year_found = true;
                
                if (duration < res.duration) {
                    res.month = month;
                    res.duration = duration;
                    res.line_num = current_line;
                } 
                else if (duration == res.duration) {
                    if (month > res.month) {
                        res.month = month;
                        res.line_num = current_line;
                    }
                }
                break;
            }
        }

        if (!year_found) {
            YearResult new_res;
            new_res.year = year;
            new_res.month = month;
            new_res.duration = duration;
            new_res.line_num = current_line;
            results.push_back(new_res);
        }
    }

    cout << "\nРезультат: " << endl;
    if (!found_record) {
        cout << "Нет данных" << endl;
    } else {
        for (size_t i = 0; i < results.size(); ++i) {
            for (size_t j = 0; j < results.size() - 1; ++j) {
                if (results[j].year > results[j + 1].year) {
                    YearResult temp = results[j];
                    results[j] = results[j + 1];
                    results[j + 1] = temp;
                }
            }
        }

        for (const auto& res : results) {
            cout << res.line_num << ". " << "Год: " << res.year << " | " << "Месяц: " << res.month << " | " << "Продолжительность: " << res.duration << endl;
        }
    }
}

// ЗАДАЧА Five12

int get_utf8_length(const std::string& s) {
    int len = 0;
    for (unsigned char c : s) {
        if ((c & 0xC0) != 0x80) len++;
    }
    return len;
}

void merge(std::vector<StudentEGE>& arr, int left, int mid, int right) {
    using namespace std;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<StudentEGE> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].score >= R[j].score) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void mergeSort(std::vector<StudentEGE>& arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void create_ege_test_file(const std::string& filename) {
    using namespace std;
    ofstream f(filename);
    if (!f.is_open()) return;
    f << "Иванов 85" << endl;
    f << "Петров 42" << endl;
    f << "Сидоров 98" << endl;
    f << "Александров 70" << endl;
    f << "Кузнецов 100" << endl;
    f << "Новиков 85" << endl;
    f.close();
    cout << "Создан файл '" << filename << "'" << endl;
}

void solve_five12() {
    using namespace std;
    cout << "\nЗадача Five12: Сортировка слиянием (ЕГЭ)" << endl;
    
    string in_file = "ege_input.txt";
    string out_file = "ege_sorted.txt";

    int c = getValidNumber("Создать тестовый файл? (1 - ДА, 0 - НЕТ): ", 0, 1);
    
    if (c == 1) create_ege_test_file(in_file);

    ifstream fin(in_file);
    if (!fin.is_open()) {
        cerr << "Ошибка: Файл " << in_file << " не найден!" << endl;
        return;
    }

    vector<StudentEGE> students;
    StudentEGE temp;
    while (fin >> temp.surname >> temp.score) {
        students.push_back(temp);
    }
    fin.close();

    if (students.empty()) {
        cout << "Файл пуст." << endl;
        return;
    }

    mergeSort(students, 0, students.size() - 1);

    ofstream fout(out_file);
    if (!fout.is_open()) {
        cerr << "Ошибка создания файла вывода!" << endl;
        return;
    }

    for (const auto& s : students) {
        int real_len = get_utf8_length(s.surname);
        
        int padding = 15 - real_len;
        if (padding < 1) padding = 1;
        
        fout << s.surname;
        
        for (int k = 0; k < padding; ++k) {
            fout << " ";
        }
        
        fout << right << setw(3) << s.score << endl;
    }
    fout.close();

    cout << "Данные отсортированы и записаны в '" << out_file << "'" << endl;
    
    ifstream check(out_file);
    string line;
    cout << "\nРезультат: " << endl;
    while(getline(check, line)) {
        cout << line << endl;
    }
}