#include <iostream>
#include "tasks.h"

int main() {
    // Локальное подключение namespace std
    using namespace std; 
    
    setlocale(LC_ALL, "");

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "[1] File7 (Элементы 1, 2, n-1, n)\n";
        cout << "[2] File30 (Удалить 2-ю половину)\n";
        cout << "[3] File49 (Объединить 4 файла по min длине)\n";
        cout << "[4] Recur15 (Выражение: +, -, *)\n";
        cout << "[0] Выход\n";
        
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1: solveFile7(); break;
            case 2: solveFile30(); break;
            case 3: solveFile49(); break;
            case 4: solveRecur15(); break;
            case 0: cout << "Выход\n"; break;
            default: cout << "Нет такого пункта\n";
        }
    } while (choice != 0);

    return 0;
}