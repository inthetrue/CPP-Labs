#include <iostream>
#include <limits>

#include "tasks.h"

int main() {
  int choice = 0;

  do {
    std::cout << "\nЛабораторная работа 13:" << std::endl;
    std::cout << "1. Задача stl3_alg5" << std::endl;
    std::cout << "2. Задача stl3_alg17" << std::endl;
    std::cout << "3. Задача stl3_alg37" << std::endl;
    std::cout << "4. Задача stl3_alg61" << std::endl;
    std::cout << "0. Выход" << std::endl;

    choice = read_int("Выберите задачу: ");

    switch (choice) {
      case 1:
        stl3_alg5();
        break;
      case 2:
        stl3_alg17();
        break;
      case 3:
        stl3_alg37();
        break;
      case 4:
        stl3_alg61();
        break;
      case 0:
        std::cout << "Выход из программы" << std::endl;
        break;
      default:
        std::cout << "Неверный выбор, попробуйте снова" << std::endl;
        break;
    }
  } while (choice != 0);

  return 0;
}