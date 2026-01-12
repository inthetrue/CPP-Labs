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
        cout << "\nГЛАВНОЕ МЕНЮ: " << endl;
        cout << "1. Фитнес-центр" << endl;
        cout << "2. Школа" << endl;
        cout << "3. Студенты" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор -  ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                fitness_task();
                break;
            case 2:
                school_task();
                break;
            case 3:
                students_task();
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