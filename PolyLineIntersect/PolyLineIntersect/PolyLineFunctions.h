// вывод описания лабораторной работы
void PrintInfo();

// проверяет - является ли строка value_in вещественным числом
bool IsCorrectDouble(char* value_in, double &value_out, bool showMessage = true);

// обеспечение корректного ввода вещественного числа с клавиатуры
double InputDouble();

// файл пуст или не существует
bool FileIsEmpty(char *path, bool showMessage);