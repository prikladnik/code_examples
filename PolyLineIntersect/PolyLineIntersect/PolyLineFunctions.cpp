#include "iostream"
#include <fstream>
#include "PolyLineFunctions.h"
using namespace std;

void PrintInfo()
{
  cout<<"--------------\n";
  cout<<"PolyLineIntersect\n";
  cout<<"Лабораторная работа №4. Вариант 5.\n";
  cout<<"Разработка структур данных и алгоритмов для решения задач САПР.\n";
  cout<<"Заданы выпуклый многоугольник в плоскости и прямая. Определить, пересекает ли прямая многоугольник.\n";
  cout<<"Если пересекает, вычислить (создать) два многоугольника, на которые исходный многоугольник был разделён прямой.\n";
  cout<<"Студентка группы 414, Голубева Валерия Андреевна, 2014 год.\n";
  cout<<"--------------\n\n";
}

// проверяет - является ли строка value_in вещественным числом
bool IsCorrectDouble(char* value_in, double &value_out, bool showMessage)
{
	// указатель на возможное место начала ошибочной последовательности символов в строке
	char * end_ptr = NULL;
	// попытка преобразования строки в число
	value_out = strtod(value_in, &end_ptr);
	// если указатель не NULL, значит строка содержит посторонние символы
	if (*end_ptr)
	{
		if (showMessage)
			cout<<"Пожалуйста, введите корректное вещественное число!\n";
		return false;
	} else
		return true;
}

// обеспечение корректного ввода вещественного числа с клавиатуры
double InputDouble()
{
	double value_out;
	// строка для хранения введенного пользователем "числа"
	char value_in[255];
	bool isCorrect = false;
	// цикл - пока пользователь не введет корректное вещественное число
	while (!isCorrect)
	{
		cin>>value_in;
		isCorrect = IsCorrectDouble(value_in, value_out);
	}
	return value_out;
}

// файл пуст или не существует
bool FileIsEmpty(char *path, bool showMessage)
{
	bool result = true;
	// вначале проверяем: есть ли такой файл и пуст ли он
	ifstream ifin (path,ios::in);
	if ((ifin) && (ifin.peek() != EOF))
	{
		if (showMessage) 
			cout<<"Файл не пуст! ";
		result = false;
	}
	ifin.close();
	return result;
}