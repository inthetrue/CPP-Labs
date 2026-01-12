#include "string.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cstdlib> // rand
#include <ctime>
#include <vector>
#include <fstream>

std::string getInputString(const std::string& prompt) {
    using namespace std;
    string s;
    cout << prompt;
    getline(cin >> ws, s); 
    return s;
}

int askUserMode(const std::string& taskName) {
    using namespace std;
    int mode;
    cout << "\nЗадача - " << taskName << endl;
    cout << "1. Ввести вручную" << endl;
    cout << "2. Сгенерировать случайно" << endl;
    cout << "Выбор:  ";
    cin >> mode;
    
    // Чистим буфер после ввода числа
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return mode;
}

std::string generateRandomHex(int length) {
    using namespace std;
    const char hex_chars[] = "0123456789ABCDEF";
    string res = "";
    for (int i = 0; i < length; ++i) {
        res += hex_chars[rand() % 16];
    }
    return res;
}

// Задача 1
int count_same_start_end(const std::string& s) {
    using namespace std;
    stringstream ss(s);
    string word;
    int count = 0;

    while (ss >> word) {
        if (word.length() >= 2) { 
            string start_char = word.substr(0, 2);
            size_t last_char_i = word.length() - 2; 
            string end_char = word.substr(last_char_i, 2);
            if (start_char == end_char) count++;
        }
    }
    return count;
}

// Задача 2
void parse_ftp_string(const std::string& s, std::string& login, std::string& password, std::string& server_address) {
    using namespace std;
    size_t login_start = s.find("://") + 3;
    size_t password_delimiter = s.find(':', login_start);
    size_t server_start = s.find('@', password_delimiter);

    if (login_start == string::npos || password_delimiter == string::npos || server_start == string::npos) {
        login = "Ошибка";
        password = "Ошибка";
        server_address = "Ошибка";
        return;
    }
    login = s.substr(login_start, password_delimiter - login_start);
    password = s.substr(password_delimiter + 1, server_start - (password_delimiter + 1));
    server_address = s.substr(server_start + 1);
}

// Задача 3
std::string gamma_cipher(const std::string& text, int gamma) {
    using namespace std;
    string result = text;
    for (char &c : result) {
        c ^= gamma;
    }
    return result;
}

// Задача 4: Сдвиг
std::string decrypt_shift_cipher(const std::string& s) {
    using namespace std;
    string dec_text = s;
    
    const string rus_upper = "АБВГДЕËЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    const string rus_lower = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    const int RUS_LEN = 33;
    
    const string eng_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string eng_lower = "abcdefghijklmnopqrstuvwxyz";
    const int ENG_LEN = 26;

    string result = "";

    for (size_t i = 0; i < dec_text.length(); ) {
        unsigned char c = (unsigned char)dec_text[i];
        bool processed = false;

        // Английский (1 байт)
        if (c < 128 && isalpha(c)) { 
            size_t pos = eng_upper.find(dec_text[i]);
            if (pos != string::npos) {
                result += eng_upper[(pos-1)];
                processed = true;
            } else {
                pos = eng_lower.find(dec_text[i]);
                if (pos != string::npos) {
                    result += eng_lower[(pos-1)];
                    processed = true;
                }
            }
            if (processed) { i++; continue; }
        }

        // Русский (2 байта)
        if (i + 1 < dec_text.length()) {
            string current_char = dec_text.substr(i, 2);

            for (int j = 0; j < rus_upper.length(); j += 2) {
                if (current_char == rus_upper.substr(j, 2)) {
                    int idx = j / 2;
                    result += rus_upper.substr(((idx + RUS_LEN - 1) % RUS_LEN) * 2, 2);
                    processed = true; break;
                }
            }


            if (!processed) {
                for (int j = 0; j < rus_lower.length(); j += 2) {
                    if (current_char == rus_lower.substr(j, 2)) {
                        int idx = j / 2;
                        result += rus_lower.substr(((idx + RUS_LEN - 1) % RUS_LEN) * 2, 2);
                        processed = true; break;
                    }
                }
            }
            if (processed) { i += 2; continue; }
        }

        result += dec_text[i];
        i++;
    }
    return result;
}

// Задача 5
long long hex_to_decimal(const std::string& hex_s) {
    using namespace std;
    long long decimal_value = 0;
    long long power = 1;
    string s = hex_s;
    
    for (char &c : s) c = toupper(c);

    for (int i = s.length() - 1; i >= 0; i--) {
        char c = s[i];
        int digit;
        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
        else {
            cerr << "Ошибка: плохой символ " << c << endl;
            return -1;
        }
        decimal_value += digit * power;
        power *= 16;
    }
    return decimal_value;
}

// Задача 6
void shuffle_until_match(const std::string& word) {
    using namespace std;
    if (word.empty()) return;

    vector<string> letters;
    // Разбивка на буквы (UTF-8)
    for (size_t i = 0; i < word.length(); ) {
        unsigned char c = static_cast<unsigned char>(word[i]);
        int char_len = 1;
        if ((c & 0x80) == 0) char_len = 1;       
        else if ((c & 0xE0) == 0xC0) char_len = 2; 
        else if ((c & 0xF0) == 0xE0) char_len = 3;
        else if ((c & 0xF8) == 0xF0) char_len = 4;
        
        letters.push_back(word.substr(i, char_len));
        i += char_len;
    }

    string shuffle_word;
    int attempts = 0;

    cout << "Слово: " << word << ". Перебор: " << endl;
    do {
        for (int i = letters.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            string temp = letters[i];
            letters[i] = letters[j];
            letters[j] = temp;
        }

        shuffle_word = "";
        for (const auto& l : letters) shuffle_word += l;

        attempts++;
        cout << shuffle_word << endl;

    } while (shuffle_word != word); 
    cout << "Готово за " << attempts << " попыток." << endl;
}


void create_test_homework_file(const std::string& filename) {
    using namespace std;
    ofstream f(filename);
    if (!f.is_open()) return;
    f << "10+5=15" << endl;
    f << "20-5=10" << endl; 
    f << "100+200=300" << endl;
    f << "50-60=-10" << endl;
    f << "2+2=5" << endl;   
    f.close();
    cout << "Создан файл: " << filename << endl;
}

void check_homework(const std::string& input_file, const std::string& output_file) {
    using namespace std;
    ifstream in(input_file);
    ofstream out(output_file);

    if (!in.is_open() || !out.is_open()) {
        cerr << "Ошибка файлов!" << endl;
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        
        int n1, n2, ans;
        char op, eq;
        
        if (ss >> n1 >> op >> n2 >> eq >> ans) {
            int correct = 0;
            bool math_ok = true;
            if (op == '+') correct = n1 + n2;
            else if (op == '-') correct = n1 - n2;
            else math_ok = false;

            out << n1 << op << n2 << eq << ans;
            
            if (math_ok && ans != correct) out << "*";
            if (!math_ok) out << " (Знак?)";
        } else {
            out << line << " (Ошибка формата)";
        }
        out << endl;
    }

    in.close();
    out.close();
    
    cout << "Результат в: '" << output_file << "'" << endl;
    ifstream check_out(output_file);
    string l;
    cout << "--- Файл " << output_file << " ---" << endl;
    while (getline(check_out, l)) cout << l << endl;
    cout << "----------------------" << endl;
}