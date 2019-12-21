#include "iostream"
#include <fstream>
using namespace std;

// вывод описания лабораторной работы
void PrintInfo();

// бинарный поиск
int BinarySearch(double arr[], int size, double key);

// пузырьковая сортировка
void BubbleSort(double arr[], int size);

// проверяет - является ли строка value_in вещественным числом
bool IsCorrectDouble(char* value_in, double &value_out);

// обеспечение корректного ввода вещественного числа с клавиатуры
double InputDouble();

// печать массива на экране
void PrintArray(double arr[], int size);

// считывание массива из файла
double* ReadFromFile(int &size, char *path, bool showMessage=true);

// файл пуст или не существует
bool FileIsEmpty(char *path, bool showMessage);

void SaveToFile(char *path, double arr[], int size, bool saveKey, double key, int pos, bool showMessage=true);

// ввод массива с клавиатуры
double* FillArray(int &size);