#include <iostream>
#include "tasks.h"

int main() {
    setlocale(LC_ALL, ""); 
    using namespace std;

    int choice;
    do {
        cout << "\nМеню: \n";
        cout << "1. Археолог (BackRec5)\n";
        cout << "2. Черепашка (HomeDyn2)\n";
        cout << "3. K-ичные числа (HomeDyn14)\n";
        cout << "0. Выход\n";
        
        choice = inputInt("Выбор: ", 0, 3);

        switch (choice) {
            case 1:
                solveBackpack();
                break;
            case 2:
                solveTurtle();
                break;
            case 3:
                solveKNumbers();
                break;
            case 0:
                cout << "Выход\n";
                break;
        }

    } while (choice != 0);

    return 0;
}