#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <fstream>
#include <vector>

int inputInt(std::string message, int min, int max);
int readSafeInt(std::ifstream& in);
void writeBinary(std::string name, const std::vector<int>& v);
int parseDigit();
int parseTerm();
int parseExpr();

void solveFile7();
void solveFile30();
void solveFile49();
void solveRecur15();

#endif