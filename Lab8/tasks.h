#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <fstream>

int manualMax(int a, int b);
int manualMin(int a, int b);

int inputInt(std::string message, int min, int max);

int readSafeInt(std::ifstream& in);

void solveBackpack();
void solveTurtle();
void solveKNumbers();

#endif