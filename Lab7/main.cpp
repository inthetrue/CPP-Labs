#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include "tasks.h"

int main() {
    using namespace std;
    setlocale(LC_ALL, ""); 
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    do {
        cout << "\nЗадачи: " << endl;
        cout << "1. Sort2 (Сортировка + Протокол)" << endl;
        cout << "2. ExamTaskC14 (Фитнес)" << endl;
        cout << "3. Five12 (ЕГЭ Сортировка слиянием)" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор - ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                solve_sort2();
                break;
            case 2:
                solve_exam_c14();
                break;
            case 3:
                solve_five12();
                break;
            case 0:
                cout << "Выход..." << endl;
                break;
            default:
                cout << "Нет такого пункта." << endl;
        }

    } while (choice != 0);

    return 0;
}