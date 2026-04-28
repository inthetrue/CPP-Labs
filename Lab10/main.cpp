#include "structures.h"

#include <iostream>

int main() {
  while (true) {
    std::cout << "\nМЕНЮ: \n";
    std::cout << "1. Dynamic4\n";
    std::cout << "2. Dynamic23\n";
    std::cout << "3. ListWork2\n";
    std::cout << "4. ListWork23\n";
    std::cout << "5. ListWork60\n";
    std::cout << "6. Демонстрация add/remove/search\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите пункт: ";

    int choice = 0;
    std::cin >> choice;
    if (!std::cin) {
      std::cout << "Ошибка ввода.\n";
      return 1;
    }

    switch (choice) {
      case 1:
        run_task_dynamic4();
        break;
      case 2:
        run_task_dynamic23();
        break;
      case 3:
        run_task_list_work2();
        break;
      case 4:
        run_task_list_work23();
        break;
      case 5:
        run_task_list_work60();
        break;
      case 6:
        run_demo_operations();
        break;
      case 0:
        std::cout << "Завершение.\n";
        return 0;
      default:
        std::cout << "Нет такого пункта.\n";
        break;
    }
  }
}
