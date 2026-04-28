#include <iostream>

#include "tasks.h"

static void print_menu_block() {
  std::cout << "\nГлавное меню\n";
  std::cout << "1. TreeWork2 вывод по возрастанию\n";
  std::cout << "2. TreeWork11 поиск значения X\n";
  std::cout << "3. TreeWork18 второе максимальное\n";
  std::cout << "0. Выход\n";
}

int main() {
  while (true) {
    print_menu_block();

    const int choice = InputValidator::read_int_in_range(
        "Введите номер пункта: ", 0, 3);

    if (choice == 0) {
      std::cout << "Работа завершена\n";
      break;
    }

    switch (choice) {
      case 1: {
        run_tree_work_2();
        break;
      }
      case 2: {
        run_tree_work_11();
        break;
      }
      case 3: {
        run_tree_work_18();
        break;
      }
      default:
        // этот путь недостижим из-за проверки диапазона
        std::cout << "Неизвестный пункт меню\n";
        break;
    }
  }

  return 0;
}
