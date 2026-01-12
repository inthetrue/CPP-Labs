#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <limits>
#include <vector>
#include "string.h"

void run_task(int task_num) {
    using namespace std;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string input_str, login, password, server;
    int mode; 
    
    switch (task_num) {
        case 1:
            input_str = getInputString("Строка: ");
            cout << "Слов (начало=конец): " << count_same_start_end(input_str) << endl;
            break;
            
        case 2:
            input_str = getInputString("FTP: ");
            parse_ftp_string(input_str, login, password, server);
            cout << "Логин: " << login << "\nПароль: " << password << "\nСервер: " << server << endl;
            break;
            
        case 3: {
            input_str = getInputString("Текст: ");
            int gamma_val;
            mode = askUserMode("Шифр Гаммы");
            
            if (mode == 2) {
                gamma_val = 127 + (rand() % 128);
                cout << "Случайная гамма: " << gamma_val << endl;
            } else {
                cout << "Введите гамму: ";
                cin >> gamma_val;
            }
            
            string enc = gamma_cipher(input_str, gamma_val);
            cout << "Шифр: " << enc << "\nРасшифровка: " << gamma_cipher(enc, gamma_val) << endl;
            break;
        }
        
        case 4:
            input_str = getInputString("Шифр (сдвиг +1): ");
            cout << "Расшифровано: " << decrypt_shift_cipher(input_str) << endl;
            break;
            
        case 5: {
            mode = askUserMode("Hex -> Dec");
            if (mode == 2) {
                input_str = generateRandomHex(2 + rand() % 3);
                cout << "Случайный Hex: " << input_str << endl;
            } else {
                input_str = getInputString("Введите Hex: ");
            }
            cout << "Decimal: " << hex_to_decimal(input_str) << endl;
            break;
        }
            
        case 6: {
            mode = askUserMode("Перестановка");
            if (mode == 2) {
                vector<string> words = {"HELLO", "WORLD", "APPLE", "CODE", "CPLUSPLUS", "ПРИВЕТ", "КОРОВА"};
                input_str = words[rand() % words.size()];
                cout << "Случайное слово: " << input_str << endl;
            } else {
                input_str = getInputString("Слово: ");
            }
            shuffle_until_match(input_str);
            break;
        }
            
        case 7: {
            string choice;
            cout << "Пересоздать FN1.txt? (y/n): ";
            getline(cin, choice); 
            if (choice == "y" || choice == "Y") create_test_homework_file("FN1.txt");
            else cout << "Старый FN1.txt" << endl;
            
            check_homework("FN1.txt", "FN2.txt");
            break;
        }
            
        default:
            cout << "Нет такой задачи." << endl;
    }
}

int main() {
    using namespace std;
    setlocale(LC_ALL, ""); 
    srand(static_cast<unsigned int>(time(0)));

    int choice;
    do {
        cout << "\n--- МЕНЮ ---" << endl;
        cout << "1. String42" << endl;
        cout << "2. Str14 (FTP)" << endl;
        cout << "3. Str23 (Гамма)" << endl;
        cout << "4. Str37 (Сдвиг)" << endl;
        cout << "5. Str27 (Hex)" << endl;
        cout << "6. Перестановка" << endl;
        cout << "7. Five2 (Файлы)" << endl;
        cout << "0. Выход" << endl;
        cout << "> ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choice != 0) run_task(choice);

    } while (choice != 0);

    return 0;
}