#include <iostream>

#include "tasks.h"

int main() {
  while (true) {
    std::cout << "\nМеню лабораторной работы 15\n";
    std::cout << "1. Человек\n";
    std::cout << "2. Имена\n";
    std::cout << "3. Человек с именем\n";
    std::cout << "4. Города\n";
    std::cout << "5. Создаем города\n";
    std::cout << "6. Дроби\n";
    std::cout << "0. Выход\n";

    const int command = read_int("Введите команду: ", 0, 6);

    switch (command) {
      case 1:
        run_task_human();
        break;
      case 2:
        run_task_names();
        break;
      case 3:
        run_task_person_with_name();
        break;
      case 4:
        run_task_cities();
        break;
      case 5:
        run_task_create_cities();
        break;
      case 6:
        run_task_fractions();
        break;
      case 0:
        std::cout << "Завершение программы\n";
        return 0;
      default:
        std::cout << "Неизвестная команда\n";
        break;
    }
  }
}
