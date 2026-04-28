#include "tasks.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>

static std::string inputStr;
static int pos = 0;

void writeBinary(std::string name, const std::vector<int>& v) {
    std::ofstream out(name, std::ios::binary);
    for (int x : v) out.write((const char*)&x, sizeof(int));
    out.close();
}

int parseDigit() {
    int num = 0;
    bool found = false;
    // Пока текущий символ — цифра, формируем число
    while (pos < (int)inputStr.length() && isdigit(inputStr[pos])) {
        num = num * 10 + (inputStr[pos] - '0');
        pos++;
        found = true;
    }
    return num;
}

int parseTerm() {
    int res = parseDigit();
    while (pos < (int)inputStr.length() && inputStr[pos] == '*') {
        pos++;
        res *= parseDigit();
    }
    return res;
}

int parseExpr() {
    int res = parseTerm();
    while (pos < (int)inputStr.length() && 
          (inputStr[pos] == '+' || inputStr[pos] == '-')) {
        char op = inputStr[pos++];
        int nextVal = parseTerm();
        if (op == '+') res += nextVal;
        else res -= nextVal;
    }
    return res;
}

// Задача File7
void solveFile7() {
    using namespace std;
    cout << "\nЗадача File7\n";
    
    int n;
    cout << "Сколько чисел записать в файл? ";
    cin >> n;
    if (n < 4) n = 4;

    vector<int> data(n);
    cout << "Введите " << n << " чисел через пробел: ";
    for (int i = 0; i < n; ++i) cin >> data[i];

    writeBinary("file7.dat", data);

    ifstream in("file7.dat", ios::binary);
    in.seekg(0, ios::end); // переход в конец

    int val;
    in.seekg(0, ios::beg); // переход в начало
    in.read((char*)&val, sizeof(int));
    cout << "Первый: " << val << endl;

    in.read((char*)&val, sizeof(int));
    cout << "Второй: " << val << endl;

    in.seekg((n - 2) * sizeof(int), ios::beg);
    in.read((char*)&val, sizeof(int));
    cout << "Предпоследний: " << val << endl;

    in.read((char*)&val, sizeof(int));
    cout << "Последний: " << val << endl;
    in.close();
}

// Задача File30
void solveFile30() {
    using namespace std;
    int n, temp;
    
    cout << "\nЗадача File30\n";
    cout << "Введите количество чисел: ";
    cin >> n;

    fstream f("file30.dat", ios::out | ios::binary);
    cout << "Введите числа: ";
    for (int i = 0; i < n; i++) {
        cin >> temp;
        f.write((char*)&temp, sizeof(int));
    }
    f.close();

    int half = n / 2;
    vector<int> nums(n);
    f.open("file30.dat", ios::in | ios::binary);
    for (int i = 0; i < half; i++) {
        f.read((char*)&nums[i], sizeof(int));
    }
    f.close();

    f.open("file30.dat", ios::out | ios::binary);
    cout << "Результат: ";
    for (int i = 0; i < half; i++) {
        f.write((char*)&nums[i], sizeof(int));
        cout << nums[i] << " ";
    }
    f.close();
    cout << endl;
}

// Задача File49
void solveFile49() {
    using namespace std;
    cout << "\nЗадача File49\n";

    string names[4] = {"SA.dat", "SB.dat", "SC.dat", "SD.dat"};
    for (int i = 0; i < 4; ++i) {
        int count;
        cout << "Сколько чисел в файле " << names[i] << "? ";
        cin >> count;
        vector<int> v(count);
        cout << "Введите числа: ";
        for (int j = 0; j < count; ++j) cin >> v[j];
        writeBinary(names[i], v);
    }

    ifstream fa("SA.dat", ios::binary), fb("SB.dat", ios::binary), 
             fc("SC.dat", ios::binary), fd("SD.dat", ios::binary);
    ofstream fe("SE.dat", ios::binary);

    int a, b, c, d;
    while (fa.read((char*)&a, sizeof(int)) && fb.read((char*)&b, sizeof(int)) && 
           fc.read((char*)&c, sizeof(int)) && fd.read((char*)&d, sizeof(int))) {
        fe.write((char*)&a, sizeof(int));
        fe.write((char*)&b, sizeof(int));
        fe.write((char*)&c, sizeof(int));
        fe.write((char*)&d, sizeof(int));
    }
    fa.close(); fb.close(); fc.close(); fd.close(); fe.close();

    cout << "\nФайл SE.dat записан\nРезультат: ";
    ifstream check("SE.dat", ios::binary);
    while (check.read((char*)&a, sizeof(int))) cout << a << " ";
    cout << endl;
}

// Задача Recur15
void solveRecur15() {
    using namespace std;
    cout << "\nЗадача Recur15\n";
    cout << "Введите выражение (цифры и знаки +, -, *): ";
    cin >> inputStr; 
    pos = 0;
    cout << "Результат: " << parseExpr() << endl;
}