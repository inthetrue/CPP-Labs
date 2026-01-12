#ifndef STRING_H
#define STRING_H

#include <string>

// Вспомогательные функции
std::string getInputString(const std::string& prompt);
int askUserMode(const std::string& taskName); // Спрашивает: 1 (Руками) или 2 (Рандом)
std::string generateRandomHex(int length);    // Генерирует Hex строку

// --- ЗАДАЧИ ---

// Задача 1: String42
int count_same_start_end(const std::string& s);

// Задача 2: Str14 (FTP)
void parse_ftp_string(const std::string& s, std::string& login, std::string& password, std::string& server_address);

// Задача 3: Шифр Гаммы
std::string gamma_cipher(const std::string& text, int gamma);

// Задача 4: Дешифровка сдвига (Рус + Англ)
std::string decrypt_shift_cipher(const std::string& s);

// Задача 5: Hex -> Decimal
long long hex_to_decimal(const std::string& hex_s); // Используем long long для больших чисел

// Задача 6: Перемешивание
void shuffle_until_match(const std::string& word);

// Задача 7: Файлы
void create_test_homework_file(const std::string& filename);
void check_homework(const std::string& input_file, const std::string& output_file);

#endif