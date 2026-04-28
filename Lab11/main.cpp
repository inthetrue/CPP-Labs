#include <iostream>
#include <limits>

#include "tasks.h"

namespace {

void print_menu() {
  std::cout << "\nМЕНЮ LAB11:\n";
  std::cout << "1 - ListWork67\n";
  std::cout << "2 - ListWork41\n";
  std::cout << "3 - ListWork44\n";
  std::cout << "4 - ListWork47\n";
  std::cout << "5 - Text2\n";
  std::cout << "6 - Демонстрация всех задач\n";
  std::cout << "0 - Выход\n";
}

}  // namespace

int main() {
  while (true) {
    print_menu();
    std::cout << "Выберите задание: ";

    int choice = 0;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка ввода. Повторите.\n";
      continue;
    }

    switch (choice) {
      case 1:
        lab11::run_task_1();
        break;
      case 2:
        lab11::run_task_2();
        break;
      case 3:
        lab11::run_task_3();
        break;
      case 4:
        lab11::run_task_4();
        break;
      case 5:
        lab11::run_task_5();
        break;
      case 6:
        lab11::run_task_6();
        break;
      case 0:
        return 0;
      default:
        std::cout << "Неверный пункт меню.\n";
        break;
    }
  }
}
