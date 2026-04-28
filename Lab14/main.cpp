#include <iostream>
#include <limits>
#include <stdexcept>

#include "tasks.h"

int main() {
  while (true) {
    try {
      std::cout << "\nМеню лабораторной работы 14\n";
      std::cout << "1. Задача 1 STL5Assoc3\n";
      std::cout << "2. Задача 2 STL5Assoc15\n";
      std::cout << "3. Задача 3 STL5Assoc22\n";
      std::cout << "0. Выход\n";
      int command = 0;
      while (true) {
        std::cout << "Введите команду: ";
        if (!(std::cin >> command)) {
          std::cout << "Ошибка: введите номер команды\n";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          continue;
        }
        break;
      }

      switch (command) {
        case 1:
          run_task_1();
          break;
        case 2:
          run_task_2();
          break;
        case 3:
          run_task_3();
          break;
        case 0:
          std::cout << "Завершение программы\n";
          return 0;
        default:
          std::cout << "Неизвестная команда\n";
          break;
      }
    } catch (const std::exception& ex) {
      std::cout << "Ошибка: " << ex.what() << "\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
