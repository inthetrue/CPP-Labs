#include <exception>
#include <iostream>
#include <limits>

#include "tasks.h"

int main() {
  while (true) {
    std::cout << "\nМЕНЮ LAB12:\n";
    std::cout << "1 - STL2Seq4\n";
    std::cout << "2 - STL2Seq9\n";
    std::cout << "3 - STL2Seq33\n";
    std::cout << "4 - STL1Iter9\n";
    std::cout << "0 - Выход\n";
    std::cout << "Выберите задачу: ";

    int choice = -1;
    std::cin >> choice;

    if (!std::cin) {
      std::cout << "Ошибка ввода\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }

    try {
      switch (choice) {
        case 1:
          run_stl2seq4();
          break;
        case 2:
          run_stl2seq9();
          break;
        case 3:
          run_stl2seq33();
          break;
        case 4:
          run_stl1iter9();
          break;
        case 0:
          std::cout << "Завершение программы\n";
          return 0;
        default:
          std::cout << "Неизвестный пункт меню\n";
          break;
      }
    } catch (const std::exception& error) {
      std::cout << "Ошибка: " << error.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
