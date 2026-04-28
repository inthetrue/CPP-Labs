#include "tasks.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>


int manualMax(int a, int b) {
    return (a > b) ? a : b;
}

int manualMin(int a, int b) {
    return (a < b) ? a : b;
}

int inputInt(std::string message, int min, int max) {
    using namespace std;
    int x;
    while (true) {
        cout << message;
        if ((cin >> x) && (x >= min) && (x <= max)) {
            cin.ignore(1000, '\n'); 
            return x;
        } else {
            cout << "Ошибка! Введите целое число от " << min << " до " << max << ".\n";
            cin.clear(); 
            cin.ignore(1000, '\n'); 
        }
    }
}


int readSafeInt(std::ifstream& in) {
    int value;
    while (true) {
        if (in >> value) {
            return value;
        }
        if (in.eof()) {
            return 0; 
        }
        in.clear();
        in.ignore(1);
    }
}

// ЗАДАЧА 1: Археолог
void solveBackpack() {
    using namespace std;
    cout << "\nЗадача: Рюкзак\n";

    ofstream createTest("input_backrec.txt");
    if (createTest.is_open()) {
        createTest << "5 предметов, 10 кг вместимость\n";      
        createTest << "Веса: 2abc 4, 3... 5  5\n"; 
        createTest << "Цены: 3 5 $$ 4 6 2\n"; 
        createTest.close();
        cout << "(Создан файл input_backrec.txt)\n";
    }

    ifstream in("input_backrec.txt");
    if (!in.is_open()) {
        cerr << "Ошибка открытия файла!\n";
        return;
    }

    int N = readSafeInt(in);
    int Z = readSafeInt(in);

    if (N <= 0 || Z < 0) {
        cout << "Ошибка данных в файле (N или Z некорректны).\n";
        return;
    }

    vector<int> weights(N);
    vector<int> values(N);

    for (int i = 0; i < N; ++i) weights[i] = readSafeInt(in);
    for (int i = 0; i < N; ++i) values[i] = readSafeInt(in);
    in.close();

    vector<vector<int>> dp(N + 1, vector<int>(Z + 1, 0));

    for (int i = 1; i <= N; ++i) {
        for (int w = 0; w <= Z; ++w) {
            if (weights[i-1] > w) {
                dp[i][w] = dp[i-1][w];
            } else {
                int valWithout = dp[i-1][w];
                int valWith = dp[i-1][w - weights[i-1]] + values[i-1];
                dp[i][w] = manualMax(valWithout, valWith);
            }
        }
    }

    vector<int> itemsTaken;
    int currentW = Z;
    int maxVal = dp[N][Z];
    int realTotalWeight = 0;

    for (int i = N; i > 0; --i) {
        if (dp[i][currentW] != dp[i-1][currentW]) {
            itemsTaken.push_back(i); 
            currentW -= weights[i-1];
            realTotalWeight += weights[i-1];
        }
    }
    // сортировка пузырьком
    int count = itemsTaken.size();
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (itemsTaken[j] > itemsTaken[j+1]) {
                int temp = itemsTaken[j];
                itemsTaken[j] = itemsTaken[j+1];
                itemsTaken[j+1] = temp;
            }
        }
    }

    cout << "Макс. ценность: " << maxVal << endl;
    cout << "Вес: " << realTotalWeight << endl;
    cout << "Предметы: ";
    if (count == 0) cout << "Нет";
    else {
        for (int i = 0; i < count; ++i) cout << itemsTaken[i] << " ";
    }
    cout << endl;
}

// ЗАДАЧА 2: Черепашка
void solveTurtle() {
    using namespace std;
    cout << "\nЗадача: Черепашка\n";

    ofstream createTest("input_turtle.txt");
    if (createTest.is_open()) {
        createTest << "Size: 3\n";
        createTest << "100 100 5\n";
        createTest << "100 100 5\n";
        createTest << "1 5 5\n";
        createTest.close();
        cout << "(Создан файл input_turtle.txt)\n";
    }

    ifstream in("input_turtle.txt");
    if (!in.is_open()) {
        cerr << "Ошибка открытия файла!\n";
        return;
    }

    int N = readSafeInt(in);
    if (N <= 0) {
        cout << "Ошибка размера доски в файле.\n";
        return;
    }

    vector<vector<int>> board(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = readSafeInt(in);
        }
    }
    in.close();

    const int INF = 1000000;
    vector<vector<int>> dp(N, vector<int>(N, INF));

    int startRow = N - 1;
    int startCol = 0;
    dp[startRow][startCol] = board[startRow][startCol];

    for (int j = 0; j < N; ++j) {
        for (int i = N - 1; i >= 0; --i) {
            if (i == startRow && j == startCol) continue;

            int fromDown = INF;
            int fromLeft = INF;

            if (i + 1 < N) fromDown = dp[i + 1][j];
            if (j - 1 >= 0) fromLeft = dp[i][j - 1];

            if (fromDown != INF || fromLeft != INF) {
                dp[i][j] = board[i][j] + manualMin(fromDown, fromLeft);
            }
        }
    }

    int result = dp[0][N - 1];
    
    ofstream out("output_turtle.txt");
    out << result;
    out.close();

    cout << "Минимальная сумма: " << result << endl;
    cout << "Результат записан в output_turtle.txt" << endl;
}

// ЗАДАЧА 3: K-ичные числа
void solveKNumbers() {
    using namespace std;
    int K, N;
    
    cout << "Введите систему счисления (K): ";
    cin >> K;
    cout << "Введите максимальное количество разрядов (N): ";
    cin >> N;

    if (K < 2 || K > 10 || N < 1 || N > 19 || N + K > 26) {
        cout << "Неправильный ввод" << endl;
        return;
    }

    long long total_sum = 0;

    vector<long long> dp1(N + 1, 0);
    vector<long long> dp0(N + 1, 0);

    dp1[1] = K - 1;
    dp0[1] = 0;

    for (int i = 2; i <= N; i++) {
        dp1[i] = (dp1[i - 1] + dp0[i - 1]) * (K - 1);
        dp0[i] = dp1[i - 1];
    }

    for (int len = 1; len <= N; len++) {
        long long all_numbers = (K - 1);
        for (int p = 0; p < len - 1; p++) {
            all_numbers *= K;
        }

        long long good = dp1[len] + dp0[len];

        long long with_zeros = all_numbers - good;
        
        total_sum += with_zeros;
    }

    cout << "Чисел, содержащих два и более нуля подряд: " << total_sum << endl;
}

